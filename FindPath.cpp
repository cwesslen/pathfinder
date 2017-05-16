//-------------------------------------------------------------------
// FindPath.cpp
// Function file
// Carl Wesslen 2016-12-09
//-----------------------------------------------------------------------------
#include "FindPath.hpp"

int FindPath(const int nStartX, const int nStartY,
const int nTargetX, const int nTargetY,
const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
int* pOutBuffer, const int nOutBufferSize){
      if(nStartX==nTargetX&&nStartY==nTargetY) return 0;
      NodeMap map(pMap,nMapWidth,nMapHeight,nStartX,nStartY,nTargetX,nTargetY);
      while(!map.openListIsEmpty()){
            if(map.step()){
                  return map.fillOutput(pOutBuffer,nOutBufferSize);
            }
      }
      return -1;
}
