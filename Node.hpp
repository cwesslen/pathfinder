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
            int pos,G;
            bool open;
            Node* parent;
      public:
            Node(){};
            Node(int id,bool ppass):pos(id),open(ppass){};
		bool operator!=(const Node &n) const{return pos!=n.pos;};
};


#endif
