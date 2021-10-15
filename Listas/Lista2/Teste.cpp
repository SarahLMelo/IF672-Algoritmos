#include <iostream>

using namespace std;

int score(string key){
    int points=0;
    for(int i= 0; i<key.size(); i++){
        points += (int)key[i]*i;
    }

    return points%103;
}

int main(){
    for(int i=0; i<3; i++){
        string command;
        cin >> command;
        cout << "score: " << score(command) << endl;
    }

    return 0;
}