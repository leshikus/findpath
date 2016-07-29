#include <stdio.h>
#include <stdlib.h>

int debug = 0;

class Map {
protected:
    const unsigned char* pMap;
    const int nWidth, nHeight, nSize;
public:
    Map(const unsigned char* _pMap, const int _nWidth, const int _nHeight) :
        pMap(_pMap), nWidth(_nWidth), nHeight(_nHeight), nSize(_nWidth * _nHeight) {
    }
    
    inline int pos(int x, int y) {
        return x + y * nWidth;
    }
    
    inline int dist(int from, int to) {
        int deltaX = from % nWidth - to % nWidth;
        int deltaY = from / nWidth - to / nWidth;
        
        return abs(deltaX) + abs(deltaY);        
    }
};

class MarkedMap: public Map {
    int nStart, nTarget, maxDist;
    int* pMarkedMap;
    int* pEquidistantSet;
    int* pPrev;
    int* pEnd;

public:
    bool isTargetFound;

    MarkedMap(const unsigned char* _pMap, const int _nWidth, const int _nHeight,
        const int _maxDist):
        Map(_pMap, _nWidth, _nHeight), maxDist(_maxDist) {
        pMarkedMap = (int*) calloc(nSize, sizeof(int));
        pEquidistantSet = (int*) calloc(nSize, sizeof(int));
        pPrev = pEquidistantSet;
        pEnd = pEquidistantSet;
    }

    ~MarkedMap() {
        free(pEquidistantSet);
        free(pMarkedMap);
    }
    
    void setEndpoints(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY) {
        nTarget = pos(nTargetX, nTargetY);
        isTargetFound = false;

        nStart = pos(nStartX, nStartY);
        pMarkedMap[nStart] = -1;
        markNeighbors(nStart, 1);
    }
    
    void mark(const int pos, const int d) {
        if (debug) {
            printf("pos = %i, d = %i\n", pos, d);
        }
        
        if (pMap[pos] == 0) return;
        if (pMarkedMap[pos] != 0) return;
        
        if (dist(pos, nTarget) + d > maxDist) return;
        
        if (debug) printf("marked at %i\n", pEnd - pEquidistantSet);
        pMarkedMap[pos] = d;
        *pEnd = pos;
        pEnd++;

        if (pos == nTarget) {
            isTargetFound = true;
            return;
        }        
    }
    
    void markNeighbors(const int pos, const int d) {
        if (pos % nWidth >= 1) mark(pos - 1, d);
        if (pos % nWidth < nWidth - 1) mark(pos + 1, d);

        if (pos >= nWidth) mark(pos - nWidth, d);
        if (pos < nSize - nWidth) mark(pos + nWidth, d);
    }

    int findNeighbor(const int pos, const int d) {
        if ((pos % nWidth >= 1) && (pMarkedMap[pos - 1] == d)) return pos - 1;
        if ((pos % nWidth < nWidth - 1) && (pMarkedMap[pos + 1] == d)) return pos + 1;

        if ((pos >= nWidth) && (pMarkedMap[pos - nWidth] == d)) return pos - nWidth;
        if ((pos < nSize - nWidth) && (pMarkedMap[pos + nWidth] == d)) return pos + nWidth;
        return -1;
    }
    
    bool addDist(const int d) {
        int* pNext = pEnd;
        int* pCur = pPrev;
        for (; (pCur < pNext) && !isTargetFound; pCur++) {
            markNeighbors(*pCur, d);
        }
        if (debug) {
            int i, j, k;
            for (j = 0, k = 0; j < nHeight; j++) {
                for(i = 0; i < nWidth; i++) printf("%3d", pMarkedMap[k++]);
                printf("\n");
            }
        }
        
        
        pPrev = pNext;
        return (pNext < pEnd);
    }
    
    void fillPath(int* pOutBuffer, int d) {
        if (debug) {
            int i, j, k;
            for (j = 0, k = 0; j < nHeight; j++) {
                for(i = 0; i < nWidth; i++) printf("%2d", pMarkedMap[k++]);
                printf("\n");
            }
        }
        
        int pos = nTarget;
        pOutBuffer[--d] = pos;
        while (d > 0) {
            pos = findNeighbor(pos, d);
            pOutBuffer[--d] = pos;
        }
    }
    
};


int FindPath(const int nStartX, const int nStartY,
    const int nTargetX, const int nTargetY,
    const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
    int* pOutBuffer, const int nOutBufferSize) {
                 
    MarkedMap map(pMap, nMapWidth, nMapHeight, nOutBufferSize);
    map.setEndpoints(nStartX, nStartY, nTargetX, nTargetY);
    
    int d;
    for (d = 2; d <= nOutBufferSize; d++) {
        int isAdded = map.addDist(d);
        if (map.isTargetFound) {
            map.fillPath(pOutBuffer, d);
            return d;            
        }
        if (!isAdded) return -1;
    }
    return -1;
}
