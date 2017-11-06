
#ifndef _FIGUE_H_
#define _FIGUE_H_
#include"xcosy.h"
#include<string.h>
#include<cstdlib>
#include<iostream>

using namespace std;
#define BLOCK_DIM 1024
typedef struct consequse
{
    int i;
    float value;
}scons,*pscons;
class figue
{
    public:
    figue(const char* _filename,int _n,int _m);

    ~figue();

    int getCosxy(const float* x,float *con);
    int getTop(const float*x,pscons c);//传入n大小的pcons地址
    int getm();
    int getn();


    private:

    char *filename;
    int m;
    int n;
    float* devFixedNum;
    float* devCon;
    float* devX;

    float* cons;
    int init();
};

#endif
