#include <stdio.h>

int main(){
    int N, K, P;
    scanf("%d%d%d", &N, &K, &P);
    int primos[100000], nPrimos = 0, ans, Q = 0, flagAchei = 0;

    for(int i = 3; i<=K; i+=2){
        int nEhPrimo = 0;
        for(int j = 0; j<nPrimos && nEhPrimo == 0; j++) if(i%primos[j]==0) nEhPrimo = 1;

        if(nEhPrimo==0){
            primos[nPrimos] = i;
            nPrimos++;
        }
    }

    for(int i = N; i<K; i++){
        int nFacPrimos = 0, flagFatorRepitido = 0;
        for(int j = 0; j<nPrimos && flagFatorRepitido == 0; j++){
            if(i%primos[j]==0){
                nFacPrimos++;
                if((i/primos[j])%primos[j]==0) flagFatorRepitido = 1;
            }
        }
        if(nFacPrimos == P && flagFatorRepitido == 0){
            if(flagAchei == 0){
                flagAchei = 1;
                ans = i;
            }
            else Q++;
            //printf("%d\n", i);
        }
    }

    if(flagAchei == 0) printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    else printf("%d %d\n", ans, Q);

    return 0;
}