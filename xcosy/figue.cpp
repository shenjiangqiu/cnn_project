#include "figue.h"
#include <cuda_runtime.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include<algorithm>
using namespace std;
#define BLOCK_DIM 1024
figue::figue(const char *_filename, int _n, int _m) : m(_m), n(_n)
{
	filename = new char[100];
	cons=new float[n];
	strcpy(filename, _filename);
	if (-1 == init())
	{
		cout << "init() failed!" << endl;
		exit(-1);
	}
}

figue::~figue()
{
	cudaFree(devFixedNum);
	cudaFree(devCon);
	cudaFree(devX);
	delete[] filename;
	delete[] cons;
}
int figue::getTop(const float* x,pscons c)
{
	
	this->getCosxy(x,cons);
	for(int i=0;i<n;i++)
	{
		c[i].i=i;
		c[i].value=cons[i];		
	}
	qsort(c,n,sizeof(scons),\
		[](const void* a,const void * b)
		{
			const pscons pa=(pscons)a;
			const pscons pb=(pscons)b;
			if(pa->value<pb->value) return 1;
			if(pa->value>pb->value) return -1;
			return 0;
		}
	);
	return 0;
	
}
int figue::getCosxy(const float *x, float *con)
{
	//int nblocks=(n+BLOCK_DIM-1)/BLOCK_DIM;
	if (cudaSuccess != cudaMemcpy(devX, x, sizeof(float) * m, cudaMemcpyHostToDevice))
	{
		cout << "memcopy x to devx failed!" << endl;
		return -1;
	}
	c_xcosy(m, n, devX, devFixedNum, devCon); //void c_xcosy(int lengthOfX,int lengthOfCon,float *x,float *y,float *con);
	if (cudaSuccess != cudaMemcpy(con, devCon, sizeof(float) * n, cudaMemcpyDeviceToHost))
	{
		cout << "memcopy devcon to con failed!" << endl;
		return -1;
	}
	return 0;
}
int figue::getm() { return m; }
int figue::getn() { return n; }
int figue::init()
{
	if (cudaSuccess != cudaMalloc((void **)&devFixedNum, sizeof(float) * m * n))
	{
		cout << "malloc devfixnum failed" << endl;
		return -1;
	}
	if (cudaSuccess != cudaMalloc(&devX, sizeof(float) * m))
	{
		cout << "malloc devx failed" << endl;
		return -1;
	}
	if (cudaSuccess != cudaMalloc(&devCon, sizeof(float) * n))
	{
		cout << "malloc devcon failed!" << endl;
		return -1;
	}

	float *fixedNum = new float[m * n];

	ifstream filein;
	filein.open(filename, ios_base::binary | ios_base::in);
	if (!filein.is_open())
	{
		cout << "openfile failed " << filename << endl;
		return -1;
	}
	filein.read((char *)fixedNum, sizeof(float) * m * n);
	filein.close();

	if (cudaSuccess != cudaMemcpy(devFixedNum, fixedNum, sizeof(float) * m * n, cudaMemcpyHostToDevice))
	{
		cout << "memcpy fixedNum to devFixedNum failed!" << endl;
		return -1;
	}
	delete[] fixedNum;
	fixedNum = NULL;

	return 0;
}
