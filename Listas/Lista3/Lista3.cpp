#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
ofstream myfile;
//#define cout myfile

struct node{
    int value, bf = 0x3f3f3f, height = -1;
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

        node *rotateleft(node *B){
            node *A = B->pai, *C = B->left;

            if(A->pai == nullptr){
                root = B;
                B->pai = nullptr;
            }
            else if(A->pai->right == A){
                A->pai->right = B;
                B->pai = A->pai;
            }
            else{
                A->pai->left = B;
                B->pai = A->pai;
            }

            A->pai = B;
            if(C!=nullptr)C->pai = A;

            B->left = A;
            A->right = C;
            
            return B;
        }

        node *rotateright(node *B){
            node *A = B->pai, *C = B->right;

            if(A->pai == nullptr){
                root = B;
                B->pai = nullptr;
            }
            else if(A->pai->right == A){
                A->pai->right = B;
                B->pai = A->pai;
            }
            else{
                A->pai->left = B;
                B->pai = A->pai;
            }

            A->pai = B;
            if(C!=nullptr)C->pai = A;

            B->right = A;
            A->left = C;
            
            return B;
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

        void printPostOrder(node *vis){
            if(vis->left!=nullptr){
                printPostOrder(vis->left);
            }
            if(vis->right!=nullptr){
                printPostOrder(vis->right);
            }
            cout << vis->value;
            if(vis!=root) cout << " ";
        }
};

int turnIntoE(BST *S){
    int l = 0;
    node *temp = S->root;
    while(temp->right != nullptr || temp->left!= nullptr){
        while(temp->right!=nullptr){
            temp = S->rotateleft(temp->right);
            l++;
        }
        temp = temp->left;
    }

    return l;
}

void etapa2(BST *S, BST *T, int *l, int *r, bool direction, node *visS, node *visT){ // 0 -> rotateright, 1-> rotateleft
    node *temp = visS;
    while(temp->value != visT->value){
        if(direction == 0){
            temp = S->rotateright(temp->left);
            (*r)++;
        }
        else{
            temp = S->rotateleft(temp->right);
            (*l)++;
        }
    }

    if(temp->left!=nullptr) etapa2(S, T, l, r, 0, temp->left, visT->left);
    if(temp->right!=nullptr) etapa2(S, T, l, r, 1, temp->right, visT->right);

    return;
}

int calculateHeight(node *vis){ //l-r
    if(vis->height != -1) return vis->height;

    if(vis->left==nullptr){
        if(vis->right == nullptr){
            vis->bf = 0;
            return vis->height = 0;
        }
        else{
            vis->height = (calculateHeight(vis->right))+1;
            vis->bf = 0 - vis->right->height - 1;
            return vis->height;
        }
    }

    else if(vis->right==nullptr){
        vis->height = (calculateHeight(vis->left))+1;
        vis->bf = (vis->left->height)+1;
        return vis->height;
    }

    vis->height = max(calculateHeight(vis->left), calculateHeight(vis->right))+1;
    vis->bf = vis->left->height - vis->right->height;

    return vis->height;
}

bool isAnAVL(node *vis){
    if((vis->bf)>1 || (vis->bf)<-1) return false;

    if(vis->left!=nullptr && isAnAVL(vis->left)==false) return false;
    if(vis->right!=nullptr && isAnAVL(vis->right)==false) return false;

    return true;
}

int main(){
    myfile.open("saida.txt");
    int N;

    while(cin >> N){
        BST S, T;
        int l=0, r=0;

        for(int i=0; i<N; i++){
            int temp;
            cin >> temp;

            S.insert(S.root, temp, nullptr);
        }

        l = turnIntoE(&S);

        for(int i=0; i<N; i++){
            int temp;
            cin >> temp;

            T.insert(T.root, temp, nullptr);
        };

        etapa2(&S, &T, &l, &r, 0, S.root, T.root);

        cout << l << " " << r << "\n";
        S.printPostOrder(S.root);
        cout << endl;

        calculateHeight(S.root);

        if(isAnAVL(S.root) == true) cout << "true\n\n";
        else cout << "false\n\n";
        
    }

    myfile.close();
    return 0;
}