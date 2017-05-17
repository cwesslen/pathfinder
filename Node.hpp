//-------------------------------------------------------------------
// Node.h
// Header file
// Carl Wesslen 2016-05-16
//-----------------------------------------------------------------------------
#ifndef Nodeclass
#define Nodeclass
using namespace std;

class Node{
      friend class NodeMap;
      private:
            int pos,G,parent;
            bool passable;
      public:
            Node(){};
            Node(int id,bool ppass):pos(id),passable(ppass){};
};


#endif
