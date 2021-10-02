#include <iostream>

using namespace std;

struct node{
        int value = 0;
        node *next = NULL;
};

class stack{
    private:
        int size;
        node *tail;
        node head;
    public:
        stack(){
            tail = &head;
            size = 0;
        }

        ~stack(){
        }

        void push(int x){
            node *temp = new node();
            if(size==0) head.next = temp;
            temp->value = x;
            tail->next = temp;
            tail = temp;
            size++;
        }
        int size(){
            return this->size;
        }
        void pop(){
                node *prox = head.next;
                if(size==0){
                    cout << "ERROR: STACK UNDERFLOW\n";
                    return;
                }
                if(size==1){
                    size--;
                    head.next = NULL;
                    return;
                }
                while(prox->next!=tail){
                    prox = prox->next;
                }
                prox->next = NULL;
                tail = prox;
                size--;
        }

        int top(){
            return tail->value;
        }
};

int main(){
    int n;
    cin >> n;

    stack pilha;
    for(int i=0; i<n; i++){
        pilha.push(i);
    }
    for(int i = 0; i<n; i++){
        cout << pilha.top() << " ";
        pilha.pop();
    }

    return 0;
}