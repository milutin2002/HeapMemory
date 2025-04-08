#include <cstdlib>
#include <iostream>
#include "../Manager/manager.h"
using namespace std;

int main(int argc,char *argv[]){
    HeapManager m;
    int *a=(int*)m.malloc(4*sizeof(int));
    for (int i=0;i<4;i++) {
        a[i]=i;
    }
    for (int i=0;i<4;i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    int *b=(int*)m.malloc(6*sizeof(int));
    for(int i=0;i<6;i++){
        b[i]=i*2;
    }
    for (int i=0;i<6;i++) {
        cout<<b[i]<<" ";
    }
    m.free(a);
    m.free(b);
    void *c=m.malloc(5);
    void *d =m.malloc(6);
    m.free(d);
    void * f=m.malloc(3);
    m.malloc(100);
    m.free(c);
    m.free(f);
    return 0;
}