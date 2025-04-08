#include "./manager.h"
#include <cstddef>
#include <unistd.h>
HeapManager::HeapManager(){
    this->head=this->tail=nullptr;
}

void * HeapManager::malloc(int size){
    HeapNode *split=findSplitableNode(size);
    if(split==nullptr){
        return addToHeap(size);
    }
    int newNodeSize=split->size-sizeof(HeapNode)-size;
    split->size=size;
    split->free=0;
    HeapNode * next=split->next;
    char *data=(char *)(split+1);
    HeapNode *newNode=(HeapNode *)(data+size);
    newNode->size=newNodeSize;
    newNode->free=1;
    split->next=newNode;
    newNode->prev=split;
    newNode->next=next;
    if(next!=nullptr){
        next->prev=split;
    }
    else{
        tail=newNode;
    }
    return split+1;
}
void HeapManager::free(void *node){
    if(node>sbrk(0)){
        return;
    }
    HeapNode *prev=nullptr,*curr=(HeapNode*)node;
    curr=curr-1;
    prev=curr->prev;
    if(curr!=nullptr && curr+1==node){
        HeapNode *next=curr->next;
        int freeBlockSize=0;
        if(next!=nullptr && next->free){
            freeBlockSize+=sizeof(HeapNode)+next->size;
            next=next->next;
        }
        if(prev!=nullptr && prev->free){
            freeBlockSize+=sizeof(HeapNode)+curr->size;
            curr=prev;
        }
        curr->free=1;
        curr->size+=freeBlockSize;
        curr->next=next;
        if(next!=nullptr){
            next->prev=curr;
        }
        if(curr->next==nullptr){
            this->tail=curr;
        }
    }
}
HeapNode * HeapManager::findSplitableNode(int size){
    if(head==nullptr){
        return nullptr;
    }
    HeapNode *curr=head;
    while(curr!=nullptr){
        if(curr->free && curr->size>=size+sizeof(HeapNode)){
            return curr;
        }
        curr=curr->next;
    }
    return nullptr;
}
void * HeapManager::addToHeap(int size){
    void *node=sbrk(0);
    sbrk(sizeof(HeapNode)+size);
    HeapNode *newNode=(HeapNode *)node;
    newNode->next=nullptr;
    newNode->size=size;
    newNode->free=0;
    if(head==nullptr){
        this->head=this->tail=newNode;
        this->head->next=nullptr;
        this->head->prev=nullptr;
        return newNode+1;
    }
    tail->next=newNode;
    newNode->prev=tail;
    tail=tail->next;
    return newNode+1;
}