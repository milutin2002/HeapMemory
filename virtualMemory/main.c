#include<stdio.h>
#include<memory.h>
#include<unistd.h>
#include<sys/mman.h>
#include <stdint.h>

static size_t system_page_size=0;


void mm_init(){

    system_page_size=getpagesize();
}

void * mm_get_new_vm_from_kernel(int units){
    char *a=mmap(0,units*system_page_size,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANON | MAP_PRIVATE,0,0);
    if(a==MAP_FAILED){
        return NULL;
    }
    memset(a,0,units*system_page_size);
    return a;
}

void  mm_get_return_vm_to_kernel(void *a,int units){
    if(munmap(a,units*system_page_size)){
        printf("Error with returning\n");
    }
}

typedef struct vm_family_t{
    char name[32];
    uint32_t size;
}vm_family_t;

typedef struct vm_families_t{
    struct vm_families_t *next;
    vm_family_t pages[0];
}vm_families_t;

static vm_families_t* first;

#define NUM_FAMILIES \
    (system_page_size - sizeof(vm_families_t))/sizeof(vm_family_t)

#define ITERATE_PAGE_FAMILY_BEGIN(ptr,curr) \
    for(curr=(vm_family_t*)&ptr->pages[0];curr->size && count<NUM_FAMILIES;curr++,count++){ 

#define ITERATE_PAGE_FAMILY_END }

void mm_create_new_page(char * name,uint32_t size){
    vm_family_t *family=NULL;
    vm_families_t *families=NULL;
    if(size>system_page_size){
        printf("Structure size is bigger than system page size\n");
        return;
    }
    if(!first){
        first=mm_get_new_vm_from_kernel(1);
        first->next=NULL;
        strncpy(first->pages->name,name,strlen(name));
        first->pages[0].size=size;
        return;
    }
    uint32_t count=0;
    ITERATE_PAGE_FAMILY_BEGIN(first,family)

        if(strncmp(family->name,name,20)!=0){
            count++;
            continue;
        }
    ITERATE_PAGE_FAMILY_END
    if(count==NUM_FAMILIES){
        vm_families_t* new_family=mm_get_new_vm_from_kernel(1);
        new_family->next=first;
    }
    else{
        strncpy(family->name,name,20);
        family->size=size;
    }
}


typedef struct a{
    int a,b;
}a;

int main(int argc,char *argv[]){
    mm_init();
    printf("VM page size = %d\n",system_page_size);
    void *a=mm_get_new_vm_from_kernel(4);
    void *b=mm_get_new_vm_from_kernel(3);
    printf("Addr1 %p Addr2 %p %d ",a,b,a-b);
    mm_create_new_page("a",sizeof(a));
    return 0;
}