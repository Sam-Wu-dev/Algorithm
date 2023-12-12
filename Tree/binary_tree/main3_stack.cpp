#include <iostream>
#include <stack>

using namespace std;

int total = 0;

struct Node {
	int value;
	Node* leftNode;
	Node* rightNode;
};

//創建節點
Node* createNode(int value);
//前序遍歷輸出每個節點
void preOrderprint(Node*& root);
//新增節點
void insertNode(Node*& node, int value);
//取得節點最大值
Node*& getMaximum(Node*& node);
//取得節點最小值
Node*& getMinimum(Node*& node);
//刪除節點
void deleteNode(Node*& node);
//刪除查找到的節點
bool deleteBST(Node*& node, int value);
//獲取樹全部節點的總共和
int getTotalNodeValue(Node* node);
//複製一顆二叉樹
Node* copyTree(Node* node);
//減去最少的節點數量，比value小於或等於時 回傳減少的節點數量
int RLeastNode(Node* node, int value, int total);
//減去最多的節點數量，比value大於或等於時 回傳減少的節點數量
int RMostNode(Node* node, int value, int total);

bool refreshed=0;
Node* store[50000];
int end_index=0;
int main() {
	Node* root = NULL;
	int ns, value;

	cin >> ns;

	for (int i = 0; i < ns; i++) {
		cin >> value;
		total += value;
		insertNode(root, value);
	}

	Node* newNode = NULL;
	char method;

	while (cin >> method) {
		switch (method)
		{
		case 'I':
			cin >> value;
			total += value;
			insertNode(root, value);
			refreshed=0;
			break;
		case 'P':
			preOrderprint(root);
			cout << endl;
			break;
		case 'D':
			cin >> value;
			total -= value;
			deleteBST(root, value);
			refreshed=0;
			break;
		case 'L':
			cin >> value;
			cout << RLeastNode(root, value, total) << endl;
			break;
		case 'M':
			cin >> value;

			//newNode = copyTree(root);

			cout << RMostNode(root, value, total) << endl;
			break;
		default:
			break;
		}
	}
}

Node* createNode(int value) {
	Node* node = new Node;
	node->value = value;
	node->leftNode = NULL;
	node->rightNode = NULL;
	return node;
}

void preOrderprint(Node*& root) {
	if (root != NULL) {
		cout << root->value;
		cout << "(";
		preOrderprint(root->leftNode);
		cout << ")(";
		preOrderprint(root->rightNode);
		cout << ")";
	}
}

void insertNode(Node*& node, int value) {
	if (node == NULL) {
		node = createNode(value);
	}
	else {
		if (node->value > value) {
			insertNode(node->leftNode, value);
		}
		else if (node->value < value) {
			insertNode(node->rightNode, value);
		}
		else {
			insertNode(node->leftNode, value);
		}
	}
}

Node*& getMaximum(Node*& node) {
	if (node->rightNode == NULL) {
		return node;
	}
	return getMaximum(node->rightNode);
}

Node*& getMinimum(Node*& node) {
	if (node->leftNode == NULL) {
		return node;
	}
	return getMinimum(node->leftNode);
}

void deleteNode(Node*& node) {
	if (node->leftNode == NULL && node->rightNode == NULL) {
		free(node);
		node = NULL;
	}
	else if (node->leftNode == NULL) {	//當左子樹為空時
		node = node->rightNode;
	}
	else if (node->rightNode == NULL) {	//當右子樹為空時
		node = node->leftNode;
	}
	else {
		Node*& temp = getMaximum(node->leftNode);
		node->value = temp->value;

		if (temp->leftNode == NULL) {
			free(temp);
			temp = NULL;
		}
		else {
			temp = temp->leftNode;
		}
	}
}

bool deleteBST(Node*& node, int value) {
	if (node == NULL) { //未找到節點
		return false;
	}
	else {
		if (node->value > value) {
			return deleteBST(node->leftNode, value);
		}
		else if (node->value < value) {
			return deleteBST(node->rightNode, value);
		}
		else {
			//找到節點并刪除節點
			deleteNode(node);
			return true;
		}
	}
}

int getTotalNodeValue(Node* node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return node->value + getTotalNodeValue(node->leftNode) + getTotalNodeValue(node->rightNode);
	}
}

stack<Node*> increasing_stack;
stack<Node*> decreasing_stack;
void clear_stack(stack<Node*>& Stack){
	while(!Stack.empty()){
		Stack.pop();
	}
}
void make_ordered_array(Node* node){
	if(node==NULL){
		return;
	}
	if(node->leftNode!=NULL){
		make_ordered_array(node->leftNode);
	}
	store[end_index++]=node;
	if(node->rightNode!=NULL){
		make_ordered_array(node->rightNode);
	}
}

int RLeastNode(Node* node, int value, int total) {
	if(!refreshed){
		end_index=0;
		make_ordered_array(node);
		refreshed=1;
	}
	int count = 0;
	int temp_index=end_index-1;
	while (total > value) {
		total-=store[temp_index--]->value;
		count++;
	}
	return count;
}

int RMostNode(Node* node, int value, int total) {
	if(!refreshed){
		end_index=0;
		make_ordered_array(node);
		refreshed=1;
	}
	int count = 0;
	int temp_index=0;
	while (total > value) {
		total-=store[temp_index++]->value;
		count++;
	}
	if(total<value){
		count--;
	}
	return count;
}