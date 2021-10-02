#include <iostream>

using namespace std;

struct node{
    int value = -1;
    node *next = NULL;
    node *previous = NULL;
    bool flag = false; //indicando se foi colocado nesse ciclo no head
};

class circularQueue{
    public:
        int size;
        node *head, *tail;

        circularQueue(){
            size = 0;

            head = new node();
            tail = new node();

            head->next = tail;
            head->previous = tail;
            tail->next = head;
            tail->previous = head;
        }
        
        ~circularQueue(){}

        void push(int x){
            if(size == 0) tail->value = x;
            else if(size == 1){
                if(tail->value==-1) tail->value = x;
                else{
                    head->value = x;
                    head->flag = true;
                }
            }
            else{
                node *temp = new node();
                temp->value = x;
                temp->next = head;
                temp->previous = tail;
                tail->next = temp;
                tail = temp;
            }
            size++;
        }

        node pop(){
            node output;

            output = *tail;
            tail->previous->next = head;

            size--;
            
            return output;
        }

        void spin(){
            tail = head;
            head = head->next;
        }
};