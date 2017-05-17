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
            int mapWidth,mapHeight,target;
            bool* map;
            queue<int> openList;
            int closedNode;
            int* G;
            int* parent;
            bool addNeighboursToOpenList();
            bool addToOpenList(int pos);
      public:
            NodeMap(const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
            const int nStartX, const int nStartY,const int nTargetX, const int nTargetY);
            ~NodeMap(){delete G; delete parent; delete map;};
            bool step();
            bool openListIsEmpty(){return openList.empty();}
            int fillOutput(int* pOutBuffer, const int nOutBufferSize);
};

#endif
