#include"xcosy.h"
#include<cuda_runtime.h>
#include<string.h>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
#define BLOCK_DIM 1024
__global__
void xcosy(int lengthOfX,int lengthOfCon,float *x,float *y,float *con)
{
	int i=blockIdx.x*blockDim.x+threadIdx.x;
	if(i>=lengthOfCon) return;
	int offset=i*lengthOfX;
	float xy=0;
	float xx=0;
	float yy=0;
	for(int j=0;j<lengthOfX;j++){
		xy+=x[j]*y[j+offset];
		xx+=x[j]*x[j];
		yy+=y[j+offset]*y[j+offset];
	}
	con[i]=xy/(sqrt(xx)*sqrt(yy));
}
extern "C" void c_xcosy(int lengthOfX,int lengthOfCon,float *x,float *y,float *con)
{
	int nblocks=(lengthOfCon+BLOCK_DIM-1)/BLOCK_DIM;
	cout<<"using blocks="<<nblocks<<",and the thread is :"<<lengthOfCon<<endl;
	cout<<"start to exec xcos y"<<endl;
	xcosy<<<nblocks,BLOCK_DIM>>>(lengthOfX,lengthOfCon,x,y,con);
	cout<<"end of exec xcosy"<<endl;
	
}
