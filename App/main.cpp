#include <cstdlib>
#include <iostream>
#include "../Manager/manager.h"
using namespace std;

int main(int argc,char *argv[]){
    HeapManager m;
    int *a=(int*)m.malloc(4*sizeof(int));
    m.displayState();
    int *b=(int*)m.malloc(6*sizeof(int));
    m.displayState();
    m.free(a);
    m.displayState();
    m.free(b);
    m.displayState();
    void *c=m.malloc(5);
    m.displayState();
    void *d =m.malloc(6);
    m.displayState();
    m.free(d);
    m.displayState();
    void * f=m.malloc(3);
    m.displayState();
    void *x=m.malloc(100);
    m.displayState();
    m.free(c);
    m.displayState();
    m.free(f);
    m.displayState();
    void *g=m.malloc(1000);
    m.displayState();
    m.free(g);
    m.displayState();
    void *z =m.malloc(160);
    m.displayState();
    void *y=m.malloc(240);
    m.displayState();
    m.free(z);
    m.displayState();
    m.free(x);
    m.displayState();
    m.free(y);
    m.displayState();
    return 0;
}