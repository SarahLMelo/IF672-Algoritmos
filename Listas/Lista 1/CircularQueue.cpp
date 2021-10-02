#include <iostream>

using namespace std;

struct node{
        int value = -1;
        node *next = NULL;
};

class circularQueue{
    private:
        int size, occupiedSpaces;
    public:
        node *head, *tail;
        circularQueue(){
            size = 2;
            occupiedSpaces = 0;

            head = new node();
            tail = new node();

            head->next = tail;
            tail->next = head;
        }

        ~circularQueue(){}

        bool isFull(){
            if(size == occupiedSpaces) return 1;
            else return 0;
        }

        bool isEmpty(){
            if(occupiedSpaces == 0) return 1;
            return 0;
        }

        void push(int x){
            if(isFull()){
                node *temp = new node();

                tail->next = temp;
                temp->next = head;
                temp->value = x;
                tail = temp;

                size++;
            }

            else{
                node *temp = head;
                while(temp->value != -1) temp = temp->next;
                temp->value = x;
            }

            occupiedSpaces++;
        }

        void circle(){
            tail = head;
            head = head->next;
        }

        int pop(){
            if(isEmpty()){
                cout << "ERROR\n";
                exit(1);
            }

            else{
                while(head->value==-1) circle();

                node temp = (*head);
                head->value = -1;
                
                occupiedSpaces--;
                return temp.value;
            }
        }

};

int main(){
    int N;
    cin >> N;

    circularQueue ccw;

    for(int i=0; i<N; i++){
        ccw.push(i);
    }

    while(!ccw.isEmpty()){
        cout << ccw.pop() << " ";
    }

    return 0;
}