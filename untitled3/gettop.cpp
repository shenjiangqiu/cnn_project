#include "gettop.h"
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<iostream>
#include<unistd.h>
using namespace std;
getTop::getTop(char*filename, int _n, int _m):n(_n),m(_m)
{

    myfigue=new figue(filename,_n,_m);

}
getTop::~getTop()
{
    delete myfigue;
}
void getTop::getValue(char *picturename, pscons mypscons)
{

    float *x=new float[m];//----------------------------------------new!!!
    int sfd=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9999);
    inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);

    int rt;
    int n=0;
    int size=m*sizeof(float);

    connect(sfd,(sockaddr*)&addr,sizeof(addr));
    send(sfd,picturename,strlen(picturename),0);



    while(n<size)
    {
        rt=recv(sfd,((char*)x)+n,size-n,0);
        cout<<"rt="<<endl;
        n=n+rt;
        cout<<"n="<<n<<endl;
    }
    close(sfd);

    myfigue->getTop(x,mypscons);
    delete[] x;//---------------------------------------------------delete!!
}
