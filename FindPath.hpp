//-------------------------------------------------------------------
// FindPath.cpp
// Function file
// Carl Wesslen 2016-05-16
//-----------------------------------------------------------------------------
#ifndef FindPathclass
#define FindPathclass
#include "NodeMap.hpp"
using namespace std;

int FindPath(const int nStartX, const int nStartY,
const int nTargetX, const int nTargetY,
const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
int* pOutBuffer, const int nOutBufferSize);

#endif
