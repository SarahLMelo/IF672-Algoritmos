#include <iostream>

using namespace std;

struct ii{ //Par de inteiros
    int id, processingTime;
};

struct node{
        ii task = {-1, 0};
        node *next = NULL;
};

class queue{
    public:
        int size;
        node head;
        node *tail;
        queue(){
            tail = &head;
            size = 0;
        }

        ~queue(){
        }

        void push(ii x){
            node *temp = new node();
            if(size==0) head.next = temp;
            temp->task = x;
            tail->next = temp;
            tail = temp;
            size++;
        }

        void pop(){
                node *erasing = head.next;
                if(size==0){
                    cout << "ERROR: QUEUE UNDERFLOW\n";
                    return;
                }
                if(size==1){
                    size--;
                    head.next = NULL;
                    return;
                }
                head.next = head.next->next;
                size--;
        }

        ii front(){
            return head.next->task;
        }
};