#include <stdio.h>
#include <math.h>

#define ll long long

int main(){
    int n, m;
    scanf("%d %d", &n, &m);

    ll int matriz[n][m];
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%lld",&matriz[i][j]);
        }
    }

    for(int i=0; i<n; i++){
        int findTheNumber = 0;
        matriz[i][0] = 1;
        double razao;
        
        for(int j=1; j<m && findTheNumber == 0; j++){
            if(matriz[i][j]!=-1){
                findTheNumber = 1;
                razao = (pow((double) matriz[i][j], (double)1/j));
            }
        }

        for(int j=1; j<m; j++){
            matriz[i][j] = pow(razao, j);
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m-1; j++){
            printf("%lld ", matriz[i][j]);
        }
        printf("%lld\n", matriz[i][m-1]);
    }

    return 1;
}