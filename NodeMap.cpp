//-------------------------------------------------------------------
// NodeMap.cpp
// Function file
// Carl Wesslen 2016-12-09
//-----------------------------------------------------------------------------
#include "NodeMap.hpp"

NodeMap::NodeMap(const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
      const int nStartX, const int nStartY,const int nTargetX, const int nTargetY):
      mapWidth(nMapWidth),mapHeight(nMapHeight),start(nStartX+nStartY*mapWidth),
      target(nTargetX+nTargetY*mapWidth),nodeMap(new Node[nMapHeight*nMapWidth]){
      for(int i=0;i<mapWidth*mapHeight;i++)
      nodeMap[i]=Node(i,pMap[i]==0);
      closedNode=&(nodeMap[start]);
      nodeMap[start].G=0;
      nodeMap[start].closed=true;
      addNeighboursToOpenList();
}

bool NodeMap::addNeighboursToOpenList(){
      int pos=closedNode->pos;
      if(pos%mapWidth==0){
            if(!nodeMap[pos+1].closed) {
                  if(addToOpenList(&nodeMap[pos+1])) return true;
            }
            if(pos/mapWidth==0) {
                  if(!nodeMap[pos+1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
            }
            }else if(pos/mapWidth==mapHeight-1){
                  if(!nodeMap[pos-1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
            }
            }else {
                  if(!nodeMap[pos+1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
                  }
                  if(!nodeMap[pos-1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
            }
            return false;
      }else if(pos%mapWidth==mapWidth-1){
            if(!nodeMap[pos-1].closed) {
                  if(addToOpenList(&nodeMap[pos-1])) return true;
            }
            if(pos/mapWidth==0) {
                  if(!nodeMap[pos+1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
                  }
            }else if(pos/mapWidth==mapHeight-1) {
                  if(!nodeMap[pos-1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
            }else{
                  if(!nodeMap[pos+1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
                  }
                  if(!nodeMap[pos-1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
            }
            return false;
      }else{
            if(!nodeMap[pos+1].closed) {
                  if(addToOpenList(&nodeMap[pos+1])) return true;
            }
            if(!nodeMap[pos-1].closed) {
                  if(addToOpenList(&nodeMap[pos-1])) return true;
            }
            if(pos/mapWidth==0){
                  if(!nodeMap[pos+1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
                  }
                  return false;
            }else if(pos/mapWidth==mapHeight-1){
                  if(!nodeMap[pos-1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
                  return false;
            }
      }
      if(!nodeMap[pos+1*mapWidth].closed) {
            if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
      }
      if(!nodeMap[pos-1*mapWidth].closed) {
            if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
      }
      return false;
}


bool NodeMap::addToOpenList(Node* neighbour){
      if(!neighbour->open){
            if(neighbour->pos==target){
                  neighbour->parent=closedNode;
                  neighbour->G=closedNode->G+1;
                  closedNode=neighbour;
                  return true;
            }
            openList.push(neighbour);
            neighbour->parent=closedNode;
            neighbour->G=closedNode->G+1;
            neighbour->open=true;
            return false;
      }
      return false;
}

bool NodeMap::step(){
      closedNode=openList.front();
      closedNode->closed=true;
      openList.pop();
      return addNeighboursToOpenList();
}

int NodeMap::fillOutput(int* pOutBuffer, const int nOutBufferSize){
      int size=closedNode->G;
      if(size>nOutBufferSize) return size;
      while(closedNode->G>0){
            pOutBuffer[closedNode->G-1]=closedNode->pos;
            closedNode=closedNode->parent;
      }return size;
}
