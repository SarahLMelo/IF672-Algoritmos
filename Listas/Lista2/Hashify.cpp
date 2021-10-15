#include <iostream>
#include <fstream>

using namespace std;

ofstream myfile;

#define cout myfile

struct node{
        int value = -1, playedTimes = 0;
        string key = "EMPTY";
};

class Hash{
    private:
        int size, occupiedSpace;
        node *hashTable;

    public:
    Hash(int n){
        hashTable = new node[n];
        size = n;
        occupiedSpace = 0;
    }

    ~Hash(){
        delete [] hashTable;
    }

    int generateIndex(string key){
        int points = 0;
        for(int i= 0; i<key.size(); i++){
            points += (int)key[i]*i;
        }
        return points%size;
    }
    
    bool isOccupied(int index){
        if(hashTable[index].value == -1) return false;
        return true;
    }

    int linearProbing(int index, int value, string key){
        while(isOccupied(index)){
            index++;
            if(index == size) index = 0;
        }

        hashTable[index].key = key;
        hashTable[index].value = value;

        return index;
    }

    void insert(int value, string key){
        increasingSize();

        int index = generateIndex(key);
        
        if(isOccupied(index)) index = linearProbing(index, value, key);
        else{
            hashTable[index].key = key;
            hashTable[index].value = value;
        }

        occupiedSpace++;

        cout << key << " " << index << endl;
        return;
    }

    node *retrive(string key){
        int index = generateIndex(key);
        
        node *temp = &hashTable[index];
        while(key != temp->key){
            index++;
            if(index == size){
                index = 0;
                temp = &hashTable[index];
            }
            else temp++;
        }

        return temp;
    }

    void increasingSize(){
        if(((float)occupiedSpace/(float)size) >= 0.5){
            node *newHashTable = new node[(size*2)+1];
            node *temp = hashTable;
            hashTable = newHashTable;

            cout << "Tamanho: " << size << " NovoTamanho: " << (size*2)+1;

            for(int i=0; i<size; i++){
                hashTable[i] = temp[i];
            }

            size = (size*2)+1;

            delete [] temp;
        }

        return;
    }
};

int main(){
    myfile.open("Saida.txt");
    int M;
    cin >> M;

    Hash playlist(M);

    string command;
    cin >> command;

    while(command!="END"){
        if(command=="ADD"){
            string key;
            int value;
            cin >> key >> value;

            playlist.insert(value, key);
        }

        else{
            node *music;
            string key;

            cin >> key;

            music = playlist.retrive(key);
            if(command == "PLAY") music->playedTimes++;

            cout << music->key << " " << (music->playedTimes)*(music->value) << endl;
        }


        cin >> command;
    }

    myfile.close();

    return 0;
}