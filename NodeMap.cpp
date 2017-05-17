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
      int size=mapWidth*mapHeight;
      for(int i=0;i<size;i++) nodeMap[i]=Node(i,pMap[i]);
      closedNode=start;
      nodeMap[start].G=0;
      nodeMap[start].passable=false;
      addNeighboursToOpenList();
}

bool NodeMap::addNeighboursToOpenList(){
      int pos=closedNode;
      if(pos%mapWidth==0){
            if(nodeMap[pos+1].passable) {
                  if(addToOpenList(&nodeMap[pos+1])) return true;
            }
            if(pos/mapWidth==0) {
                  if(nodeMap[pos+1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
            }
            }else if(pos/mapWidth==mapHeight-1){
                  if(nodeMap[pos-1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
            }
            }else {
                  if(nodeMap[pos+1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
                  }
                  if(nodeMap[pos-1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
            }
            return false;
      }else if(pos%mapWidth==mapWidth-1){
            if(nodeMap[pos-1].passable) {
                  if(addToOpenList(&nodeMap[pos-1])) return true;
            }
            if(pos/mapWidth==0) {
                  if(nodeMap[pos+1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
                  }
            }else if(pos/mapWidth==mapHeight-1) {
                  if(nodeMap[pos-1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
            }else{
                  if(nodeMap[pos+1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
                  }
                  if(nodeMap[pos-1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
            }
            return false;
      }else{
            if(nodeMap[pos+1].passable) {
                  if(addToOpenList(&nodeMap[pos+1])) return true;
            }
            if(nodeMap[pos-1].passable) {
                  if(addToOpenList(&nodeMap[pos-1])) return true;
            }
            if(pos/mapWidth==0){
                  if(nodeMap[pos+1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
                  }
                  return false;
            }else if(pos/mapWidth==mapHeight-1){
                  if(nodeMap[pos-1*mapWidth].passable) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
                  return false;
            }
      }
      if(nodeMap[pos+1*mapWidth].passable) {
            if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
      }
      if(nodeMap[pos-1*mapWidth].passable) {
            if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
      }
      return false;
}


bool NodeMap::addToOpenList(Node* neighbour){
      if(neighbour->pos==target){
            neighbour->parent=closedNode;
            neighbour->G=nodeMap[closedNode].G+1;
            closedNode=neighbour->pos;
            return true;
      }
      openList.push(neighbour->pos);
      neighbour->parent=closedNode;
      neighbour->G=nodeMap[closedNode].G+1;
      neighbour->passable=false;
      return false;
}

bool NodeMap::step(){
      closedNode=(openList.front());
      openList.pop();
      return addNeighboursToOpenList();
}

int NodeMap::fillOutput(int* pOutBuffer, const int nOutBufferSize){
      int size=nodeMap[closedNode].G;
      if(size>nOutBufferSize) return size;
      while(nodeMap[closedNode].G>0){
            pOutBuffer[nodeMap[closedNode].G-1]=nodeMap[closedNode].pos;
            closedNode=nodeMap[closedNode].parent;
      }return size;
}
