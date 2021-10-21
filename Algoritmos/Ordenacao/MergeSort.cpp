#include <iostream>

using namespace std;

void merge(int array[], int left, int mid, int right){
    int sizeLeftArray = mid-left+1, sizeRightArray = right - mid;

    int *leftArray = new int[sizeLeftArray];
    int *rightArray = new int[sizeRightArray];

    for(int i=0; i<sizeLeftArray; i++){
        leftArray[i] = array[i+left];
    }
    for(int i=0; i<sizeRightArray; i++){
        rightArray[i] = array[i+mid+1];
    }

    int currentLeftArray = 0, currentRightArray = 0, indexMergedArray = left;

    while(currentLeftArray<sizeLeftArray && currentRightArray<sizeRightArray){
        if(leftArray[currentLeftArray]<=rightArray[currentRightArray]){
            array[indexMergedArray] = leftArray[currentLeftArray];
            currentLeftArray++;
        }
        else{
            array[indexMergedArray] = rightArray[currentRightArray];
            currentRightArray++;
        }

        indexMergedArray++;
    }

    while(currentLeftArray<sizeLeftArray){
        array[indexMergedArray] = leftArray[currentLeftArray];
        currentLeftArray++;
        indexMergedArray++;
    }

    while(currentRightArray<sizeRightArray){
        array[indexMergedArray] = rightArray[currentRightArray];
        currentRightArray++;
        indexMergedArray++;
    }

    delete [] leftArray;
    delete [] rightArray;
}

void mSort(int array[], int begin, int end){
    if(begin>=end) return;
    
    int mid = begin + ((end-begin)/2);

    mSort(array, begin, mid);
    mSort(array, mid+1, end);

    merge(array, begin, mid, end);

    return;
}

int main(){
    int N; cin >> N;
    int array[N];
    
    for(int i=0; i<N; i++){
        cin >> array[i];
    }

    for(int i=0; i<N; i++){
        cout << array[i] << " ";
    }
    cout << "\n";

    mSort(array, 0, N-1);

    for(int i=0; i<N; i++){
        cout << array[i] << " ";
    }
    cout << "\n";

    return 0;
}