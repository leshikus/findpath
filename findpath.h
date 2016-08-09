#ifndef FINDPATH_H
#define FINDPATH_H

const int DEBUG = 0;
const int MAX_DEBUG_WIDTH = 40;
const int STATS = 1;

int FindPath(const int nStartX, const int nStartY,
    const int nTargetX, const int nTargetY,
    const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
    int* pOutBuffer, const int nOutBufferSize);
    
#endif // FINDPATH_H
