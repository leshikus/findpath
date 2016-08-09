#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "findpath.h"

const int VERBOSE = 1;
const int MAX_DEBUG_BUFFER = 40;

static int findPathVerbose(const int nStartX, const int nStartY,
    const int nTargetX, const int nTargetY,
    unsigned char* pMap, const int nMapWidth, const int nMapHeight,
    int* pOutBuffer, const int nOutBufferSize) {

    int i, j, k;    
    if (VERBOSE && (nMapWidth <= MAX_DEBUG_WIDTH)) {
        for (j = 0, k = 0; j < nMapHeight; j++) {
            for(i = 0; i < nMapWidth; i++) printf("%d", pMap[k++]);
            printf("\n");
        }
    }
    
        
    int len = FindPath(nStartX, nStartY, nTargetX, nTargetY,
        pMap, nMapWidth, nMapHeight,
        pOutBuffer, nOutBufferSize);
        
    if (!VERBOSE) return len;
    
    printf("Path length = %d\n", len);            
    if ((len > 0) && (len <= nOutBufferSize) && (len <= MAX_DEBUG_BUFFER)) {
        for (k = 0; k < len; k++) printf("p[%i] = %i\n", k, pOutBuffer[k]);
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
    assert(pOutBuffer[18] == 69);  
}

int rand(int m) {
    static int r;
    
    if (m == 0) {
        r = 0;
        return 0;
    }
    
    r = r * 1103515245 + 12345;
    return r % m;
}

void test4(const int mapWidth, const int mapHeight, const int mod, const int res) {
    const int size = mapWidth * mapHeight;
    
    unsigned char* pMap = (unsigned char*) malloc(size * sizeof(char));
    int* pOutBuffer = (int*) malloc(size * sizeof(int));
    
    int k;
    
    rand(0);
    printf("Generating map, mapWidth = %i, mapHeight = %i, pathLen = %i\n", mapWidth, mapHeight, res);
    for (k = 0; k < size; k++) {
        pMap[k] = (rand(mod) == 1) ? 0 : 1;
    }
    pMap[1 + mapWidth] = 1;
    pMap[size - mapWidth - 2] = 1;
    
    int len = findPathVerbose(1, 1, mapWidth - 2, mapHeight - 2, pMap, mapWidth, mapHeight, pOutBuffer, size);    
    assert(len == res);
    
    free(pMap);
    free(pOutBuffer);
}

int main()
{
    test1();
    test2();
    test3();
    test4(20, 20, 8, 34);
    test4(1000, 1000, 3, 1994);
    test4(20000, 20000, 3, 39994);
    return 0;
}

