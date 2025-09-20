typedef struct HeapNode{
    int size;
    HeapNode *prev,*next;
    int free;
}HeapNode;
class HeapManager{
    HeapNode *head,*tail;
    HeapNode *findSplitableNode(int size);
    void * addToHeap(int size);
public:
    HeapManager();
    void* malloc(int size);
    void free(void *node);
    void displayState();
};
