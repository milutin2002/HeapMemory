#include<stdio.h>
#include<memory.h>
#include<unistd.h>
#include<sys/mman.h>

static size_t system_page_size=0;

void mm_init(){
    system_page_size=getpagesize();
}

static void * mm_get_new_vm_from_kernel(int units){
    char *a=mmap(0,units*system_page_size,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANON | MAP_PRIVATE,0,0);
    if(a==MAP_FAILED){
        return NULL;
    }
    memset(a,0,units*system_page_size);
    return a;
}

static void  mm_get_return_vm_to_kernel(void *a,int units){
    if(munmap(a,units*system_page_size)){
        printf("Error with returning\n");
    }
}

int main(int argc,char *argv[]){
    mm_init();
    printf("VM page size = %d\n",system_page_size);
    void *a=mm_get_new_vm_from_kernel(4);
    void *b=mm_get_new_vm_from_kernel(3);
    printf("Addr1 %p Addr2 %p %d ",a,b,a-b);
    return 0;
}