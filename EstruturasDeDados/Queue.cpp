#include <iostream>

using namespace std;

struct node{
        int value = 0;
        node *next = NULL;
};

class queue{
    private:
        node *tail;
        node head;
    public:
        int size;
        queue(){
            tail = &head;
            size = 0;
        }

        ~queue(){
        }

        void push(int x){
            node *temp = new node();
            if(size==0) head.next = temp;
            temp->value = x;
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

        int front(){
            return head.next->value;
        }
};

int main(){
    int n;
    cin >> n;

    queue fila;
    for(int i=0; i<n; i++){
        fila.push(i);
    }
    for(int i = 0; i<n; i++){
        cout << fila.front() << " ";
        fila.pop();
    }

    return 0;
}