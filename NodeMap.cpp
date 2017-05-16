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
      nodeMap[i]=Node(i,pMap[i]==0,i%mapWidth==0||i%mapWidth==mapWidth-1||i/mapWidth==0||i/mapWidth==mapHeight-1);
      closedNode=&(nodeMap[start]);
      nodeMap[start].closed=true;
      addNeighboursToOpenList();
}

bool NodeMap::addNeighboursToOpenList(){
      int pos=closedNode->pos;
      if(!closedNode->edge){
            if(!nodeMap[pos+1].closed) {
                  if(addToOpenList(&nodeMap[pos+1])) return true;
            }
            if(!nodeMap[pos+1*mapWidth].closed) {
                  if(addToOpenList(&nodeMap[pos+1*mapWidth])) return true;
            }
            if(!nodeMap[pos-1*mapWidth].closed) {
                  if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
            }
            if(!nodeMap[pos-1].closed) {
                  if(addToOpenList(&nodeMap[pos-1])) return true;
            }
            return false;
      }
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
            }else{
                  if(!nodeMap[pos-1*mapWidth].closed) {
                        if(addToOpenList(&nodeMap[pos-1*mapWidth])) return true;
                  }
            }
      }
      return false;
}


bool NodeMap::addToOpenList(Node* neighbour){
      if(!neighbour->open){
            if(neighbour->pos==target){
                  neighbour->parent=closedNode;
                  closedNode=neighbour;
                  return true;
            }
            openList.push(neighbour);
            neighbour->parent=closedNode;
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
      vector<int> path;
      while(*closedNode!=nodeMap[start]){
            path.push_back(closedNode->pos);
            closedNode=closedNode->parent;
      }
      if(path.size()>nOutBufferSize) return path.size();
      for(int i=0;i<path.size();i++) pOutBuffer[i]=path[path.size()-1-i];
      return path.size();
}
