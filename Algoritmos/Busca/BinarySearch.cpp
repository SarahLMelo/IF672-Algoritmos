#include <iostream>

//Não debugado

int binarySearch(int array[], int k, int n){
    int pos, l = 0, r = n-1;

    while(r - l>1){
        int m = (l+r)/2;
        if(array[m]>=k){
            r = m;
        }
        else if(array[m]<k){
            l = m+1;
        }
    }

    if(l!=r){
        if(array[l]==k) pos = l;
        else if(array[r]==k) pos = r;
        else -1;
    }
    else{
        if(array[l]==k) pos = l;
        else -1;
    }

    return pos;
}