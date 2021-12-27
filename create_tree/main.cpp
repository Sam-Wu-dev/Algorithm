#include <iostream>
using namespace std;
struct node
{
    char value;
    node *leftnode = NULL;
    node *rightnode = NULL;
};

int now_index;
string inorder_storage;
string preorder_storage;

void init()
{
    now_index=0;
    // inorder_storage="CBAEDGHFI";//test data 01
	// preorder_storage = "ABCDEFGHI";

    // inorder_storage =  "FCGAHDIBJEK";//test data 02
    // preorder_storage = "ACFGBDHIEJK";

    inorder_storage =  "FBHEACG";//test data 03
    preorder_storage = "EFBHGCA";
}

node* create_tree(int inorder_start,int inorder_end,int preorder_start,int preorder_end){
    if(inorder_start>=inorder_end){
        return NULL;
    }
    node* temp=new node;
    temp->value=preorder_storage[now_index++];
    if(preorder_start>=preorder_end){
        return temp;
    }
    int middle=-1;
    for(int i=inorder_start;i<inorder_end;i++){
        if(inorder_storage[i]==temp->value){
            middle=i;
            break;
        }
    }
    temp->leftnode=create_tree(inorder_start,middle,preorder_start+1,middle+1);
    temp->rightnode=create_tree(middle+1,inorder_end,middle+1,preorder_end);
    return temp;
}
void inorder_print(node *root)
{
    if (root != NULL)
    {
        inorder_print(root->leftnode);
        cout << root->value;
        inorder_print(root->rightnode);
    }
}
void preorder_print(node *root){
    if (root != NULL)
    {
        cout << root->value;
        preorder_print(root->leftnode);
        preorder_print(root->rightnode);
    }
}
int main()
{
    init();//initialize setting
    node *root = new node;
    root=create_tree(0,inorder_storage.size(),0,preorder_storage.size());
    cout<<"Inorder print:"<<endl;
    inorder_print(root);
    cout<<endl;
    cout<<"Preorder print:"<<endl;
    preorder_print(root);
}