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
      for(int i=0;i<mapWidth*mapHeight;i++) nodeMap[i]=Node(i,pMap[i]==1,i%mapWidth==0||i%mapWidth==mapWidth-1||i/mapWidth==0||i/mapWidth==mapHeight-1);
      closedNode=&(nodeMap[start]);
      nodeMap[start].G=0;
      nodeMap[start].closed=true;
      addNeighboursToOpenList();
}

bool NodeMap::addNeighboursToOpenList(){
      Node* node=closedNode;
      int x=node->pos%mapWidth;
      int y=node->pos/mapWidth;
      Node* neighbour;
      if(!node->edge){
            neighbour=&nodeMap[x+1+(y)*mapWidth];
            if(neighbour->pass&&!neighbour->closed) {
                  if(addToOpenList(neighbour,node)) return true;
            }
            neighbour=&nodeMap[x+(y+1)*mapWidth];
            if(neighbour->pass&&!neighbour->closed) {
                  if(addToOpenList(neighbour,node)) return true;
            }
            neighbour=&nodeMap[x+(y-1)*mapWidth];
            if(neighbour->pass&&!neighbour->closed) {
                  if(addToOpenList(neighbour,node)) return true;
            }
            neighbour=&nodeMap[x-1+(y)*mapWidth];
            if(neighbour->pass&&!neighbour->closed) {
                  if(addToOpenList(neighbour,node)) return true;
            }
            return false;
      }
      if(x==0){
            if(y==0) {
                  neighbour=&nodeMap[x+1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y+1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
            }
            }else if(y==mapHeight-1){
                  neighbour=&nodeMap[x+1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
            }
                  neighbour=&nodeMap[x+(y-1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
            }
            }else {
                  neighbour=&nodeMap[x+1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y+1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y-1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
            }
            }
      }else if(x==mapWidth-1){
            if(y==0) {
                  neighbour=&nodeMap[x-1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y+1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
            }else if(y==mapHeight-1) {
                  neighbour=&nodeMap[x-1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y-1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
            }else{
                  neighbour=&nodeMap[x-1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y+1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y-1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
            }
      }else{
            if(y==0){
                  neighbour=&nodeMap[x+1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y+1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x-1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
            }else if(y==mapHeight-1){
                  neighbour=&nodeMap[x+1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x+(y-1)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
                  neighbour=&nodeMap[x-1+(y)*mapWidth];
                  if(neighbour->pass&&!neighbour->closed) {
                        if(addToOpenList(neighbour,node)) return true;
                  }
            }
      }
      return false;
}


bool NodeMap::addToOpenList(Node* neighbour, Node* parent){
      if(!neighbour->open){
            if(neighbour->pos==target){
                  closedNode=neighbour;
                  neighbour->parent=parent;
                  return true;
            }
            neighbour->parent=parent;
            neighbour->G=parent->G+1;
            openList.push_front(neighbour);
            neighbour->open=true;
            return false;
      }
      return false;
}

bool NodeMap::step(){
      closedNode=openList.back();
      closedNode->closed=true;
      openList.pop_back();
      return addNeighboursToOpenList();
}

int NodeMap::fillOutput(int* pOutBuffer, const int nOutBufferSize){
      Node* node=closedNode;
      vector<int> path;
      while(*node!=nodeMap[start]){
            path.push_back(node->pos);
            node=node->parent;
      }
      for(int i=0;i<path.size()&&i<nOutBufferSize;i++){
            pOutBuffer[i]=path[path.size()-1-i];
      }
      return path.size();
}
