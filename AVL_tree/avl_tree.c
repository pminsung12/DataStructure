#include <stdio.h>
#include <stdlib.h>

int getMax(int a, int b) {
	if (a > b) return a;
	return b;
}

typedef struct Node {
	int key;
	int height;
	struct Node* left;
	struct Node* right;
}Node;

typedef struct AVL {
	Node* root;
	int count;
}AVL;

Node* CreateNode(AVL* my_AVL, int Newkey);//ok
void __init__(AVL* my_AVL);//ok
void create(AVL* my_AVL, int key);//ok
Node* search(AVL* my_AVL, Node* node, int key);//ok
void PreOrderPrintTree(AVL* my_tree, Node* root);
int getHeight(Node* node);
void setHeight(Node* node);
int balancingFactor(Node* node);
Node* rotateLL(Node* node);
Node* rotateRR(Node* node);
Node* rotateLR(Node* node);
Node* rotateRL(Node* node);
Node* balance(AVL* my_AVL, Node* node);
Node* insert_node(AVL* my_AVL, Node* node, int key); 
void delete_node(AVL* my_AVL, Node* node, int key);
Node* delete_balance(AVL* my_AVL, Node* node);
void inorder_traversal(AVL* my_AVL, Node* root);//ok
void right_root_left_traversal(AVL* my_AVL, Node* root);//ok
int height(AVL* my_AVL, Node* node);
int get_left_child(AVL* my_AVL, int key);//ok
int get_right_child(AVL* my_AVL, int key);//ok
int get_min(AVL* my_AVL, Node* node);//ok
int get_max(AVL* my_AVL, Node* node);//ok
int find_node(AVL* my_AVL, Node* node, int key);
int balance_factor(Node* my_AVL, Node* node, int key);
int count_node(AVL* my_AVL);//ok
void clear(AVL* my_AVL, Node* node);//ok
void PostOrderPrintTree(AVL* my_AVL, Node* node); //사용자 추가 함수 1
void destroy_node(AVL* my_AVL, Node* node); //사용자 추가 함수 2
void destroy_tree(AVL* my_AVL, Node* node); //사용자 추가 함수 3

