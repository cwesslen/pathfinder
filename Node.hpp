//-------------------------------------------------------------------
// Node.h
// Header file
// Carl Wesslen 2016-12-09
//-----------------------------------------------------------------------------
#ifndef Nodeclass
#define Nodeclass
using namespace std;

class Node{
      friend class NodeMap;
      private:
            int pos,G;
            bool edge,closed,open;
            Node* parent;
      public:
            Node(){};
            Node(int id,bool ppass,bool pedge):pos(id),closed(ppass),edge(pedge),open(false){};
		bool operator!=(const Node &n) const{return pos!=n.pos;};
};


#endif
