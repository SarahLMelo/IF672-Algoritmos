#include <iostream>

using namespace std;
#define int long long int

struct node{
    int index, casos;
};

class Heap{
    private:
        int size;

    public:
    int occupied;
    node *arr;
    node **arrPos;

    Heap(){  //Constructor
        size = 0;
        arr = new node[1];
        occupied = 0;
        arrPos = new node* [1000000];
    }

    ~Heap(){ //Destructor
        delete[] arr;
        delete[] arrPos;
    }

    void increaseHeap(){ //Increasing vector size
        node *temp = arr;
        int oldSize = size;
        if(size == 0){
            size = 1;
            arr = new node[2];

            delete[] temp;
            return;
        }

        size += (size*2);
        arr = new node[size+1];

        for(int i=1; i<=oldSize; i++){
            arr[i] = temp[i];
            arrPos[arr[i].index] = arr+i;
        }

        delete[] temp;
        return;
    }

    void add(int index, int casos){ //Adding something to the heap
        if(occupied == size) increaseHeap();
        occupied++;

        arr[occupied].index = index;
        arrPos[index] = arr+occupied;
        arr[occupied].casos = casos;

        //Checking if it need to change order
        int parent = occupied/2, pos = occupied;

        //Checking the priority between parent and leaf
        while(arr[pos].casos >= arr[parent].casos && occupied >1){
            if(arr[pos].casos != arr[parent].casos || arr[pos].index>arr[parent].index){
                node temp = arr[pos];
                arr[pos] =arr[parent];
                arr[parent] = temp;

                arrPos[arr[parent].index] = arr+parent;
                arrPos[arr[pos].index] = arr+pos;
            }
            pos = parent;
            parent = pos/2;
            if(parent == 0) break;
        }

        return;
    }

    node* top(){
        return &arr[1];
    }

    void orderUp(int pos){
        int parent = pos/2;

        while(parent !=0 && arr[pos].casos >= arr[parent].casos && occupied >1){
            if(arr[pos].casos != arr[parent].casos || arr[pos].index>arr[parent].index){
                node temp = arr[pos];
                arr[pos] =arr[parent];
                arr[parent] = temp;

                arrPos[arr[parent].index] = arr+parent;
                arrPos[arr[pos].index] = arr+pos;
            }
            pos = parent;
            parent = pos/2;
        }
        
        return;
    }

    void orderDown(int parent){
        int leaf1 = parent*2, leaf2 = leaf1+1;

        while((leaf1<=occupied && arr[parent].casos<=arr[leaf1].casos) || (leaf2<=occupied && arr[parent].casos<=arr[leaf2].casos)){
            if(leaf1<=occupied && (arr[leaf1].casos>arr[leaf2].casos) || (arr[leaf1].casos==arr[leaf2].casos && arr[leaf1].index > arr[leaf2].index)){
                node temp = arr[parent];
                arr[parent] = arr[leaf1];
                arr[leaf1] = temp;

                arrPos[arr[parent].index] = arr+parent;
                arrPos[arr[leaf1].index] = arr+leaf1;

                parent = leaf1;
                leaf1 = 2*parent;
                leaf2 = 2*parent+1;

                if(leaf1>occupied) break;
            }
            else if(leaf2<=occupied){
                node temp = arr[parent];
                arr[parent] = arr[leaf2];
                arr[leaf2] = temp;

                arrPos[arr[parent].index] = arr+parent;
                arrPos[arr[leaf2].index] = arr+leaf2;

                parent = leaf2;
                leaf1 = 2*parent;
                leaf2 = 2*parent+1;

                if(leaf1>occupied) break;
            }
            else break;
        }
        
        return;
    }

    void remove(int index){
        node *toRemove = arrPos[index];
        (*toRemove) =  arr[occupied];
        arrPos[arr[occupied].index] = toRemove;

        orderUp(toRemove-arr);
        orderDown(toRemove-arr);

        occupied--;
        return;
    }

    int increaseCases(int n, int index){
        node *temp = arrPos[index];
        (*temp).casos += n;
        int casosTotais = (*temp).casos;

        orderUp(temp-arr);

        return casosTotais;
    }

    int decreaseCases(int n, int index){
        node *temp = arrPos[index];

        (*temp).casos -= n;
        if((*temp).casos<0) (*temp).casos = 0;
        int casosTotais = (*temp).casos;

        orderDown(temp-arr);

        return casosTotais;
    }

    int pay(int R){
        int amount = 0;

        while(R-- && arr[1].casos >0){
            decreaseCases(1, arr[1].index);
            amount++;
        }

        return amount;
    }
};

#undef int
int main(){

    #define int long long int

    int N;
    Heap queue;

    cin >> N;
    for(int i=0; i<N; i++){
        int cases;
        cin >> cases;
        queue.add(i, cases);
    }

    string command;
    cin >> command;

    while(command != "END"){
        if(command == "NEW"){
            int index, cases;
            cin >> index >> cases;

            queue.add(index, cases);
            cout << queue.top()->index << " " << queue.top()->casos << "\n";
        }

        else if(command == "DEL"){
            int index;
            cin >> index;

            queue.remove(index);
            if(queue.occupied != 0) cout << queue.top()->index << " " << queue.top()->casos << "\n";
            else cout << "-1 -1\n";
        }

        else if(command == "IN"){
            int index, cases;
            cin >> index >> cases;
            cout << queue.increaseCases(cases, index) << "\n";
        }

        else if(command == "OUT"){
            int index, cases;
            cin >> index >> cases;
            cout << queue.decreaseCases(cases, index) << "\n";
        }
        else if(command == "PAY"){
            int resources;
            cin >> resources;
            cout << queue.pay(resources) << "\n";
        }



        cin >> command;
    }

    int totalCases = 0;
    for(int i=1; i<=queue.occupied; i++){
        totalCases += queue.arr[i].casos;
    }

    cout << totalCases << "\n";

    return 0;
}