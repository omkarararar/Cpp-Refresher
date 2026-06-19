#include<bits/stdc++.h>
using namespace std;

struct node{
    int data;
    node* left;
    node* right;
};

class BST{
    private:
        node* root;

        node* insert(node* root,int val){
            // node* newNode=new node{val,nullptr,nullptr};
            if(!root){    
                return new node{val,nullptr,nullptr};
            }
            if(val<root->data){
                root->left=insert(root->left,val);
            }else{
                root->right=insert(root->right,val);
            }
            return root;
        }

        void inorderTrav(node* root){
            if(!root) return;
            inorderTrav(root->left);
            cout << root->data << " ";
            inorderTrav(root->right);
        }

        void postorderTrav(node* root){
            if(!root) return;
            postorderTrav(root->left);
            postorderTrav(root->right);
            cout << root->data << " ";
        }

        void preorderTrav(node* root){
            if(!root) return;
            cout << root->data << " ";
            preorderTrav(root->left);
            preorderTrav(root->right);
        }

        vector<vector<int>> levelorderTrav(node* root){
            if(!root) return {};

            vector<vector<int>> result;
            queue<node*> q;
            q.push(root);
            while(!q.empty()){
                vector<int> level;
                int size=q.size();
                for(int i=0; i<size; i++){
                    node* current=q.front();
                    q.pop();
                    level.push_back(current->data);
                    if(current->left) q.push(current->left);
                    if(current->right) q.push(current->right);
                }
                result.push_back(level);
            }
            return result;
        }

    public:
        BST(){
            root=nullptr;
        }

        void insert(int val) {
            root = insert(root, val);
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
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    cout << "Inorder Traversal: ";
    bst.printInorder();
    cout << "Postorder Traversal: ";
    bst.printPostorder();
    cout << "Preorder Traversal: ";
    bst.printPreorder();
    cout << "Levelorder Traversal: ";
    auto levelorder = bst.printLevelorder();
    for(const auto& level : levelorder){
        for(int val : level){
            cout << val << " ";
        }
        cout << endl;
    }   
    return 0;
}