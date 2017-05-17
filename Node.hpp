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
            bool closed,open;
            Node* parent;
      public:
            Node(){};
            Node(int id,bool ppass):pos(id),closed(ppass),open(false){};
		bool operator!=(const Node &n) const{return pos!=n.pos;};
};


#endif
