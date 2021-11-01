#include <iostream>

using namespace std;

struct node{
    int value;
    node *left = nullptr, *right = nullptr, *pai = nullptr;
};

class BST{
    public:
        node *root;
        BST(){
            root = nullptr;
        }

        ~BST(){

        }

        void insert(node *root, int value, node *pai){
            if(this->root == nullptr){
                this->root = new node;
                this->root->value = value;
                return;
            }

            if(root == nullptr){
                root = new node;
                root->value = value;
                root->pai = pai;
                
                if(value < root->pai->value) root->pai->left = root;
                else if(value > root->pai->value) root->pai->right = root;

                return;
            }

            else{
                if(value == (*root).value) return;

                else if(value < (*root).value){
                    insert((*root).left, value, root);
                }

                else{
                    insert((*root).right, value, root);
                }
            }

            return;
        }

        node *search(node *root, int value){
            if(root == nullptr || value == (*root).value) return root;

            else if(value < (*root).value){
                return search((*root).left, value);
            }

            else{
                return search((*root).right, value);
            }
        }

        void remove(node *root, int value){
            node *aRemover = search(root, value);

            if((*aRemover).left == nullptr && (*aRemover).right == nullptr){ //folha
                if((*aRemover).pai == nullptr){
                    this->root = nullptr;
                }
                else{
                    if((*(*aRemover).pai).left == aRemover){
                        (*(*aRemover).pai).left = nullptr;
                    }
                    else{
                        (*(*aRemover).pai).right = nullptr;
                    }
                    delete aRemover;
                }
                return;
            }

            else if((*aRemover).left == nullptr){ //Só tem filhos a direita
                if((*(*aRemover).pai).left == aRemover){
                   aRemover->pai->left = aRemover->right;
                }
                else{
                    aRemover->pai->right = aRemover->right;
                }
                delete aRemover;
                return;
            }

            else if((*aRemover).right == nullptr){ //Só tem filhos a esquerda
                if((*(*aRemover).pai).left == aRemover){
                   aRemover->pai->left = aRemover->left;
                }
                else{
                    aRemover->pai->right = aRemover->left;
                }
                delete aRemover;
                return;
            }

            else{ //Tem filhos dos oois lados
                node *temp = aRemover->right; 
                while(temp->left!=nullptr) temp = temp->left;

                aRemover->value = temp->value;
                if(temp->right != nullptr){
                    temp->pai->left = temp->right;
                }
                else{
                    temp->pai->left = nullptr;
                }

                delete temp;
            }
        }
};


int main(){
    int N; cin >> N;
    BST tree;

    for(int i=0; i<N; i++){
        int a;
        cin >> a;
        tree.insert(tree.root, a, nullptr);
    }

    int pesquisar; cin >> pesquisar;
    while(pesquisar--){
        int a; cin >> a;
        node *achado = tree.search(tree.root, a);
        if (achado != nullptr){
            cout << "Achei o valor: " << achado->value << "\n";
        }
        else{
            cout << "Nao achei esse valor\n";
        }
    }

    for(int i=0; i<N; i++){
        int a;
        cin >> a;
        tree.remove(tree.root, a);
    }

    return 0;
}