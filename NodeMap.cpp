//-------------------------------------------------------------------
// NodeMap.cpp
// Function file
// Carl Wesslen 2016-12-09
//-----------------------------------------------------------------------------
#include "NodeMap.hpp"

NodeMap::NodeMap(const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
      const int nStartX, const int nStartY,const int nTargetX, const int nTargetY):
      mapWidth(nMapWidth),mapHeight(nMapHeight),target(nTargetX+nTargetY*mapWidth),
      map(new bool[nMapHeight*nMapWidth]),G(new int[nMapHeight*nMapWidth]),
      parent(new int[nMapHeight*nMapWidth]){
      int size=mapWidth*mapHeight,start=nStartX+nStartY*mapWidth;
      for(int i=0;i<size;i++) map[i]=pMap[i];
      closedNode=start;
      G[start]=0;
      map[start]=0;
      addNeighboursToOpenList();
}

bool NodeMap::addNeighboursToOpenList(){
      if(closedNode%mapWidth==0){
            if(addToOpenList(closedNode+1)) return true;
            if(closedNode/mapWidth==0) {
                  if(addToOpenList(closedNode+1*mapWidth)) return true;
            }else if(closedNode/mapWidth==mapHeight-1){
                  if(addToOpenList(closedNode-1*mapWidth)) return true;
            }else {
                  if(addToOpenList(closedNode+1*mapWidth)) return true;
                  if(addToOpenList(closedNode-1*mapWidth)) return true;
            }
            return false;
      }else if(closedNode%mapWidth==mapWidth-1){
            if(addToOpenList(closedNode-1)) return true;
            if(closedNode/mapWidth==0) {
                  if(addToOpenList(closedNode+1*mapWidth)) return true;
            }else if(closedNode/mapWidth==mapHeight-1) {
                  if(addToOpenList(closedNode-1*mapWidth)) return true;
            }else{
                  if(addToOpenList(closedNode+1*mapWidth)) return true;
                  if(addToOpenList(closedNode-1*mapWidth)) return true;
            }
            return false;
      }else{
            if(addToOpenList(closedNode+1)) return true;
            if(addToOpenList(closedNode-1)) return true;
            if(closedNode/mapWidth==0){
                  if(addToOpenList(closedNode+1*mapWidth)) return true;
                  return false;
            }else if(closedNode/mapWidth==mapHeight-1){
                  if(addToOpenList(closedNode-1*mapWidth)) return true;
                  return false;
            }
      }
      if(addToOpenList(closedNode+1*mapWidth)) return true;
      if(addToOpenList(closedNode-1*mapWidth)) return true;
      return false;
}


bool NodeMap::addToOpenList(const int pos){
      if(map[pos]){
            if(pos==target){
                  parent[pos]=closedNode;
                  G[pos]=G[closedNode]+1;
                  closedNode=pos;
                  return true;
            }
            openList.push(pos);
            parent[pos]=closedNode;
            G[pos]=G[closedNode]+1;
            map[pos]=0;
      }return false;
}

bool NodeMap::step(){
      closedNode=openList.front();
      openList.pop();
      return addNeighboursToOpenList();
}

int NodeMap::fillOutput(int* pOutBuffer, const int nOutBufferSize){
      int size=G[closedNode];
      if(size>nOutBufferSize) return size;
      while(G[closedNode]>0){
            pOutBuffer[G[closedNode]-1]=closedNode;
            closedNode=parent[closedNode];
      }return size;
}
