#include <iostream>

using namespace std;

class Heap{
    private:
        int size;
        int occupied;

    public:
    int *arr;
    Heap(){  //Constructor
        size = 0;
        arr = new int[1];
        occupied = 0;
    }

    ~Heap(){ //Destructor
        delete[] arr;
    }

    void increaseHeap(){ //Increasing vector size
        int *temp = arr;
        int oldSize = size;
        if(size == 0){
            size = 1;
            arr = new int[2];

            delete[] temp;
            return;
        }

        size += (size*2);
        arr = new int[size+1];

        for(int i=1; i<=oldSize; i++){
            arr[i] = temp[i];
        }

        delete[] temp;
        return;
    }

    void add(int n){ //Adding something to the heap
        if(occupied == size) increaseHeap();
        occupied++;

        arr[occupied] = n;

        //Checking if it need to change order
        int parent = occupied/2, pos = occupied;

        //Checking the priority between parent and leaf
        while(arr[pos] > arr[parent] && occupied >1){
            arr[pos] ^=arr[parent];
            arr[parent] ^=arr[pos];
            arr[pos] ^=arr[parent];
        }

        return;
    }

    int top(){
        return arr[1];
    }

    int remove(){
        //First Step -> Swap
        if(occupied>1){
            arr[occupied]^=arr[1];
            arr[1]^=arr[occupied];
            arr[occupied]^=arr[1];
        }

        //Second Step -> Making the priority right
        if(occupied>2){
            int parent = 1, leaf1 = 2, leaf2 = 3;

            while((arr[leaf1] >= arr[parent] && leaf1 < occupied) || (arr[leaf2] >= arr[parent] && leaf2 < occupied)){

                if(arr[leaf1]>arr[leaf2]){
                    arr[leaf1] ^=arr[parent];
                    arr[parent] ^=arr[leaf1];
                    arr[leaf1] ^=arr[parent];

                    parent = leaf1;
                    leaf1 = 2*leaf1;
                    leaf2 = 2*leaf1+1;
                }

                else{
                    arr[leaf2] ^=arr[parent];
                    arr[parent] ^=arr[leaf2];
                    arr[leaf2] ^=arr[parent];

                    parent = leaf2;
                    leaf1 = 2*leaf2;
                    leaf2 = 2*leaf2+1;
                }
            }
        }

        //Third step ->Take the last element out of the heap
        occupied--;
        return arr[occupied+1];
    }
};

int main(){
    int N;
    Heap test;
    cin >> N;

    for(int i=0; i<N; i++){
        int n;
        cin >> n;

        test.add(n);
    }

    for(int i=0; i<N; i++){
        cout << test.remove() << " ";
    }

    cout << endl;


    delete &test;
    return 0;
}