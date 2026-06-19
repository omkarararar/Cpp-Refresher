#include <iostream>
#include <bits/stdc++.h>
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
};

class BinaryTree{
    private:
        Node* root;
        void inorderTrav(Node* root){
            if(!root) return;
            inorderTrav(root->left);
            cout << root->data << " ";
            inorderTrav(root->right);
        }

        void postorderTrav(Node* root){
            if(!root) return;
            postorderTrav(root->left);
            postorderTrav(root->right);
            cout << root->data << " ";
        }

        void preorderTrav(Node* root){
            if(!root) return;
            cout << root->data << " ";
            preorderTrav(root->left);
            preorderTrav(root->right);
        }

        vector<vector<int>> levelorderTrav(Node* root){
            if(!root) return{};

            vector<vector<int>> res;

            queue<Node*> q;
            q.push(root);
            while(!q.empty()){
                int size=q.size();
                vector<int> level;
                for(int i=0;i<size;i++){
                    Node* front=q.front();
                    q.pop();
                    if(front->left) q.push(front->left);
                    if(front->right) q.push(front->right);
                    level.push_back(front->data);
                }            
                res.push_back(level);
            }
            return res;
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

            queue<Node*> queue; // Assuming a maximum of 100 nodes in the tree
            queue.push(root);

            while(!queue.empty()){
                Node *current=queue.front();
                queue.pop();
                if(!current->left){
                    current->left=newNode;
                    return;
                }else{
                    queue.push(current->left);
                }
                if(!current->right){
                    current->right=newNode;
                    return;
                }else{
                    queue.push(current->right);
                }
            }
        }
        void printInorder(){
            inorderTrav(root);
            cout << endl;
        }
        void printPostorder(){
            postorderTrav(root);
            cout << endl;
        }
        void printPreorder(){
            preorderTrav(root);
            cout << endl;
        }

        vector<vector<int>> printLevelorder(){
            return levelorderTrav(root);
        }
};

int main(){
    BinaryTree bt;
    bt.insert(1);
    bt.insert(2);
    bt.insert(3);
    bt.insert(4);
    bt.insert(5);
    
    cout << "Inorder Traversal: ";
    bt.printInorder();
    cout << "Postorder Traversal: ";
    bt.printPostorder();
    cout << "Preorder Traversal: ";
    bt.printPreorder();
    cout << "Levelorder Traversal: ";
    auto levelorder = bt.printLevelorder();
    for(const auto& level : levelorder){
        for(int val : level){
            cout << val << " ";
        }
        cout << endl;
    }   
    return 0;
}