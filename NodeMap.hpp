//-------------------------------------------------------------------
// NodeMap.h
// Header file
// Carl Wesslen 2016-05-16
//-----------------------------------------------------------------------------
#ifndef NodeMapclass
#define NodeMapclass
#include <queue>
using namespace std;

class NodeMap{
      private:
            int mapWidth,mapHeight,target,closedNode;
            queue<int> openList;
            bool* map;
            int* G;
            int* parent;
            bool addNeighboursToOpenList();
            bool addToOpenList(const int pos);
      public:
            NodeMap(const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
            const int nStartX, const int nStartY,const int nTargetX, const int nTargetY);
            ~NodeMap(){delete G; delete parent; delete map;};
            bool step();
            int fillOutput(int* pOutBuffer, const int nOutBufferSize);
};

#endif
