//-------------------------------------------------------------------
// NodeMap.h
// Header file
// Carl Wesslen 2016-05-16
//-----------------------------------------------------------------------------
#ifndef NodeMapclass
#define NodeMapclass
#include "Node.hpp"
#include <queue>
#include <vector>
using namespace std;

class NodeMap{
      private:
            int mapWidth,mapHeight,start,target;
            Node* nodeMap;
            queue<Node*> openList;
            Node* closedNode;
            bool addNeighboursToOpenList();
            bool addToOpenList(Node* neighbor);
      public:
            NodeMap(const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
            const int nStartX, const int nStartY,const int nTargetX, const int nTargetY);
            ~NodeMap(){delete nodeMap;};
            bool step();
            bool openListIsEmpty(){return openList.empty();}
            int fillOutput(int* pOutBuffer, const int nOutBufferSize);
};

#endif
