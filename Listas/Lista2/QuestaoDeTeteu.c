#include <stdio.h>

int main(){
    int registrador[8], valor, comando;

    for(int i=0; i<8; i++) scanf("%d", &registrador[i]);

    comando = 2*2*2*registrador[0] + 2*2*registrador[1] + 2*registrador[2] + registrador[3];
    valor = 2*2*2*registrador[4] + 2*2*registrador[5] + 2*registrador[6] + registrador[7];

    while(comando!=15){
        if(comando == 0){
            for(int i=4; i<8; i++) scanf("%d", &registrador[i]);
            valor = 2*2*2*registrador[4] + 2*2*registrador[5] + 2*registrador[6] + registrador[7];
        }

        else if(comando == 2){
            printf("O registrador tem os seguintes valores:\nHigh: 2\nLow: %d\n", valor);
        }

        else if(comando == 5){
            printf("%d\n", valor*valor);
        }

        else if(comando == 8){
            printf("%X\n", valor);
        }

        else if(comando == 12){
            int multiplicador;
            scanf("%d", &multiplicador);
            printf("%d\n", valor*multiplicador);
        }

        else printf("ERRO: A instrucao nao existe.\n");

        for(int i=0; i<4; i++) scanf("%d", &registrador[i]);
        comando = 2*2*2*registrador[0] + 2*2*registrador[1] + 2*registrador[2] + registrador[3];
    }

    return 0;
}