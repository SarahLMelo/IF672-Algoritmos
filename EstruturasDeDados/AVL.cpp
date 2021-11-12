#include <iostream>

using namespace std;

struct node{
    int value, bf, height;
    node *left = nullptr, *right = nullptr, *pai = nullptr;
};

class AVL{
    public:
        node *root;
        AVL(){
            root = nullptr;
        }

        ~AVL(){

        }

        void rotateleft(node *root){
            node *tempUp = root, *tempDown = root->right, *tempSubTree = root->right->left;

            root = tempDown;
            root->left = tempUp;
            root->left->right = tempSubTree;

            if(root->pai->left==tempUp) root->pai->left = tempDown;
            else root->pai->right = tempDown;

            return;
        }

        void rotateright(node *root){
            node *tempUp = root, *tempDown = root->left, *tempSubTree = root->left->right;

            tempDown->right = tempUp;
            tempDown->right->left = tempSubTree;

            if(root->pai->left==tempUp) root->pai->left = tempDown;
            else root->pai->right = tempDown;

            return;
        }

        void recalculateBF(node *root){
            node *temp = root;
            while(temp->pai!=nullptr){
                bool repeat = false;
                int hl = 0, hr = 0;

                if(temp->right!=nullptr) hr = temp->right->height+1;
                if(temp->left!=nullptr) hl = temp->left->height+1;
                
                temp->height = max(hr, hl);
                temp->bf = hr-hl;

                if(temp->bf > 1 || temp->bf < -1){
                    repeat = true;
                    if(hr>hl) rotateleft(temp);
                    else if(hr<hl) rotateright(temp);
                }

                if(repeat == false) temp = temp->pai;
            }

            return;
        }

        void insert(node *root, int value, node *pai){
            if(this->root == nullptr){
                this->root = new node;
                this->root->value = value;
                this->root->bf = 0;
                this->root->height = 0;
                return;
            }

            if(root == nullptr){
                root = new node;
                root->value = value;
                root->pai = pai;
                root->height = 0;
                
                if(value < root->pai->value) root->pai->left = root;
                else if(value > root->pai->value) root->pai->right = root;

                recalculateBF(root);
            }

            else{
                if(value < (*root).value){
                    insert((*root).left, value, root);
                }

                else if(value > (*root).value){
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
};

int main(){
    int N; cin >> N;
    AVL tree;

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

    return 0;
}