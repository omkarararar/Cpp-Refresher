#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left = nullptr;
        right = nullptr;
    }
}

class BinaryTree{
    private:
        Node* root;
        void inorderTrav(Node* root){
            if(!root) return;
            inorderTrav(root->left);
            cout << root->data << " ";
            inorderTrav(root->right);
        }
    public:
        BinaryTree(){
            root=nullptr;
        }

        void insert(int val){
            Node *newNode=new Node(val);
            if(!root){
                root=newNode;
                return;     
            }   

            Node *queue[100];
            int front=0,rear=0;
            queue[rear++]=root;

            while(front<rear){
                Node *current=queue[front++];
                if(!current->left){
                    current->left=newNode;
                    return;
                }else{
                    queue[rear++]=current->left;
                }
                if(!current->right){
                    current->right=newNode;
                    return;
                }else{
                    queue[rear++]=current->right;
                }
            }
        }
        void printInorder(){
            inorderTrav(root);
            cout << endl;
        }
};
