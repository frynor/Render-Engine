#include "../include/scanline.h"

// Global edge table: one EdgeTableTuple per scanline.
EdgeTableTuple EdgeTable[MAX_HT];
// Active Edge Table (AET)
EdgeTableTuple ActiveEdgeTable;

void initEdgeTable() {
    for (int i = 0; i < MAX_HT; i++) {
        EdgeTable[i].countEdgeBucket = 0;
    }
    ActiveEdgeTable.countEdgeBucket = 0;
}

void printTuple(const EdgeTableTuple *tup) {
    if (tup->countEdgeBucket == 0)
        return;
    printf("Count: %d | ", tup->countEdgeBucket);
    for (int j = 0; j < tup->countEdgeBucket; j++) {
        printf("[yMax: %d, X: %.2f, invSlope: %.2f] ", 
               tup->buckets[j].yMax, tup->buckets[j].XofYmin, tup->buckets[j].slopeInverse);
    }
    printf("\n");
}

void printEdgeTable() {
    for (int i = 0; i < MAX_HT; i++) {
        if (EdgeTable[i].countEdgeBucket > 0) {
            printf("Scanline %d: ", i);
            printTuple(&EdgeTable[i]);
        }
    }
}

void insertionSort(EdgeTableTuple *ett) {
    // Sort by increasing XofYmin.
    for (int i = 1; i < ett->countEdgeBucket; i++) {
        EdgeBucket temp = ett->buckets[i];
        int j = i - 1;
        while (j >= 0 && temp.XofYmin < ett->buckets[j].XofYmin) {
            ett->buckets[j + 1] = ett->buckets[j];
            j--;
        }
        ett->buckets[j + 1] = temp;
    }
}

void storeEdgeInTuple(EdgeTableTuple *receiver, int yMax, int xWithYMin, float slopeInv) {
    if (receiver->countEdgeBucket < MAX_VER) {
        receiver->buckets[receiver->countEdgeBucket].yMax = yMax;
        receiver->buckets[receiver->countEdgeBucket].XofYmin = (float)xWithYMin;
        receiver->buckets[receiver->countEdgeBucket].slopeInverse = slopeInv;
        receiver->countEdgeBucket++;
        insertionSort(receiver);
    } else {
        printf("EdgeTableTuple overflow!\n");
    }
}

void storeEdgeInGlobalTable(int x1, int y1, int x2, int y2) {
    // Ignore horizontal edges.
    if (y1 == y2)
        return;
    
    // Compute inverse slope: Δx / Δy
    float invSlope = (x2 - x1) / (float)(y2 - y1);
    
    // Determine the lower endpoint (start of the edge) and the upper endpoint.
    int yStart, yEnd, xAtYMin;
    if (y1 < y2) {
        yStart = y1;
        yEnd = y2;
        xAtYMin = x1;
    } else {
        yStart = y2;
        yEnd = y1;
        xAtYMin = x2;
    }
    
    if (yStart >= 0 && yStart < MAX_HT) {
        storeEdgeInTuple(&EdgeTable[yStart], yEnd, xAtYMin, invSlope);
    }
}

void removeEdgesAtScanline(EdgeTableTuple *tup, int currentScanline) {
    // Remove edges that are no longer active.
    for (int i = tup->countEdgeBucket - 1; i >= 0; i--) {
        if (tup->buckets[i].yMax <= currentScanline) {
            // Shift remaining buckets down.
            for (int j = i; j < tup->countEdgeBucket - 1; j++) {
                tup->buckets[j] = tup->buckets[j + 1];
            }
            tup->countEdgeBucket--;
        }
    }
}

void updateXInActiveEdgeTable(EdgeTableTuple *tup) {
    for (int i = 0; i < tup->countEdgeBucket; i++) {
        tup->buckets[i].XofYmin += tup->buckets[i].slopeInverse;
    }
}

// A simple stub for drawing a horizontal line.
// In your actual renderer, replace this with a function that sets pixels in your framebuffer.
#ifdef DEBUG_DRAW
#include <stdlib.h>
void drawHorizontalLine(int y, int xStart, int xEnd) {
    printf("Scanline %d: Filling from x=%d to x=%d\n", y, xStart, xEnd);
}
#endif

void scanlineFill(void (*drawHorizontalLine)(int y, int xStart, int xEnd)) {
    // Determine the overall y-range where edges exist.
    int yMin = MAX_HT, yMax = 0;
    for (int i = 0; i < MAX_HT; i++) {
        if (EdgeTable[i].countEdgeBucket > 0) {
            if (i < yMin)
                yMin = i;
            for (int j = 0; j < EdgeTable[i].countEdgeBucket; j++) {
                if (EdgeTable[i].buckets[j].yMax > yMax)
                    yMax = EdgeTable[i].buckets[j].yMax;
            }
        }
    }
    
    // Process each scanline from yMin to yMax.
    for (int y = yMin; y < yMax; y++) {
        // 1. Add edges that start at this scanline to the Active Edge Table.
        if (y < MAX_HT && EdgeTable[y].countEdgeBucket > 0) {
            for (int i = 0; i < EdgeTable[y].countEdgeBucket; i++) {
                storeEdgeInTuple(&ActiveEdgeTable, 
                                 EdgeTable[y].buckets[i].yMax,
                                 (int)EdgeTable[y].buckets[i].XofYmin,
                                 EdgeTable[y].buckets[i].slopeInverse);
            }
        }
        
        // 2. Remove edges from AET that are no longer active.
        removeEdgesAtScanline(&ActiveEdgeTable, y);
        
        // 3. Sort the Active Edge Table by current x intersections.
        insertionSort(&ActiveEdgeTable);
        
        // 4. For each pair of edges in the AET, fill between them.
        for (int i = 0; i < ActiveEdgeTable.countEdgeBucket; i += 2) {
            if (i + 1 < ActiveEdgeTable.countEdgeBucket) {
                int xStart = (int)(ActiveEdgeTable.buckets[i].XofYmin);
                int xEnd = (int)(ActiveEdgeTable.buckets[i + 1].XofYmin);
                if (xStart > xEnd) {
                    int temp = xStart;
                    xStart = xEnd;
                    xEnd = temp;
                }
                // Draw (or fill) the horizontal span.
                drawHorizontalLine(y, xStart, xEnd);
            }
        }
        
        // 5. Update x intersections in the AET for the next scanline.
        updateXInActiveEdgeTable(&ActiveEdgeTable);
    }
    
    printf("Scanline filling complete.\n");
}
