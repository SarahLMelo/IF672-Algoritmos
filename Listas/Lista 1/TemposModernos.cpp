#include <iostream>

using namespace std;


struct ii{ //Par de inteiros
    int id, processingTime;
};

struct node{
        ii task = {-1, 0};
        node *next = nullptr;
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
                delete erasing;
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

void processor(queue *W, int N){
    if(W->size==0){
        cout << "PROC -1 -1\n";
    }
    else{
        W->head.next->task.processingTime-=N;
        if(W->head.next->task.processingTime<0) W->head.next->task.processingTime = 0;
        cout << "PROC " << W->head.next->task.id << " " << W->head.next->task.processingTime << "\n";
    }
}

void scheduler(queue *W, stack *O, queue *I, int N){
    bool doNotCircle = false;

    //Step 1
    if(W->size != 0){
        if(W->tail->task.processingTime<=0){
            O->push(W->tail->task);
            for(int i=0; i<W->size-1; i++) spin(W);
            W->pop();
        }
    }

    //Step 2
    if(I->size!=0){
        W->push(I->front());
        I->pop();
    }

    //Step 3
    processor(W, N);
    if(doNotCircle==false) spin(W);
}

int main(){

    int K; //Dura????o de um ciclo de processamento
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

    return 0;
}