int main() {

	AVL my_AVL;
	__init__(&my_AVL);
	int i = 0;
	int Flag = 1;


	printf("사용자 추가 함수 1: 후위순회 출력함수 명령어 : O \n");
	printf("사용자 추가 함수 2: 노드 메모리 해제 함수 (트리파괴 함수에 쓰이기 때문에 따로 명령어 X)\n");
	printf("사용자 추가 함수 3: 트리 파괴 함수 (트리를 파괴함과 동시에 프로그램 종료) 명령어 : T \n");
	printf("명령어에 공백이 없도록 처리해주세요\n\n");
	printf("delete를 할 때 오른쪽 서브트리에서 가장 작은 값을 찾기때문에\n");
	printf("교수님의 결과값(왼쪽에서 가장 큰 것)이랑 다르게 나올 수 있습니다.\n");
	while (Flag) {
		char com[20] = { 0, };
		char value[5] = { 0, };
		int intkey = 0;
		printf("\n명령을 입력하세요: ");
		fgets(com, sizeof(com), stdin);
		for (int i = 0; i < strlen(com); i++) {
			if (com[i] == '+' && com[i + 1] == '^') {
				/*for (int j = 0; j < 1; j++) {
					value[j] = com[j+1];
				}*/
				value[0] = com[2];
				intkey = atoi(value);
				create(&my_AVL, intkey);
				my_AVL.count++;
			}

			else if (com[i] == '+') {
				value[0] = com[1];
				intkey = atoi(value);
				insert_node(&my_AVL, my_AVL.root, intkey);
				my_AVL.count++;
			}

			else if (com[i] == 'D') {
				value[0] = com[1];
				intkey = atoi(value);
				delete_node(&my_AVL, my_AVL.root, intkey);
				my_AVL.count--;
			}

			else if (com[i] == 'I') {
				inorder_traversal(&my_AVL, my_AVL.root);
				printf("\n");
			}

			else if (com[i] == 'B') {
				value[0] = com[1];
				intkey = atoi(value);
				int bf = balance_factor(&my_AVL, my_AVL.root, intkey);
				printf("balance factor >> %d\n", bf);
			}

			else if (com[i] == 'R') {
				right_root_left_traversal(&my_AVL, my_AVL.root);
				printf("\n");
			}

			else if (com[i] == 'H') {
				int AVL_height = height(&my_AVL, my_AVL.root);
				printf("height >> %d [1부터 시작]\n", AVL_height);
			}

			else if (com[i] == 'G') {
				value[0] = com[1];
				intkey = atoi(value);
				int rc = get_right_child(&my_AVL, intkey);
				if (rc) printf("right child >> %d\n", rc);
				else printf("NULL\n");
			}

			else if (com[i] == 'L') {
				value[0] = com[1];
				intkey = atoi(value);
				int lc = get_left_child(&my_AVL, intkey);
				if (lc) printf("left child >> %d\n", lc);
				else printf("NULL\n");
			}

			else if (com[i] == '#') {
				int count = count_node(&my_AVL);
				printf("%d\n", count);
			}

			else if (com[i] == 'X') {
				int max = get_max(&my_AVL, my_AVL.root);
				printf("max >> %d\n", max);
			}

			else if (com[i] == 'N') {
				int min = get_min(&my_AVL, my_AVL.root);
				printf("min >> %d\n", min);
			}

			else if (com[i] == 'F') {
				value[0] = com[1];
				intkey = atoi(value);

				if (search(&my_AVL, my_AVL.root, intkey) != NULL) {
					printf("Root");
					find_node(&my_AVL, my_AVL.root, intkey);
					printf("\n");
				}
				else {
					printf("Error // Not Exist!\n");
				}
			}

			else if (com[i] == 'O') {
				PostOrderPrintTree(&my_AVL, my_AVL.root);
				printf("\n");
			}

			else if (com[i] == 'T') {
				destroy_tree(&my_AVL, my_AVL.root);
				Flag = 0;
				break;//프로그램 종료
			}

			else if (com[i] == 'C') {
				clear(&my_AVL, my_AVL.root);
			}

			else if (com[i] == 'P') break;

			else if (com[i] == 'Q') {
				Flag = 0;
				break; //프로그램 종료
			}
		}
		if (com[0] == 'Q') printf("프로그램을 종료합니다.\n");
		else if (com[0] == 'T') printf("트리가 파괴되었습니다.\n프로그램을 종료합니다.\n");
		else if (com[0] == 'P') {
			printf("(");
			PreOrderPrintTree(&my_AVL, my_AVL.root);
			printf(")\n");
		}
		else {
			printf("(");
			PreOrderPrintTree(&my_AVL, my_AVL.root);
			printf(")\n");
		}
	}
	return 0;
}


Node* CreateNode(AVL* my_AVL, int Newkey) {
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->left = NULL;
	NewNode->right = NULL;
	NewNode->key = Newkey;
	NewNode->height = 1;
	return NewNode;
}

void __init__(AVL* my_AVL) {
	my_AVL->root = CreateNode(my_AVL, NULL);
	my_AVL->count = 0;
}

void create(AVL* my_AVL, int key) { //ok
	my_AVL->root->key = key;
	my_AVL->count++;
}

Node* search(AVL* my_AVL, Node* node, int key)
{
	/* 찾고자 하는 값을 찾아봤는데 아예 없었을 경우
	혹은 애초에 node 자체가 NULL이었을 경우 */
	if (node == NULL)
		return NULL;

	// 순환으로 탐색 중 원하는 값을 찾았을 때
	if (key == node->key)
		return node; // 해당 노드의 주소를 반환

	  // 찾는 값보다 루트키값이 큰 경우
	else if (node->key > key)
		return search(my_AVL, node->left, key); // 오른쪽 서브트리로 이동

	  // 찾는 값보다 루트키값이 작은 경우
	else
		return search(my_AVL, node->right, key); // 왼쪽 서브트리로 이동
}

void PreOrderPrintTree(AVL* my_tree, Node* root) { //ok
	if (!root) { //방어코드
		return;
	}
	printf("%d", root->key);
	if (root->left != NULL || root->right != NULL)
		printf("(");
	if (root->left != NULL)
		PreOrderPrintTree(my_tree, root->left);
	if (root->left != NULL || root->right != NULL)
		printf(",");
	if (root->right != NULL)
		PreOrderPrintTree(my_tree, root->right);
	if (root->left != NULL || root->right != NULL)
		printf(")");
}

int getHeight(Node* node) {
	if (node == NULL) return 0;
	return node->height;
}

// 모든 노드는 회전을 수행한 이후에 높이를 다시 계산
void setHeight(Node* node) {
	node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
}

