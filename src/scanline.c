#include "../include/scanline.h"
#include <stdio.h>

EdgeTableTuple EdgeTable[maxHt], ActiveEdgeTuple;

void initEdgeTable() {
	int i;
	for (i = 0; i < maxHt; i++) {
		EdgeTable[i].countEdgeBucket = 0;
	}

	ActiveEdgeTuple.countEdgeBucket = 0;
}

void printTuple(EdgeTableTuple *tup) {
     
    	if (tup->countEdgeBucket) {
		printf("\nCOunt %d------\n", tup->countEdgeBucket);
	}

	for (int j = 0; j < tup->countEdgeBucket; j++) {
		printf(" %d+%.2f+%.2f", tup->buckets[j].yMax, tup->buckets[j].XofYmin, tup->buckets[j].slopeInverse);
	}
         
}

void printTable() {
	for (int i = 0; i < maxHt; i++) {
		if (EdgeTable[i].countEdgeBucket) {
			printf("\nScanline %d", i);
		}
		printTuple(&EdgeTable[i]);
	}
}

void insertionSort(EdgeTableTuple *ett) {
	EdgeBucket temp;

	for (int i = 1; i < ett->countEdgeBucket; i++) {
		temp.yMax = ett->buckets[i].yMax;
		temp.XofYmin = ett->buckets[i].XofYmin;
		temp.slopeInverse = ett->buckets[i].slopeInverse;
		int j = i - 1;

		while ((temp.XofYmin < ett->buckets[i].XofYmin) && (j >= 0)) {
			ett->buckets[j + 1].yMax = ett->buckets[j].yMax;
			ett->buckets[j + 1].XofYmin = ett->buckets[j].XofYmin;
			ett->buckets[j + 1].slopeInverse = ett->buckets[j].slopeInverse;
			j--;
		}
		ett->buckets[j + 1].yMax = temp.yMax;
		ett->buckets[j + 1].XofYmin = temp.XofYmin;
		ett->buckets[j + 1].slopeInverse = temp.slopeInverse;
	}

}

void storeEdgeInTuple(EdgeTableTuple *receiver, int ym, int xm, float slopInv) {
	// both used for edgetable and active edge table..
    	// The edge tuple sorted in increasing ymax and x of the lower end.
    	(receiver->buckets[(receiver)->countEdgeBucket]).yMax = ym;
    	(receiver->buckets[(receiver)->countEdgeBucket]).XofYmin = (float)xm;
    	(receiver->buckets[(receiver)->countEdgeBucket]).slopeInverse = slopInv;
             
    	// sort the buckets
    	insertionSort(receiver);
    	     
    	(receiver->countEdgeBucket)++;
}

void storeEdgeInTable(int x1, int y1, int x2, int y2) {
	float m, minV;
	int yMaxTS, XwithYminTS, scanline;

	if (x2 == x1) {
		minV = 0.000000;
	} else {
		m = ((float)(y2 - y1)) / ((float)(x2 - x1));
		if (y2 == y1) {
			return;
		}
		minV = (float)1.0/m;
		printf("\nSlope string for %d %d & %d %d: %f", x1, y1, x2, y2, minV);
	}

	if (y1 > y2) {
		scanline = y2;
		yMaxTS = y1;
		XwithYminTS = x2;
	} else {
		scanline = y1;
		yMaxTS = y2;
		XwithYminTS = x1;
	}

	storeEdgeInTuple(&EdgeTable[scanline], yMaxTS, XwithYminTS, minV);

}

void removeEdgeByYmax(EdgeTableTuple *tup, int yy) {
	for (int i = 0; i < tup->countEdgeBucket; i++) {
		if (tup->buckets[i].yMax == yy) {
			printf("\nRemoved at %d", yy);

			for (int j = i; j < tup->countEdgeBucket - 1; j++) {
				tup->buckets[j].yMax = tup->buckets[j + 1].yMax;
				tup->buckets[j].XofYmin = tup->buckets[j + 1].XofYmin;
				tup->buckets[j].slopeInverse = tup->buckets[j + 1].slopeInverse;
			}
			tup->countEdgeBucket--;
		}
		i--;
	}
}

