#include <bits/stdc++.h>

using namespace std;

int bt(int M, int Q, vector <int> *P, int peguei, int pos, int gasto){
    int nPego = 0, pego = 0, achei = 0;

    if(pos+1<(*P).size()){
        nPego = bt(M, Q, P, peguei, pos+1, gasto);
        if(gasto+(*P)[pos] <= Q) pego = bt(M, Q, P, peguei+1, pos+1, gasto+(*P)[pos]);
    }
    else{
        if(Q >= gasto && M <= peguei) achei++;
        if(Q >= gasto+(*P)[pos] && M <= peguei+1) achei++;
    }

    achei += pego + nPego;

    return achei;
}

int main(){
    int K;
    cin >> K;

    for(int caso = 0; caso <K; caso++){
        int L, M, Q;
        cin >> L;

        vector <int> P(L);
        for(int i=0; i<L; i++){
            cin >> P[i];
        }

        cin >> M >> Q;

        cout << "caso " << caso << ": " << bt(M, Q, &P, 0, 0, 0) << "\n";
    }

    return 0;
}