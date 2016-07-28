#include <stdio.h>
#include <assert.h>

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
        
    if (len > 1) {
        for (k = 0; k < len; k++) printf("p[%i] = %i\n", k, pOutBuffer[k]);
    }
    
//    pMap[nStartX + nMapWidth * nStartY] = 2;
//    pMap[nTargetX + nMapWidth * nTargetY] = 2;
//    if (len > 1) for (k = 0; k < len - 1; k++) pMap[pOutBuffer[k]] = 2;
    
    for (j = 0, k = 0; j < nMapHeight; j++) {
        for(i = 0; i < nMapWidth; i++) printf("%d", pMap[k++]);
        printf("\n");
    }
    
    return len;
}

static void test1() {
    unsigned char pMap[] = {
        1, 1, 1, 1,
        0, 1, 0, 1,
        0, 1, 1, 1};
    int pOutBuffer[12];
    int len = findPathVerbose(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

    assert(len == 3);
    assert(pOutBuffer[0] == 1);
    assert(pOutBuffer[1] == 5);
    assert(pOutBuffer[2] == 9);
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

void test3() {
    int mapWidth = 10;
    int mapHeight = 10;
    unsigned char pMap[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
        0, 1, 0, 0, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 0, 1, 1, 1, 1, 0, 0,
        1, 1, 1, 0, 1, 1, 1, 0, 0, 1,
        1, 1, 1, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
    int pOutBuffer[100];
    int len = findPathVerbose(0, 0, 9, 6, pMap, mapWidth, mapHeight, pOutBuffer, 19);

    assert(len == 19);
    assert(pOutBuffer[3] == 31);    
    assert(pOutBuffer[9] == 82);
    assert(pOutBuffer[10] == 83);
    assert(pOutBuffer[11] == 84);
    assert(pOutBuffer[12] == 85);
    assert(pOutBuffer[13] == 86);
    assert(pOutBuffer[14] == 87);
    assert(pOutBuffer[15] == 88);
    assert(pOutBuffer[16] == 78);
    assert(pOutBuffer[18] == 69);  
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}

