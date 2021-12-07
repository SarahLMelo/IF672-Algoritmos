#include <bits/stdc++.h>

using namespace std;

//ofstream myfile;

//#define cout myfile
#define inf 0x3f3f3f

vector<vector <pair <double, int>>> bellmanford(vector <vector <pair <int, double>>> g, int N, int start){
    vector<vector <pair <double, int>>> D(N, vector <pair <double, int>> (N, {inf, -1}));
    D[0][start].first = 0;

    for(int i=1; i<N; i++){
        D[i] = D[i-1];

        for(int u=0; u<N; u++){
            for(int e=0; e<g[u].size(); e++){
                int v = g[u][e].first;
                double w = g[u][e].second;

                if(D[i-1][u].first+w < D[i][v].first){
                    D[i][v].first = D[i-1][u].first+w;
                    D[i][v].second = u;
                }
            }
        }
    }

    for(int u=0; u<N; u++){
        for(int e=0; e<g[u].size(); e++){
            int v = g[u][e].first;
            double w = g[u][e].second;

            if(D[N-1][u].first+w < D[N-1][v].first){
                D[N-1][0].first = -1;
                D[N-1][0].second = -1;
            }
        }
    }


    return D;
}

void solve(vector <vector <pair <int, double>>> g, int N){
    vector<vector <pair <double, int>>> D = bellmanford(g, N, 0);

    if(D[N-1][0].first == -1){
        cout << "LOOP\n";
        return;
    }

    cout << D[N-1][N-1].first;
    stack <int> caminho;

    caminho.push(N-1);

    int percursor = D[N-1][N-1].second;
    while(percursor != -1){
        caminho.push(percursor);
        percursor = D[N-1][percursor].second;
    }

    while(!caminho.empty()){
        cout << " " << caminho.top();
        caminho.pop();
    }
    cout << "\n";

    return;
}

int main(){
    //myfile.open("saida.txt");

    int T;
    cin >> T;
    while(T--){
        int N; //Numero de Vertices
        cin >> N;

        vector <pair <int, int>> pontos(N); //Posição dos vértices
        for(int i=0; i<N; i++){
            cin >> pontos[i].first >> pontos[i].second;
        }

        int M; //Número de Moedas
        cin >> M;
        set <int> coins; // indices dos moedas
        for(int i=0; i<M; i++){
            int n;
            cin >> n;
            coins.insert(n);
        }

        vector <vector <pair <int, double>>> graph(N); //Grafo
        for(int i=0; i<N; i++){
            int Dj;
            cin >> Dj;
            for(int j=0; j<Dj; j++){
                int indexY;
                cin >> indexY;

                double energy = (pontos[i].first - pontos[indexY].first)*(pontos[i].first - pontos[indexY].first) + (pontos[i].second - pontos[indexY].second)*(pontos[i].second - pontos[indexY].second);
                if(coins.find(indexY)!=coins.end()) energy = - energy;

                graph[i].push_back({indexY, energy});
            }
        }

        solve(graph, N);

    }

    //myfile.close();
    return 0;
}