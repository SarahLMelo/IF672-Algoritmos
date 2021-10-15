#include <iostream>

using namespace std;

struct node{
        int value = -1;
        string key = "EMPTY";
        node *next = nullptr;
};

class Hash{
    private:
        int size;
        node *hashTable;

    public:
    Hash(int n){
        hashTable = new node[n];
        size = n;
    }

    ~Hash(){
        delete hashTable;
    }

    int generateIndex(string key){
        int points = 0;
        for(int i= 0; i<key.size(); i++){
            points += (int)key[i];
        }
        return points%size;
    }
    
    bool isOccupied(int index){
        if(hashTable[index].key == "EMPTY") return false;
        return true;
    }

    void chaining(int index, int value, string key){
        node *temp = hashTable[index].next;
        
        while(temp->next!=nullptr) temp = temp->next;

        temp->next = new node;
        temp = temp->next;
        temp->key = key;
        temp->value = value;
        
        return;
    }

    void linearProbing(int index, int value, string key){
        while(isOccupied(index)){
            index++;
            if(index == size) index = 0;
        }

        hashTable[index].key = key;
        hashTable[index].value = value;

        return;
    }

    void insert(int value, string key){
        int index = generateIndex(key);
        
        if(isOccupied(index)) linearProbing(index, value, key);
        else{
            hashTable[index].key = key;
            hashTable[index].value = value;
        }

        return;
    }

    int retrive(string key){
        int index = generateIndex(key);
        
        node *temp = &hashTable[index];
        while(key != temp->key){
            index++;
            if(index == size) index = 0;
            temp = &hashTable[index];
        }

        return temp->value;
    }
};

int main(){
    int n; cin >> n;
    Hash table(n);

    for(int i=0; i<5; i++){
        int value;
        string key;
        cin >> value >> key;
        table.insert(value, key);
    }

    for(int i=0; i<3; i++){
        string key;
        cin >> key;
        cout << table.retrive(key) << endl;
    }

    return 0;
}