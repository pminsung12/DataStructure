#include <stdio.h>
#include <stdlib.h>
#define MAX 15 
#define TRUE 1
#define FALSE 0

/*===================================================
					  구조체 정의
=====================================================*/
typedef struct Node {
	char vertex;
	struct Node* next;
	int visited;
}Node;

typedef struct Graph {
	Node* head_array[MAX];
	int count;
	int visited[MAX];//정점에 대한 방문 표시를 위한 배열
}Graph;

typedef struct stackNode {//깊이 우선 탐색
	int data;
	struct stackNode* next;
}stackNode;

stackNode* top;


/*===================================================
					   함수선언
=====================================================*/
Node* CreateNode(char v);//ok
void __init__(Graph* my_graph);//ok
Node* array_search(Graph* my_graph, char v);//사용자 추가 함수 1
Node* node_search(Graph* my_graph, Node* head, char v);//사용자 추가 함수 2
void insertVertex(Graph* my_graph, char v);//정렬까지
void deleteVertex(Graph* my_graph, char v);
void deleteEdge(Graph* my_graph, char u, char v);
void insertEdge(Graph* my_graph, char u, char v);//정렬까지
void print(Graph* my_graph);//ok
int degree_of_vertex(Graph* my_graph, char v);//ok
int is_connected(Graph* my_graph);//ok
int is_empty(Graph* my_graph);//ok
void adjacent(Graph* my_graph, char v);//ok
int path_exist(Graph* my_graph, char u, char v, char x);
int num_of_vertex(Graph* my_graph);
int num_of_edge(Graph* my_graph);
void renameVertex(Graph* my_graph, char u, char v);
void clear(Graph* my_graph);
void push(int item);//사용자 추가 3
char pop();//사용자 추가 4


/*===================================================
                       M A I N 
=====================================================*/
int main() {
	Graph my_graph;
	__init__(&my_graph);
	int i = 0;
	int Flag = 1;


	printf("사용자 추가 함수 1: array_search() 헤드 배열안에서 노드반환 함수\n");
	printf("사용자 추가 함수 2: node_search() 헤드와 연결된 노드들에서 원하는 노드반환 함수\n");
	printf("사용자 추가 함수 3: push() 스택용 push\n");
	printf("사용자 추가 함수 4: pop() 스택용 pop\n");
	printf("명령어에 공백이 없도록 처리해주세요\n");

	while (Flag) {
		char com[20] = { 0, };
		printf("\n명령을 입력하세요: ");
		fgets(com, sizeof(com), stdin);
		for (int i = 0; i < strlen(com); i++) {
			if (com[i] == '+') {
				insertVertex(&my_graph, com[i + 1]);
			}

			else if (com[i] == 'E' && com[i + 1] == '(') {
				insertEdge(&my_graph, com[i + 2], com[i + 4]);
			}

			else if (com[i] == '-') {
				deleteVertex(&my_graph, com[i + 1]);
			}

			else if (com[i] == 'D' && com[i + 1] == '(') {
				deleteEdge(&my_graph, com[i + 2], com[i + 4]);
			}

			else if (com[i] == 'V' && com[i + 1] == '(') {
				int dv = degree_of_vertex(&my_graph, com[i + 2]);
				printf("%d\n", dv);
			}

			else if (com[0] == 'C') {
				int ic = is_connected(&my_graph);
				if (ic) printf("True\n");
				else printf("False\n");
				Node* cur;
				for (int j = 0; j < my_graph.count; j++) {//visited 변수 다시 0으로 초기화
					cur = my_graph.head_array[j];
					cur->visited = 0;
				}
				break;
			}

			else if (com[i] == 'N') {
				int ie = is_empty(&my_graph);
				if (ie) printf("True\n");
				else printf("False\n");
			}

			else if (com[i] == 'A' && com[i + 1] == '(') {
				adjacent(&my_graph, com[i + 2]);
			}

			else if (com[i] == 'P' && com[i + 1] == '(') {
				int pe = path_exist(&my_graph, com[i + 2], com[i + 2], com[i + 4]);
				if (pe) printf("True\n");
				else printf("False\n");
				Node* cur;
				for (int j = 0; j < my_graph.count; j++) {//visited 변수 다시 0으로 초기화
					cur = my_graph.head_array[j];
					cur->visited = 0;
				}
			}

			else if (com[i] == 'X') {
				int vtx = num_of_vertex(&my_graph);
				printf("%d\n", vtx);
			}

			else if (com[i] == 'H') {
				int edg = num_of_edge(&my_graph);
				printf("%d\n", edg);
			}

			else if (com[i] == 'R' && com[i + 1] == '(') {
				renameVertex(&my_graph, com[i + 2], com[i + 4]);
			}

			else if (com[i] == 'K') {
				printf("그래프가 Clear되었습니다.\n");
				clear(&my_graph);
			}

			else if (com[0] == 'L') {
				break;
			}

			else if (com[i] == 'Q') {
				Flag = 0;
				break; //프로그램 종료
			}
		}
		if (com[0] == 'Q') printf("프로그램을 종료합니다.\n");
		else if (com[0]=='L') print(&my_graph);
		else {
			print(&my_graph);
		}
	}
	return 0;
}//main()


