#ifndef SCANLINE_H
#define SCANLINE_H

#include <math.h>
#define maxHt 800
#define maxWd 600
#define maxVer 10000

typedef struct {
	int yMax;
	float XofYmin;
	float slopeInverse;
} EdgeBucket;

typedef struct {
	int countEdgeBucket;
	EdgeBucket buckets[maxVer];
} EdgeTableTuple;

void initEdgeTable();
void printTuple(EdgeTableTuple *tup);
void printTable();
void insertionSort(EdgeTableTuple *ett);
void storeEdgeInTuple (EdgeTableTuple *receiver, int ym, int xm, float slopInv);
void storeEdgeInTable(int x1, int y1, int x2, int y2);
void removeEdgeByYmax(EdgeTableTuple *tup, int yy);
void updateXbySlopeInv(EdgeTableTuple *tup);
void scanlineFill();

#endif // SCANLINE_H
