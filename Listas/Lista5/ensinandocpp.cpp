#include <bits/stdc++.h>

using namespace std;

/*
VECTOR
std::vector <int> batata(3, 0);
batata.push_back(5); 0 0 0 5
batata.pop_back();  0 0 0
batata.begin(); Endereço do inicio
batata.end(); Endereço do final
batata.size();

batata.front(); Variável no inicio
batata.back(); Variável no final


PAIR
std::pair <int, double> azul;
azul.first -> int
azul.second -> double
*/

int main(){
    int N;
    cin >> N;
    vector <vector <pair <int, double>>> G(N);

    int arestas;
    cin >> arestas;
    while(arestas--){
        int u, v; //u de onde sai e v para onde vai
        double dist;
        cin >> u >> v >> dist;
        G[u].push_back({v, dist});
    }

    return 0;
}