/*===================================================
                      함수정의
=====================================================*/
Node* CreateNode(char v) { //노드 malloc해주는 함수
	Node* NewNode = (Node*)malloc(sizeof(Node));
	NewNode->next = NULL;
	NewNode->vertex = v;
	NewNode->visited = FALSE;
	return NewNode;
}

void __init__(Graph* my_graph) { //그래프 카운트 초기화
	my_graph->count = 0;
	for (int v = 0; v < MAX; v++) {
		my_graph->head_array[v] = NULL;
		my_graph->visited[v] = FALSE;
	}
}

Node* array_search(Graph* my_graph, char v) {
	for (int i = 0; i < my_graph->count; i++) {
		if (my_graph->head_array[i]->vertex == v) {
			return my_graph->head_array[i];
		}
	}
	return NULL;
}

Node* node_search(Graph* my_graph, Node* head, char v) {
	Node* cur = head->next;
	while (cur) {
		if (cur->vertex == v) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

void insertVertex(Graph* my_graph, char v) {
	if (my_graph->count == MAX) {
		printf("\n 정점을 더이상 만들 수 없습니다.\n");
	}
	Node* node = CreateNode(v);
	my_graph->head_array[my_graph->count] = node;

	my_graph->count++;
}

void insertEdge(Graph* my_graph, char u, char v) {
	/*예외체크*/
	int ucheck = 0;
	int vcheck = 0;
	for (int i = 0; i < my_graph->count; i++) {
		if (my_graph->head_array[i]->vertex == u) {
			ucheck = 1;
		}
		if (my_graph->head_array[i]->vertex == v) {
			vcheck = 1;
		}
	}
	if (!(ucheck && vcheck)) {
		printf("\n 그래프에 없는 정점입니다.");
		return;
	}

	/*Edge 추가*/
	Node* u_head = array_search(my_graph, u);//배열에서 u에 해당하는 vertex 찾기
	Node* v_head = array_search(my_graph, v);//배열에서 v에 해당하는 vertex 찾기

	Node* u_node = CreateNode(u);
	Node* v_node = CreateNode(v);

	Node* cur = u_head;
	while (cur->next) {
		cur = cur->next;
	}
	cur->next = v_node;

	cur = v_head;
	while (cur->next) {
		cur = cur->next;
	}
	cur->next = u_node;
}//insertEdge()

void deleteVertex(Graph* my_graph, char v) {
	Node* cur = NULL;
	Node* del = NULL;
	int j = -1;
	int flag = 1;

	/*index가 필요해 search함수 대신 수작업 진행*/
	for (int i = 0; i < my_graph->count; i++) {
		cur = my_graph->head_array[i];
		if (cur->vertex == v) {
			cur = my_graph->head_array[i];
			j = i;
			break;
		}
	}
	/*예외처리*/
	if (j < 0) {
		printf("%c라는 정점은 존재하지 않습니다.\n", v);
		return;
	}
	if (!(cur->next)) {//독립된 헤드일때
		free(cur);
		
	}
	else {
		/*헤드와 next로 연결된 노드들 삭제*/
		while (flag) {
			if (!(cur->next)) {
				free(cur);
				break;
			}
			del = cur->next;
			free(cur);//일일이 매모리 해제
			cur = del;
		}
	}

	/*array가 중간에 비면 떙겨주기*/
	for (int k = j; j < my_graph->count - 1; j++) {
		my_graph->head_array[j] = my_graph->head_array[j + 1];
	}
	my_graph->count--;
	if (!(cur->next)) return; //독립된 헤드일 때 여기까지만

	/*array돌면서 삭제될 노드들 찾기*/
	for (int i = 0; i < my_graph->count; i++) {
		cur = my_graph->head_array[i];
		Node* node = cur;
		while (node->next) {
			if (node->next->vertex == v) {
				if (node->next->next) {
					del = node->next;
					node->next = node->next->next;
				}
				else {
					del = node->next;
					node->next = NULL;
				}
				free(del);//메모리 해제
				break;
			}
			node = node->next;
		}
	}
}//deleteVertex()

void deleteEdge(Graph* my_graph, char u, char v) {
	Node* u_node = array_search(my_graph, u);
	Node* v_node = array_search(my_graph, v);
	Node* del;//메모리 해제 할때 쓰임
	/*예외처리1: 존재하지 않는 정점을 인자로 받았을 때*/
	if (!(u_node && v_node)) {
		printf("Error: 정점이 존재하지 않습니다!\n");
		return;
	}

	/*예외처리2: 두 정점이 애초에 연결이 되어있지 않았을 때*/
	Node* cur = node_search(my_graph, u_node, v);
	if (!cur) {
		printf("Error: 두 정점은 서로 연결되어 있지 않습니다!\n");
		return;
	}

	/*본격 delete*/
	Node* node;
	node = u_node;
	while (node->next) {
		if (node->next->vertex == v) {
			if (node->next->next) {
				del = node->next;
				node->next = node->next->next;
			}
			else {
				del = node->next;
				node->next = NULL;
			}
			free(del);//메모리 해제
			break;
		}
		node = node->next;
	}

	node = v_node;
	while (node->next) {
		if (node->next->vertex == u) {
			if (node->next->next) {
				del = node->next;
				node->next = node->next->next;
			}
			else {
				del = node->next;
				node->next = NULL;
			}
			free(del);//메모리 해제
			break;
		}
		node = node->next;
	}

}//deleteEdge()

void print(Graph* my_graph) {//트리 출력함수
	printf("(");
	Node* cur;
	for (int i = 0; i < my_graph->count; i++) {
		cur = my_graph->head_array[i];
		printf("%c", cur->vertex);
		if (cur->next) {
			printf("(");
			printf("%c", cur->next->vertex);
			cur = cur->next;
			while (cur->next) {
				printf(",");
				printf("%c", cur->next->vertex);
				cur = cur->next;
			}
			printf(")");
		}
		if (i != my_graph->count - 1) printf(",");
	}
	printf(")");
}//print()

int degree_of_vertex(Graph* my_graph, char v) {
	Node* cur = array_search(my_graph, v);
	int dgr = 0;
	while (cur->next) {
		dgr++;
		cur = cur->next;
	}
	return dgr;
}

int is_connected(Graph* my_graph) { //그래프가 서로 다 연결되어 있는지 T/F

	for (int i = 0; i < my_graph->count; i++) {
		for (int j = 0; j < my_graph->count; j++) {
			int pe = path_exist(my_graph, my_graph->head_array[i]->vertex, my_graph->head_array[i]->vertex, my_graph->head_array[j]->vertex);
			if (!pe) return FALSE;
		}
	}
	return TRUE;
}

int is_empty(Graph* my_graph) { //그래프가 비어있는지 T/F
	if (my_graph->count == 0) {
		return TRUE;
	}
	return FALSE;
}

void adjacent(Graph* my_graph, char v) {//연결되어있는 vertex집합 출력
	Node* cur = array_search(my_graph, v);
	if (!(cur->next)) {//아무와 연결되어있지 않을 때
		printf("Empty\n");
		return;
	}
	printf("{");
	printf("%c", cur->next->vertex);
	cur = cur->next;
	while (cur->next) {
		printf(",");
		printf("%c", cur->next->vertex);
		cur = cur->next;
	}
	printf("}\n");
}

/*
int path_exist(Graph* my_graph, char u, char v) {
	Node* temp;
	Node* cur;
	int check = 0;
	temp = array_search(my_graph, u);
	cur = array_search(my_graph, v);
	//예외 1
	if (u == v) {
		return TRUE;
	}
	//예외 2
	if (!temp || !cur) {
		printf("존재하지 않는 노드입니다.\n");
		return TRUE;
	}
	//본격적인 탐색
	temp->visited = TRUE;
	if (temp->vertex == v) {
		check = 1;
		return TRUE;
	}
	temp = temp->next;
	while (temp) {
		Node* new = array_search(my_graph, temp->vertex);
		if (!(new->visited)) {
			char new_u = temp->vertex;
			int pe = path_exist(my_graph, new_u, v);
			if(pe) return TRUE;
		}
		temp = temp->next;
	}
	return FALSE;
	
}
*/

int path_exist(Graph* my_graph, char vertex1, char rotate_vertex, char vertex2) {
	Node* cur = array_search(my_graph, rotate_vertex);
	if (cur == NULL) return;

	cur->visited = TRUE;

	Node* temp = cur->next;
	while (temp) {
		Node* temp2 = array_search(my_graph, temp->vertex);
		if (temp2->visited == FALSE) {
			int next = path_exist(my_graph, vertex1, temp2->vertex, vertex2);
		}
		temp = temp->next;
	}
	Node* v1 = array_search(my_graph, vertex1);
	Node* v2 = array_search(my_graph, vertex2);

	if (v1->visited == v2->visited) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int num_of_vertex(Graph* my_graph) {//전체 vertex들의 개수
	return my_graph->count;
}

int num_of_edge(Graph* my_graph) {//전체 edge들의 개수
	Node* cur;
	int num = 0;
	for (int i = 0; i < my_graph->count; i++) {
		cur = my_graph->head_array[i];
		while (cur->next) {
			num++;
			cur = cur->next;
		}
	}//for()
	return num / 2;
}

void renameVertex(Graph* my_graph, char u, char v) {//vertex u를 v로 이름 바꿔주는 함수
	Node* cur = array_search(my_graph, u);
	if (!cur) {//u가 존재하지 않을 때
		printf("%c라는 정점은 존재하지 않습니다.\n", u);
		return;
	}
	if (array_search(my_graph, v)) {//v라는 정점이 이미 존재할 때
		printf("%c라는 정점은 이미 존재합니다.\n", v);
	}
	cur->vertex = v;
	//케이스 분리
	if (cur->next) {//어딘가에							 연결되어있는 정점이었을 때
		for (int i = 0; i < my_graph->count; i++) {
			cur = my_graph->head_array[i];
			while (cur) {
				if (cur->vertex == u) {
					cur->vertex = v;
				}
				cur = cur->next;
			}
		}
	}//if()
	else {//독립된 정점이었을 때
		return;
	}
}//renameVertex()

void clear(Graph* my_graph) {
	for (int i = 0; i < my_graph->count; i++) {
		deleteVertex(my_graph, my_graph->head_array[i]->vertex);
	}
	__init__(my_graph);
}

void push(int item) {//stack용 push()
	Node* temp = CreateNode(item);
	temp->next = top;
	top = temp;
}

char pop() {//stack용 pop()
	int item;
	Node* temp = top;
	/*스택이 비어있을 경우*/
	if (!top) {
		printf("Stack is Empty!!\n");
		return NULL;
	}
	item = temp->vertex;
	top = temp->next;
	free(temp);//메모리 해제
	return item;
}

void DFS_graph(Graph* my_graph, int v) {//깊이 우선탐색
	

	Node* w;
	top = NULL;//스택 top 설정
	push(v);//v부터 시작
	my_graph->visited[v] = TRUE;//v를 방문함
	printf("%c ", v + 65);

	while (top) {//스택이 공백이 아닌 동안 깊이 우선 탐색 반복
		w = my_graph->head_array[v];
		while(w) {
			if (!my_graph->visited[w->vertex - 65]) {
				push(w->vertex - 65);
				my_graph->visited[w->vertex - 65] = TRUE;
				printf("%c ", w->vertex);
				v = w->vertex;
				w = my_graph->head_array[v - 65];
			}
			else w = w->next;
		}
		v = pop(); //현재 정점에서 더 이상 순회를 진행할 인접정점이 없는 경우에 스택 pop!
	}
	
}//DFS_graph()
