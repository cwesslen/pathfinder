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
      int start=nStartX+nStartY*mapWidth;
      closedNode=start;
      G[start]=0;
      map[start]=0;
      for(auto i=0;i<mapWidth*mapHeight;i++) map[i]=pMap[i];
      addNeighboursToOpenList();
}

bool NodeMap::addNeighboursToOpenList(){
      if(closedNode%mapWidth==0){
            if(addToOpenList(closedNode+1)) return true;
            if(closedNode/mapWidth==0){
                  return addToOpenList(closedNode+mapWidth);
            }else if(closedNode/mapWidth==mapHeight-1){
                  return addToOpenList(closedNode-mapWidth);
            }else{
                  if(addToOpenList(closedNode+mapWidth)) return true;
                  return addToOpenList(closedNode-mapWidth);
            }
      }else if(closedNode%mapWidth==mapWidth-1){
            if(addToOpenList(closedNode-1)) return true;
            if(closedNode/mapWidth==0){
                  return addToOpenList(closedNode+mapWidth);
            }else if(closedNode/mapWidth==mapHeight-1) {
                  return addToOpenList(closedNode-mapWidth);
            }else{
                  if(addToOpenList(closedNode+mapWidth)) return true;
                  return addToOpenList(closedNode-mapWidth);
            }
      }else{
            if(addToOpenList(closedNode+1)) return true;
            if(addToOpenList(closedNode-1)) return true;
            if(closedNode/mapWidth==0){
                  return addToOpenList(closedNode+mapWidth);
            }else if(closedNode/mapWidth==mapHeight-1){
                  return addToOpenList(closedNode-mapWidth);
            }
      }
      if(addToOpenList(closedNode+mapWidth)) return true;
      return addToOpenList(closedNode-mapWidth);
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
      if(openList.empty()) return true;
      closedNode=openList.front();
      openList.pop();
      return addNeighboursToOpenList();
}

int NodeMap::fillOutput(int* pOutBuffer, const int nOutBufferSize){
      if(closedNode!=target) return -1;
      int size=G[closedNode];
      if(size>nOutBufferSize) return size;
      for(auto i=size-1;i>0;i--){
            pOutBuffer[i]=closedNode;
            closedNode=parent[closedNode];
      }
      pOutBuffer[0]=closedNode;
      return size;
}
