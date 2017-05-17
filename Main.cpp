//-------------------------------------------------------------------
// Main.cpp
// Mainfil
// Carl Wesslen 2016-05-16
//-----------------------------------------------------------------------------
#include <iostream>
#include <ctime>
#include "FindPath.hpp"
using namespace std;

int main(){
      cout << "Test 1" << endl;
      int pOutBuffer[2000];
      int xSize=800;
      int ySize=800;
      int xStart=0;
      int yStart=0;
      int xTarget=xSize-1;
      int yTarget=ySize-1;
      unsigned char pMap[xSize*ySize];
      for(int i=0;i<xSize*ySize;++i) pMap[i]=1;


      clock_t start;
      double duration;
      start = clock();
      int steps = FindPath(xStart,yStart,xTarget,yTarget,pMap,xSize,ySize,pOutBuffer,2000);
      duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
      for(int i=1000;i<1020;i++) cout << pOutBuffer[i] << " ";
      cout << endl;
      cout<<"Time: "<< duration <<endl;
      cout << "steps: " << steps << endl;
      start = clock();
      steps = FindPath(xTarget,yTarget,xTarget,yTarget,pMap,xSize,ySize,pOutBuffer,2000);
      duration = (( clock() - start ) / (double) CLOCKS_PER_SEC);
      cout<<"Time: "<< duration <<endl;
      cout << "steps: " << steps << endl;
//      cout << "path: ";
//      for(int i=0;i<steps;i++) cout << pOutBuffer[i] << " ";
//      cout << endl;
      /*
      cout << "Test 2" << endl;
      unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
      int pOutBuffer[7];
      int steps= FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);
      cout << "steps: " << steps << endl;
      cout << "path: ";
      for(int i=0;i<steps&&i<14;i++) cout << pOutBuffer[i] << " ";
      cout << endl;
      */
}
