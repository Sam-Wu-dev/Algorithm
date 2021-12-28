#include <iostream>
#define COUNT 5
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
    inorder_storage="DBEFAGHC";//test data 01
	preorder_storage = "ABDEFCGH";

    // inorder_storage =  "FCGAHDIBJEK";//test data 02
    // preorder_storage = "ACFGBDHIEJK";

    // inorder_storage =  "FBHEACG";//test data 03
    // preorder_storage = "EFBHGCA";
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
void SwapChild(node* root){
    if(root==NULL){
        return;
    }
    SwapChild(root->leftnode);
    SwapChild(root->rightnode);
    node* temp=root->leftnode;
    root->leftnode=root->rightnode;
    root->rightnode=temp;
    return;
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
void printBT(const std::string& prefix, const node* root, bool isLeft)
{
    if( root != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << root->value << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), root->leftnode, true);
        printBT( prefix + (isLeft ? "│   " : "    "), root->rightnode, false);
    }
}
void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->rightnode, space);
 
    // Print current node after space
    // count
    cout<<endl;
    for (int i = COUNT; i < space; i++)
        cout<<" ";
    cout<<root->value<<"\n";
 
    // Process left child
    print2DUtil(root->leftnode, space);
}
 
// Wrapper over print2DUtil()
void print2D(node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
void printdivider(int times){
    for(int i=0;i<times;i++){
        cout<<"-";
    }
    cout<<endl;
}
int main()
{
    init();//initialize setting
    node *root = new node;
    root=create_tree(0,inorder_storage.size(),0,preorder_storage.size());
    print2D(root);
    SwapChild(root);
    printdivider(20);
    print2D(root);

}