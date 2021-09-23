#include <iostream>
#include <cstring>

using namespace std;

//int dp[(int)2*10^5];

int fib(int i){
    //if(dp[i]!=-1) return dp[i];
    if(i==0) return /*dp[i] =*/ 0;
    if(i==1) return /*dp[i] =*/ 1;

    return /*dp[i] =*/ fib(i-1)+fib(i-2);
}

int main(){
    //memset(dp, -1, sizeof(dp));
    
    int n;
    cin >> n;
    cout << fib(n-1) << "\n";

    return 0;
}