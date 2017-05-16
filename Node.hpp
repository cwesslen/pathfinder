//-------------------------------------------------------------------
// Node.h
// Header file
// Carl Wesslen 2016-12-09
//-----------------------------------------------------------------------------
#ifndef Nodeclass
#define Nodeclass
#include <vector>
using namespace std;

class Node{
      friend class NodeMap;
      private:
            int pos,G;
            bool pass,edge,closed,open;
            Node* parent;
      public:
            Node(){};
            Node(int id,bool ppass,bool pedge):pos(id),pass(ppass),edge(pedge),closed(false),open(false){};
		bool operator<=(const Node &n) const{return G<=n.G;};
		bool operator<(const Node &n) const{return G<n.G;};
		bool operator==(const Node &n) const{return pos==n.pos;};
		bool operator!=(const Node &n) const{return pos!=n.pos;};
};


#endif
