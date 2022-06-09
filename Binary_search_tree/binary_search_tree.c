#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int key;
	struct Node* left;
	struct Node* right;
}Node;

typedef struct BST {
	Node* root;
	int count;
}BST;

Node* CreateNode(BST* my_BST, int Newkey);//ok
void __init__(BST* my_BST);//ok
void create(BST* my_BST, int key);//ok
Node* search(BST* my_BST, Node* node, int key);//ok
Node* insert_node(BST* my_BST, Node* node, int key);//ok
void inorder_traversal(BST* my_BST, Node* root);//ok
void right_root_left_traversal(BST* my_BST, Node* root);//ok
void PreOrderPrintTree(BST* my_BST, Node* root);//ok
void delete_node(BST*, Node* node, int key);//ok
int height(BST* my_BST, Node* node);//ok
int get_left_child(BST* my_BST, int key);//ok
int get_right_child(BST* my_BST, int key);//ok
int get_min(BST* my_BST, Node* node);//ok
int get_max(BST* my_BST, Node* node);//ok
int find_node(BST* my_BST, Node* node, int key);
int count_node(BST* my_BST);//ok
void clear(BST* my_BST, Node* node);//ok
void PostOrderPrintTree(BST* my_BST, Node* node); //사용자 추가 함수 1
void destroy_node(BST* my_BST, Node* node); //사용자 추가 함수 2
void destroy_tree(BST* my_BST, Node* node); //사용자 추가 함수 3

int main() {

	BST my_BST;
	__init__(&my_BST);
	int i = 0;
	int Flag = 1;


	printf("사용자 추가 함수 1: 후위순회 출력함수 명령어 : B \n");
	printf("사용자 추가 함수 2: 노드 메모리 해제 함수 (트리파괴 함수에 쓰이기 때문에 따로 명령어 X)\n");
	printf("사용자 추가 함수 3: 트리 파괴 함수 (트리를 파괴함과 동시에 프로그램 종료) 명령어 : D \n");
	printf("명령어에 공백이 없도록 처리해주세요\n");

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
				value[1] = com[3];
				intkey = atoi(value);
				create(&my_BST, intkey);
				my_BST.count++;
			}

			else if (com[i] == '+') {
				value[0] = com[1];
				value[1] = com[2];
				intkey = atoi(value);
				insert_node(&my_BST, my_BST.root, intkey);
				my_BST.count++;
			}

			else if (com[i] == '-') {
				value[0] = com[1];
				value[1] = com[2];
				intkey = atoi(value);
				delete_node(&my_BST, my_BST.root, intkey);
				my_BST.count--;
			}

			else if (com[i] == 'I') {
				inorder_traversal(&my_BST, my_BST.root);
				printf("\n");
			}

			else if (com[i] == 'R') {
				right_root_left_traversal(&my_BST, my_BST.root);
				printf("\n");
			}

			else if (com[i] == 'H') {
				int bst_height = height(&my_BST, my_BST.root) - 1;
				printf("height >> %d [0부터 시작]\n", bst_height);
			}

			else if (com[i] == 'G' && com[i + 1] == '(') {
				value[0] = com[2];
				value[1] = com[3];
				intkey = atoi(value);
				int rc = get_right_child(&my_BST, intkey);
				if (rc) printf("right child >> %d\n", rc);
				else printf("NULL\n");
			}

			else if (com[i] == 'L' && com[i + 1] == '(') {
				value[0] = com[2];
				value[1] = com[3];
				intkey = atoi(value);
				int lc = get_left_child(&my_BST, intkey);
				if (lc) printf("left child >> %d\n", lc);
				else printf("NULL\n");
			}

			else if (com[i] == '#') {
				int count = count_node(&my_BST);
				printf("%d\n", count);
			}

			else if (com[i] == 'X') {
				int max = get_max(&my_BST, my_BST.root);
				printf("max >> %d\n", max);
			}
			
			else if (com[i] == 'N') {
				int min = get_min(&my_BST, my_BST.root);
				printf("min >> %d\n", min);
			}

			else if (com[i] == 'F') {
				value[0] = com[1];
				value[1] = com[2];
				intkey = atoi(value);
				
				if(search(&my_BST, my_BST.root, intkey) != NULL) {
					printf("Root");
					find_node(&my_BST, my_BST.root, intkey);
					printf("\n");
				}
				else {
					printf("Error // Not Exist!\n");
				}
			}

			else if (com[i] == 'C') {
				clear(&my_BST, my_BST.root);
			}

			else if (com[i] == 'B') {
				PostOrderPrintTree(&my_BST, my_BST.root);
				printf("\n");
			}

			else if (com[i] == 'D') {
				destroy_tree(&my_BST, my_BST.root);
				Flag = 0;
				break;//프로그램 종료
			}

			else if (com[i] == 'P') break;
			
			else if (com[i] == 'Q') {
				Flag = 0;
				break; //프로그램 종료
			}
		}
		if (com[0] == 'Q') printf("프로그램을 종료합니다.\n");
		else if (com[0] == 'D') printf("트리가 파괴되었습니다.\n프로그램을 종료합니다.\n");
		else if (com[0] == 'P') {
			printf("(");
			PreOrderPrintTree(&my_BST, my_BST.root);
			printf(")\n");
		}
		else {
			printf("(");
			PreOrderPrintTree(&my_BST, my_BST.root);
			printf(")\n");
		}
	}
	return 0;
}

