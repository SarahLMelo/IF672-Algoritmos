#include <stdio.h>
#include <math.h>

int main(){
    int N,M,i,j, FoundIt;
    scanf("%d %d",&N, &M);
    double Matriz[N][M],raz;
    for(i=0; i<N;i++){
        for(j=0;j<M;j++){
            scanf("%lf", &Matriz[i][j]);
        }
    }

    for(i=0;i<N;i++){
        FoundIt=0;
        for(j=1;j<M && FoundIt!=1;j++){
            if(Matriz[i][j]!=-1){
                FoundIt=1;
                raz = pow(Matriz[i][j], 1.0/j);
                // printf("%lf %lf\n",Matriz[i][j],raz);
            }
        }
        for(j=0;j<M;j++){
            Matriz[i][j]=pow(raz,(double)j);
        }
    }

    for(i=0; i<N;i++){
        for(j=0;j<M;j++){
            printf("%0.lf", Matriz[i][j]);
            if(j<M-1){
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}