void updateXbySlopeInv(EdgeTableTuple *tup) {
	for (int i = 0; i < tup->countEdgeBucket; i++) {
		(tup->buckets[i]).XofYmin = (tup->buckets[i]).XofYmin + (tup->buckets[i]).slopeInverse;
	}
}

void scanlineFill() {
    /* Follow the following rules:
    1. Horizontal edges: Do not include in edge table
    2. Horizontal edges: Drawn either on the bottom or on the top.
    3. Vertices: If local max or min, then count twice, else count
        once.
    4. Either vertices at local minima or at local maxima are drawn.*/
 
 
    int i, j, x1, ymax1, x2, ymax2, FillFlag = 0, coordCount;
     
    // we will start from scanline 0; 
    // Repeat until last scanline:
    for (i=0; i<maxHt; i++)//4. Increment y by 1 (next scan line)
    {
         
        // 1. Move from ET bucket y to the
        // AET those edges whose ymin = y (entering edges)
        for (j=0; j<EdgeTable[i].countEdgeBucket; j++)
        {
            storeEdgeInTuple(&ActiveEdgeTuple,EdgeTable[i].buckets[j].
                     yMax,EdgeTable[i].buckets[j].XofYmin,
                    EdgeTable[i].buckets[j].slopeInverse);
        }
        printTuple(&ActiveEdgeTuple);
         
        // 2. Remove from AET those edges for 
        // which y=ymax (not involved in next scan line)
        removeEdgeByYmax(&ActiveEdgeTuple, i);
         
        //sort AET (remember: ET is presorted)
        insertionSort(&ActiveEdgeTuple);
         
        printTuple(&ActiveEdgeTuple);
         
        //3. Fill lines on scan line y by using pairs of x-coords from AET
        j = 0; 
        FillFlag = 0;
        coordCount = 0;
        x1 = 0;
        x2 = 0;
        ymax1 = 0;
        ymax2 = 0;
        while (j<ActiveEdgeTuple.countEdgeBucket)
        {
            if (coordCount%2==0)
            {
                x1 = (int)(ActiveEdgeTuple.buckets[j].XofYmin);
                ymax1 = ActiveEdgeTuple.buckets[j].yMax;
                if (x1==x2)
                {
                /* three cases can arrive-
                    1. lines are towards top of the intersection
                    2. lines are towards bottom
                    3. one line is towards top and other is towards bottom
                */
                    if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
                    {
                        x2 = x1;
                        ymax2 = ymax1;
                    }
                 
                    else
                    {
                        coordCount++;
                    }
                }
                 
                else
                {
                        coordCount++;
                }
            }
            else
            {
                x2 = (int)ActiveEdgeTuple.buckets[j].XofYmin;
                ymax2 = ActiveEdgeTuple.buckets[j].yMax; 
             
                FillFlag = 0;
                 
                // checking for intersection...
                if (x1==x2)
                {
                /*three cases can arrive-
                    1. lines are towards top of the intersection
                    2. lines are towards bottom
                    3. one line is towards top and other is towards bottom
                */
                    if (((x1==ymax1)&&(x2!=ymax2))||((x1!=ymax1)&&(x2==ymax2)))
                    {
                        x1 = x2;
                        ymax1 = ymax2;
                    }
                    else
                    {
                        coordCount++;
                        FillFlag = 1;
                    }
                }
                else
                {
                        coordCount++;
                        FillFlag = 1;
                } 
              
        }
             
        j++;
    } 
             
         
    // 5. For each nonvertical edge remaining in AET, update x for new y
    updateXbySlopeInv(&ActiveEdgeTuple);
}
 
 
printf("\nScanline filling complete");
 
}
