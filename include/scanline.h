#ifndef SCANLINE_H
#define SCANLINE_H

#include <math.h>
#include <stdio.h>

#define MAX_HT 800
#define MAX_WD 600
#define MAX_VER 10000

// An edge bucket holds the y-coordinate where the edge ends (yMax),
// the x-coordinate of the intersection at the lower end (XofYmin),
// and the inverse slope (delta x / delta y)
typedef struct {
    int yMax;
    float XofYmin;
    float slopeInverse;
} EdgeBucket;

// A tuple (list) of edge buckets
typedef struct {
    int countEdgeBucket;
    EdgeBucket buckets[MAX_VER];
} EdgeTableTuple;

// Global edge table: one entry per scanline (indexed by y)
extern EdgeTableTuple EdgeTable[MAX_HT];

// Active Edge Table (AET) used during the scanline fill
extern EdgeTableTuple ActiveEdgeTable;

// Initializes the global Edge Table and Active Edge Table.
void initEdgeTable();

// For debugging: prints the contents of a given edge table tuple.
void printTuple(const EdgeTableTuple *tup);

// For debugging: prints the entire global edge table.
void printEdgeTable();

// Insertion sort the tuple by increasing XofYmin.
void insertionSort(EdgeTableTuple *ett);

// Inserts an edge into a given tuple.
// (yMax: the maximum y of the edge,
//  xWithYMin: the x coordinate at the lower endpoint,
//  slopeInv: inverse slope = Δx/Δy)
void storeEdgeInTuple(EdgeTableTuple *receiver, int yMax, int xWithYMin, float slopeInv);

// Computes the inverse slope and inserts the edge into the global Edge Table.
// Horizontal edges (y1 == y2) are ignored.
void storeEdgeInGlobalTable(int x1, int y1, int x2, int y2);

// Removes from a tuple (typically the AET) any edges that have yMax <= currentScanline.
void removeEdgesAtScanline(EdgeTableTuple *tup, int currentScanline);

// For each active edge, update its current x-intersection by adding its inverse slope.
void updateXInActiveEdgeTable(EdgeTableTuple *tup);

// The scanline fill algorithm. For each scanline, it processes the global
// edge table and active edge table, then fills horizontal spans.
// The parameter drawHorizontalLine is a callback function that, given a scanline y,
// and a starting x and ending x, will draw (or fill) that span.
void scanlineFill(void (*drawHorizontalLine)(int y, int xStart, int xEnd));

#endif // SCANLINE_H
