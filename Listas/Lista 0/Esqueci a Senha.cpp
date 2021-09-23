#include <iostream>

using namespace std;

void bt(string palavras[], int pos, int n, string comando, string formado){
    if(pos == comando.size()-1){
        if(comando[pos]=='#'){
            for(int i=0; i<10; i++){
                cout << formado << i << "\n";
            }
        }
        else{
            for(int i=0; i<n; i++){
                cout << formado+palavras[i] << "\n";
            }
        }
    }
    else{
        if(comando[pos]=='#'){
            for(int i=0; i<10; i++){
                char numero = i+48;
                
                bt(palavras, pos+1, n, comando, formado+numero);
            }
        }
        else{
            for(int i=0; i<n; i++){
                bt(palavras, pos+1, n, comando, formado+palavras[i]);
            }
        }
    }

    return;
}

int main(){
    int n;
    cin >> n;

    string palavras[n];
    for(int i=0; i<n; i++) cin >> palavras[i];

    cin.ignore(1);
    int Q = 100;
    while(Q--){
        string comando;
        cin >> comando;
        if(comando == "\0" || cin.eof()) break;
        bt(palavras, 0, n, comando, "");
    }

    return 0;
}