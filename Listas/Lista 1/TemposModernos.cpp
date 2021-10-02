#include <iostream>
#include <fstream>

using namespace std;

#define cout myfile

ofstream myfile;

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

class stack{
    private:
        node *tail;
        node head;
    public:
    int size;
        stack(){
            tail = &head;
            size = 0;
        }

        ~stack(){
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

        ii top(){
            return tail->task;
        }
};

void spin(queue *W){
    if(W->size==0 || W->size==1) return;
    ii element;
    element = W->head.next->task;
    W->pop();
    W->push(element);
}

void processor(queue *W, int N, bool flag){
    if(W->size==0){
        cout << "PROC -1 -1\n";
    }
    else if(W->size==1 || flag == true){
        W->head.next->task.processingTime-=N;
        if(W->head.next->task.processingTime<0) W->head.next->task.processingTime = 0;
        cout << "PROC " << W->head.next->task.id << " " << W->head.next->task.processingTime << "\n";
    }
    else{
        W->head.next->next->task.processingTime-=N;
        if(W->head.next->next->task.processingTime<0) W->head.next->next->task.processingTime = 0;
        cout << "PROC " << W->head.next->next->task.id << " " << W->head.next->next->task.processingTime << "\n";
    }
}

void scheduler(queue *W, stack *O, queue *I, int N){
    bool flag = false, someoneLeft = false;

    //Step 1
    if(W->size != 0){
        if(W->head.next->task.processingTime<=0){
            O->push(W->head.next->task);
            W->pop();
            someoneLeft = true;
        }
    }

    //Step 2
    if(I->size!=0){
        if((W->size==0) || someoneLeft == true){
            W->push(I->front());
            I->pop();
        }
        else {
            ii element = W->front();
            W->head.next->task = I->front();
            I->pop();
            W->push(element);
        }
    }

    //Step 3
    processor(W, N, someoneLeft);
    spin(W);
}

int main(){
    myfile.open ("out.txt");

    int K; //Duração de um ciclo de processamento
    cin >> K;
    cin.ignore(1);
    string comando;
    cin >> comando;
    queue inputQueue;
    stack outputStack;
    queue workQueue;

    while(comando!="END"){
        if(comando == "LOAD"){
            ii task;
            cin >> task.id >> task.processingTime;
            inputQueue.push(task);
            cin.ignore(1);
        }

        else if(comando == "UNLD"){
            cout << "UNLD " << outputStack.top().id << "\n";
            outputStack.pop();
        }
        
        else if(comando == "PROC"){
            scheduler(&workQueue, &outputStack, &inputQueue, K);
        }

        cin>>comando;
    }

    myfile.close();
    return 0;
}