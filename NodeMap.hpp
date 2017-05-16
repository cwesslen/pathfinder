//-------------------------------------------------------------------
// NodeMap.h
// Header file
// Carl Wesslen 2016-12-09
//-----------------------------------------------------------------------------
#ifndef NodeMapclass
#define NodeMapclass
#include "Node.hpp"
#include <queue>
using namespace std;

class NodeMap{
      private:
            int mapWidth,mapHeight,start,target;
            Node* nodeMap;
            queue<Node*> openList;
            Node* closedNode;
            bool addNeighboursToOpenList();
            bool addToOpenList(Node* neighbor, Node* parent);
      public:
            NodeMap(const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
            const int nStartX, const int nStartY,const int nTargetX, const int nTargetY);
            ~NodeMap(){delete nodeMap;};
            bool step();
            bool openListIsEmpty(){return openList.empty();}
            int fillOutput(int* pOutBuffer, const int nOutBufferSize);
};

#endif
