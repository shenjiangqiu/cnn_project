#ifndef GETTOP_H
#define GETTOP_H
#include"/home/sjq/project1/xcosy/figue.h"
#define _IN_
#define _OUT_
class getTop
{
public:
    getTop(_IN_ char* filename,int _n,int _m);
    ~getTop();
    void getValue(_IN_ char* picturename,pscons mypscons);
private:
    figue *myfigue;
    int n;
    int m;
};

#endif // GETTOP_H