int balancingFactor(Node* node) {
	if (node == NULL) return 0;
	Node* leftChild = node->left;
	Node* rightChild = node->right;
	return getHeight(leftChild) - getHeight(rightChild);
}

Node* rotateLL(Node* node) {
	Node* leftchild = node->left;
	node->left = leftchild->right;
	leftchild->right = node;
	setHeight(node);
	return leftchild;
}

Node* rotateRR(Node* node) {
	Node* rightchild = node->right;
	node->right = rightchild->left;
	rightchild->left = node;
	setHeight(node);
	return rightchild;
}

Node* rotateLR(Node* node) {
	Node* leftchild = node->left;
	node->left = rotateRR(leftchild);
	return rotateLL(node);
}

Node* rotateRL(Node* node) {
	Node* rightchild = node->right;
	node->right = rotateLL(rightchild);
	return rotateRR(node);
}

Node* balance(AVL* my_AVL, Node* node) {
	int difference = balancingFactor(node);
	if (difference >= 2) {
		if (balancingFactor(node->left) >= 1) {
			node = rotateLL(node);
			printf("Rotate LL\n");
		}
		else if (balancingFactor(node->left) < 0) {
			node = rotateLR(node);
			printf("Rotate LR\n");
		}
	}
	else if (difference <= -2) {
		if (balancingFactor(node->right) <= -1) {
			node = rotateRR(node);
			printf("Rotate RR\n");
		}
		else if (balancingFactor(node->right) > 0) {
			node = rotateRL(node);
			printf("Rotate RL\n");
		}
	}	
	setHeight(node);
	return node;
}

Node* insert_node(AVL* my_AVL, Node* node, int key) {
	if (node == NULL) return CreateNode(my_AVL, key);
	
	else if (key < node->key) {
		node->left = insert_node(my_AVL, node->left, key);
		my_AVL->root = balance(my_AVL, node);
	}
	else if (key > node->key) {
		node->right = insert_node(my_AVL, node->right, key);
		my_AVL->root = balance(my_AVL, node);
	}
	else {
		printf("데이터 중복이 발생되었습니다.\n");
	}

	return my_AVL->root;
}

