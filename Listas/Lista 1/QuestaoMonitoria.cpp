#include <iostream>

using namespace std;


int binarySearch(int array[], int l, int r, int k){
    if(r==l-1 || r==l){
        if(array[l]==k){
            if(r==l) return 1;
            else if(array[r]==k) return 2;
        }
        else if(array[r]==k) return 1;
        else return -1;
    }
    int m = (l+r)/2, maior, menor;
    if(array[m]==k){
        menor = binarySearch(array, l, m, k);
        maior = binarySearch(array, m+1, r, k);
        if(maior==-1) maior = menor;
    }
    else if(array[m]>k){
        maior = binarySearch(array, l, m, k);
        menor = maior;
    }
    else{
        maior = binarySearch(array, m+1, r, k);
        menor = maior;
    }

    if(maior-menor<0) return -1;
    else return maior-menor;
}

int main(){
    int k, n, ans;
    cin >> k >> n;
    int array[n];

    for(int i=0; i<n; i++){
        cin >> array[i];
    }

    ans = binarySearch(array, 0, n-1, k);

    cout << ans << "\n";

    return 0;
}