Node* CreateNode(BST* my_BST, int Newkey) {
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->left = NULL;
	NewNode->right = NULL;
	NewNode->key = Newkey;
	return NewNode;
}

void __init__(BST* my_BST) {
	my_BST->root = CreateNode(my_BST, NULL);
	my_BST->count = 0;
}

void create(BST* my_BST, int key) { //ok
	my_BST->root->key = key;
	my_BST->count++;
}

Node* search(BST* my_BST, Node* node, int key)
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
		return search(my_BST, node->left, key); // 오른쪽 서브트리로 이동

	  // 찾는 값보다 루트키값이 작은 경우
	else
		return search(my_BST, node->right, key); // 왼쪽 서브트리로 이동
}

void PreOrderPrintTree(BST* my_tree, Node* root) { //ok
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

Node* insert_node(BST* my_BST, Node* node, int key)
{
	if (node == NULL) return CreateNode(my_BST, key);
	if (key < node->key)
		node->left = insert_node(my_BST, node->left, key);
	else if (key > node->key)
		node->right = insert_node(my_BST, node->right, key);
	return node;
}

//너무 어려워 구글의 도움을 받았습니다.
void delete_node(BST* my_BST, Node* node, int key) {
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
			my_BST->root = NULL;
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
			my_BST->root = child;
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
}

void inorder_traversal(BST* my_BST, Node* node) {
	if (node) {
		inorder_traversal(my_BST, node->left);
		printf("%d ", node->key);
		inorder_traversal(my_BST, node->right);
	}
}

void right_root_left_traversal(BST* my_BST, Node* node) {
	if (node) {
		right_root_left_traversal(my_BST, node->right);
		printf("%d ", node->key);
		right_root_left_traversal(my_BST, node->left);
	}
}

int height(BST* my_BST, Node* node)
{
	if (node == NULL)
		return 0;
	else
	{
		//서브트리들의 높이를 구해서
		int lheight = height(my_BST, node->left);
		int rheight = height(my_BST, node->right);

		//더 큰 것을 사용
		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}

int get_left_child(BST* my_BST, int key) {
	Node* parent = search(my_BST, my_BST->root, key);//부모 노드 찾기
	if (parent->left) {
		Node* lc = parent->left;
		return lc->key;
	}
	else return NULL;
}

int get_right_child(BST* my_BST, int key) {
	Node* parent = search(my_BST, my_BST->root, key);//부모 노드 찾기
	if (parent->right) {
		Node* rc = parent->right;
		return rc->key;
	}
	else return NULL;//못찾았을 시 NULL반환
}

int get_min(BST* my_BST, Node* node) {
	Node* cur = node;

	//제일 왼쪽 노드 찾아가기
	while (cur->left != NULL) {
		cur = cur->left;
	}
	return cur->key;
}

int get_max(BST* my_BST, Node* node) {
	Node* cur = node;

	//제일 오른쪽 노드 찾아가기
	while (cur->right != NULL) {
		cur = cur->right;
	}
	return cur->key;
}

int find_node(BST* my_BST, Node* node, int key) {

	// 순환으로 탐색 중 원하는 값을 찾았을 때
	if (key == node->key)
		return;

	// 찾는 값보다 루트키값이 큰 경우
	else if(node->key > key) {
		printf(" > Left");
		find_node(my_BST, node->left, key); // 왼쪽 서브트리로 이동
	}
	// 찾는 값보다 루트키값이 작은 경우
	else if (node->key < key) {
		printf(" > Right");
		find_node(my_BST, node->right, key); // 오른쪽 서브트리로 이동
	}
}

int count_node(BST* my_BST) {
	return my_BST->count - 1;//??
}

void clear(BST* my_BST, Node* node) {
	if (node) {//메모리 해제
		clear(my_BST, node->right);
		clear(my_BST, node->left);
		free(node);
	}
	__init__(my_BST);
	
}

// 후위 순회 
void PostOrderPrintTree(BST* my_BST, Node* node) { //사용자 추가 함수 1
	if (!node)
		return;

	// 왼쪽 하위 트리 출력
	PostOrderPrintTree(my_BST, node->left);

	// 오른쪽 하위 트리 출력
	PostOrderPrintTree(my_BST, node->right);

	// 부모 노드 출력
	printf("%d ", node->key);
}

void destroy_node(BST* my_BST, Node* node) { //사용자 추가 함수 2
	free(node);
}

void destroy_tree(BST* my_BST, Node* node) { //사용자 추가 함수 3
	if (node == NULL)
		return;

	// 왼쪽 하위 트리 소멸
	destroy_tree(my_BST, node->left);

	// 오른쪽 하위 트리 소멸
	destroy_tree(my_BST, node->right);

	// 루트 노드 소멸
	destroy_node(my_BST, node);
}
