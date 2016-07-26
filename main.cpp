#include <stdio.h>
#include <assert.h>
#include "grid.h"

int verbose = 1;

extern int FindPath(const int nStartX, const int nStartY,
    const int nTargetX, const int nTargetY,
    const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
    int* pOutBuffer, const int nOutBufferSize);

static int findPathVerbose(const int nStartX, const int nStartY,
    const int nTargetX, const int nTargetY,
    unsigned char* pMap, const int nMapWidth, const int nMapHeight,
    int* pOutBuffer, const int nOutBufferSize) {
        
    int len = FindPath(nStartX, nStartY, nTargetX, nTargetY,
        pMap, nMapWidth, nMapHeight,
        pOutBuffer, nOutBufferSize);
        
    if (!verbose) return len;
    
    printf("Path length = %d\n", len);
    
    int i, j, k;
    
    pMap[pos(nStartX, nStartY, nMapWidth)] = 2;
    pMap[pos(nTargetX, nTargetY, nMapWidth)] = 2;
    
    if (len > 1) for (int k = 0; k < len - 1; k++) pMap[pOutBuffer[k]] = 2;
    
    for (j = 0, k = 0; j < nMapHeight; k++, j++) {
        for(i = 0; i < nMapWidth; i++) printf("%d", pMap[k++]);
        printf("\n");
    }
}

static void test1() {
    unsigned char pMap[] = {
        1, 1, 1, 1,
        0, 1, 0, 1,
        0, 1, 1, 1};
    int pOutBuffer[12];
    int len = findPathVerbose(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

    assert(len == 3);
    assert(pOutBuffer[0] = 1);
    assert(pOutBuffer[0] = 5);
    assert(pOutBuffer[0] = 9);
}

static void test2() {
    unsigned char pMap[] = {
        0, 0, 1,
        0, 1, 1,
        1, 0, 1};
    int pOutBuffer[7];
    int len = findPathVerbose(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);    
    
    assert(len == -1);
}

int main()
{
    test1();
    test2();
    return 0;
}