void delete_node(AVL* my_AVL, Node* node, int key) {
	Node* parent, * child, * suc, * suc_p, * t;

	// key를 갖는 노드 t를 탐색한다. parent는 t의 부모노드다.
	parent = NULL; // 시초가 되는 root의 부모는 없다.
	t = node;

	// key를 갖는 노드 t를 탐색한다.
	while (t != NULL && t->key != key)
	{
		parent = t; // 부모를 t값과 동일하게 준 후 t를 통해 탐색한다.
			  // t는 왼쪽이나 key값에 따라 왼쪽이나 오른쪽으로 내려간다.
		t = (key < parent->key) ? parent->left : parent->right;
	}

	// 탐색이 끝난 시점에서 만약 키 값이 트리에 없었다면 t는 NULL일 것이다.
	if (!t)
	{
		printf("Error : key is not in the tree\n");
		return; // 원하는 값이 없으므로 return 한다.
	}
	// 위에서 탐색을 못했을 경우를 다뤘기 때문에 이 아래부터는 탐색이
	// 성공적으로 이루어졌다는 가정 하에 경우의 수를 따진다.

	// 첫 번째: 단말노드였을 경우
	if (t->left == NULL && t->right == NULL)
	{
		if (parent) // 부모 노드가 NULL이 아닐 때, 즉 존재할 때
		{
			if (parent->left == t)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		else // 부모 노드가 NULL 이라면, 삭제하려는 노드가 루트 노드다.
			my_AVL->root = NULL;
	}
	// 두 번째: 하나의 서브트리만 가지는 경우
	else if ((t->left == NULL) || (t->right == NULL))
	{
		child = (t->left != NULL) ? t->left : t->right;
		if (parent)
		{
			if (parent->left == t)
				parent->left = child;
			else
				parent->right = child;
		}
		else // 부모 노드가 NULL이라면 삭제되는 노드가 루트노드다.
			my_AVL->root = child;
	}
	// 세 번째: 두개의 서브트리를 모두 가지는 경우
	else
	{
		// 오른쪽 서브트리에서 가장 작은 값을 찾는다.
		suc_p = t;
		suc = t->right;
		while (suc->left != NULL)
		{
			suc_p = suc;
			suc = suc->left;
		}
		// 후속자의 부모와 자식을 연결
		if (suc_p->left == suc)
			suc_p->left = suc->right;
		// 왼쪽 끝까지 내려왔지만 그 끝에 오른쪽 서브트리가 있을 수도 있는데,
		// 이 경우를 대비해 suc->right 값을 대입하는 것이다.

		else
			suc_p->right = suc->right;

		t->key = suc->key;
		t = suc;
	}
	free(t);
	delete_balance(my_AVL, node);
}

Node* delete_balance(AVL* my_AVL, Node* node) {
	if (!node)
		return;

	// 왼쪽 하위 트리 출력
	Node* left = delete_balance(my_AVL, node->left);


	// 오른쪽 하위 트리 출력
	Node* right = delete_balance(my_AVL, node->right);

	balance(my_AVL, node);
}

void inorder_traversal(AVL* my_AVL, Node* node) {
	if (node) {
		inorder_traversal(my_AVL, node->left);
		printf("%d ", node->key);
		inorder_traversal(my_AVL, node->right);
	}
}

void right_root_left_traversal(AVL* my_AVL, Node* node) {
	if (node) {
		right_root_left_traversal(my_AVL, node->right);
		printf("%d ", node->key);
		right_root_left_traversal(my_AVL, node->left);
	}
}

int height(AVL* my_AVL, Node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		//서브트리들의 높이를 구해서
		int lheight = height(my_AVL, node->left);
		int rheight = height(my_AVL, node->right);

		//더 큰 것을 사용
		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}

int get_left_child(AVL* my_AVL, int key) {
	Node* parent = search(my_AVL, my_AVL->root, key);//부모 노드 찾기
	if (parent->left) {
		Node* lc = parent->left;
		return lc->key;
	}
	else return NULL;
}

int get_right_child(AVL* my_AVL, int key) {
	Node* parent = search(my_AVL, my_AVL->root, key);//부모 노드 찾기
	if (parent->right) {
		Node* rc = parent->right;
		return rc->key;
	}
	else return NULL;//못찾았을 시 NULL반환
}

int get_min(AVL* my_AVL, Node* node) {
	Node* cur = node;

	//제일 왼쪽 노드 찾아가기
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur->key;
}

int get_max(AVL* my_AVL, Node* node) {
	Node* cur = node;

	//제일 오른쪽 노드 찾아가기
	while (cur->right != NULL) {
		cur = cur->right;
	}
	return cur->key;
}

int find_node(AVL* my_AVL, Node* node, int key) {

	// 순환으로 탐색 중 원하는 값을 찾았을 때
	if (key == node->key)
		return;

	// 찾는 값보다 루트키값이 큰 경우
	else if (node->key > key) {
		printf(" > Left");
		find_node(my_AVL, node->left, key); // 왼쪽 서브트리로 이동
	}
	// 찾는 값보다 루트키값이 작은 경우
	else if (node->key < key) {
		printf(" > Right");
		find_node(my_AVL, node->right, key); // 오른쪽 서브트리로 이동
	}
}

int count_node(AVL* my_AVL) {
	return my_AVL->count - 1;//??
}

int balance_factor(Node* my_AVL, Node* node, int key) {
	Node* cur = search(my_AVL, node, key);
	return balancingFactor(cur);
}

void clear(AVL* my_AVL, Node* node) {
	if (node) {//메모리 해제
		clear(my_AVL, node->right);
		clear(my_AVL, node->left);
		free(node);
	}
	__init__(my_AVL);

}

// 후위 순회 
void PostOrderPrintTree(AVL* my_AVL, Node* node) { //사용자 추가 함수 1
	if (!node)
		return;

	// 왼쪽 하위 트리 출력
	PostOrderPrintTree(my_AVL, node->left);

	// 오른쪽 하위 트리 출력
	PostOrderPrintTree(my_AVL, node->right);

	// 부모 노드 출력
	printf("%d ", node->key);
}

void destroy_node(AVL* my_AVL, Node* node) { //사용자 추가 함수 2
	free(node);
}

void destroy_tree(AVL* my_AVL, Node* node) { //사용자 추가 함수 3
	if (node == NULL)
		return;

	// 왼쪽 하위 트리 소멸
	destroy_tree(my_AVL, node->left);

	// 오른쪽 하위 트리 소멸
	destroy_tree(my_AVL, node->right);

	// 루트 노드 소멸
	destroy_node(my_AVL, node);
}
