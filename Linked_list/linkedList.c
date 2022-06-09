#pragma warning(disable: 4996)//scanf()
#include <stdio.h>
#include <stdlib.h> //malloc() atoi()

typedef struct Node//노드 정의
{
    char data;//데이터
    struct Node* next;//다음노드 가리키는 링크
    struct Node* prev;//이전노드 가리키는 링크
}Node;

Node* NewNode(char data) //노드생성
{
    Node* now = (Node*)malloc(sizeof(Node)); //동적할당
    now->data = data; //데이터 저장
    now->prev = now->next = NULL; //링크 초기화
    return now; 
}

typedef struct List//연결리스트 정의
{
    Node* head;
    Node* tail;
    int node_counting; //노드개수
    Node* current_pos; //현재위치
}List;

void __Init__(List* my_list)
{
    my_list->head = NewNode(0);//연결 리스트의 맨 앞에 더미 노드 생성
    my_list->tail = NewNode(0);//연결 리스트의 맨 뒤에 더미 노드 생성
    my_list->head->next = my_list->tail;//head의 다음은 tail로 설정
    my_list->tail->prev = my_list->head;//tail의 다음은 head로 설정
    my_list->node_counting = 0;//보관한 데이터 개수를 0으로 설정    
    my_list->current_pos = my_list->head; //현재위치는 맨앞 노드로 설정
}//__Init__()

void addTail(List* my_list, char data) //맨뒤에 노드 추가 함수
{
    Node* now = NewNode(data);//새로운 노드 생성
    now->prev = my_list->tail->prev;//now의 prev를 tail 앞 노드로 설정
    now->next = my_list->tail;//now의 next를 tail로 설정
    my_list->tail->prev->next = now;//tail의 이전 노드의 next를 now로 설정
    my_list->tail->prev = now;//tail의 prev를 now로 설정
    my_list->node_counting++;//보관한 데이터 개수를 1 증가
    if (my_list->node_counting == 1) my_list->current_pos = my_list->head->next; //현재위치 설정
    else my_list->current_pos = my_list->current_pos->next; //현재위치설정
    printf("현재 위치는 %c입니다.\n", my_list->current_pos->data); //현재위치 출력
}//addTail()

void insert(List* my_list, char data) { //사용자 추가 1: 오름차순으로 구성되도록 삽입함수
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data; //데이터 저장
    Node* cur;
    cur = my_list->head->next; //cur은 맨 앞 노드
    while (cur->data < data && cur != my_list->tail) { //오름차순으로 정렬
        cur = cur->next;
    }
    Node* prev = cur->prev; //링크 설정
    prev->next = node;
    node->prev = prev;
    cur->prev = node;
    node->next = cur;
    my_list->current_pos = node; //현재위치를 새로 만든 노드로
    my_list->node_counting++; //보관한 데이터 개수를 1증가
    printf("현재 위치는 %c입니다.\n", my_list->current_pos->data);//현재 위치 출력
}//insert()

void print(List* list) //출력함수
{
    Node* seek = list->head->next;//head->next 부터 출력
    int i = 0; //편의로 노드 순서 알려주는 변수 설정
    printf("보관한 데이터 개수: %d\n", list->node_counting); //보관한 데이터 개수도 출력

    while (seek != list->tail) //seek가 참이면(NULL 이 아니면)
    {
        i++;
        printf("[%d]:%c ", i, seek->data);

        if (i % 5 == 0)//5의 배수일 때
        {
            printf("\n");//다음줄로
        }
        seek = seek->next;//seek를 다음으로 이동
    }
    printf("\n");
}//print()

void reverse_print(List* list) //사용자 추가 2 : 거꾸로 출력해주는 함수
{
    Node* seek = list->tail->prev;//head->prev 부터 출력
    int i = 0;
    printf("보관한 데이터 개수: %d\n", list->node_counting);

    while (seek != list->head) //seek가 참이면(NULL 이 아니면)
    {
        i++;
        printf("[%d]:%c ", i, seek->data);

        if (i % 5 == 0)//5의 배수일 때
        {
            printf("\n");//다음줄로
        }
        seek = seek->prev;//seek를 이전으로 이동
    }
    printf("\n");
}//reverse_print()

char get_data(List* my_list) { //현재위치의 데이터 반환 함수
    return my_list->current_pos->data;
}//get_data()

void traverse_front(List* my_list, char count) {//현재위치 이동함수(순방향)
    char a[10] = { count, };//형변환
    int intcount = atoi(a);//형변환
    if (count == 'N') {//N 이면
        Node* cur;
        cur = my_list->current_pos;
        cur = cur->next;
        my_list->current_pos = cur; //현재위치를 다음노드로 설정
    }
    else { //숫자를 입력받으면
        Node* cur;
        cur = my_list->head->next;
        for (int i = 0; i < intcount-1; i++) cur = cur->next; //숫자만큼 현재위치 이동
        my_list->current_pos = cur;
    }
    printf("현재 위치는 %c입니다.\n", my_list->current_pos->data);
}//traverse_front()

void traverse_rear(List* my_list, char count) { //현재위치 이동함수(역방향)
    char a[10] = { count, };
    int intcount = atoi(a);
    if(count=='P'){//'P'이면
        Node* cur;
        cur = my_list->current_pos;
        cur = cur->prev;//현재위치를 이전 노드로 설정
        my_list->current_pos = cur;
    }
    else {
        Node* cur;
        cur = my_list->tail->prev;
        for (int i = 0; i < intcount-1; i++) cur = cur->prev;
        my_list->current_pos = cur;
    }
    printf("현재 위치는 %c입니다.\n", my_list->current_pos->data);
}//traverse_rear()

void delete(List* my_list) //현재위치 삭제 함수
{
    Node* node = my_list->current_pos->next;
    my_list->current_pos->prev->next = my_list->current_pos->next;//이전 노드의 next를 now의 다음 노드로 설정
    my_list->current_pos->next->prev = my_list->current_pos->prev;//다음 노드의 prev를 now의 이전 노드로 설정
    free(my_list->current_pos);//노드 소멸
    if (node == my_list->tail) my_list->current_pos = node->prev;
    else my_list->current_pos = node;
    my_list->node_counting--;//보관한 노드 개수를 1 감소
    printf("현재 위치는 %c입니다.\n", my_list->current_pos->data);
}//delete()

void removeFront(List* my_list) { //사용자 추가 3: 맨앞의 노드삭제 함수

    Node* cur;
    Node* curnext;
    cur = my_list->head->next;
    curnext = cur->next;
    my_list->current_pos = cur;
    my_list->head->next = cur->next;
    cur->next->prev = cur->prev;
    free(cur);
    my_list->current_pos = curnext;

    my_list->node_counting--;
    printf("현재 위치는 %c입니다.\n", my_list->current_pos->data);

}//removeFront()

void add(List* my_list, char N ,char data) { //현재위치 +1 에 노드 생성 함수
    if (N == 'N') { //그냥 N을 받았을 때
        Node* cur;
        cur = my_list->current_pos->next;
        if (cur == my_list->tail) {//현재위치가 마지막 노드일 때 addTail참조
            Node* now = NewNode(data);//새로운 노드 생성
            now->prev = my_list->tail->prev;//now의 prev를 tail 앞 노드로 설정
            now->next = my_list->tail;//now의 next를 tail로 설정
            my_list->tail->prev->next = now;//tail의 이전 노드의 next를 now로 설정
            my_list->tail->prev = now;//tail의 prev를 now로 설정
            my_list->node_counting++;//보관한 데이터 개수를 1 증가
            if (my_list->node_counting == 1) my_list->current_pos = my_list->head->next;
            else my_list->current_pos = my_list->current_pos->next;
        }//if()
        else {
            Node* new = NewNode(data);
            Node* curnext;
            curnext = my_list->current_pos->next;
            new->prev = curnext->prev;
            new->next = my_list->current_pos->next;
            curnext->prev = new;
            my_list->current_pos->next = new;
            new->prev = curnext->prev;
            my_list->node_counting++;

            if (my_list->node_counting == 1) my_list->current_pos = my_list->head->next;
            else my_list->current_pos = my_list->current_pos->next;
        }//else()
    }//if()
    else {//특정한 N값을 받았을 때 (현재는 0인 경우만 생각)
        char a[10] = { N, };//형변환
        int intN = atoi(a);//형변환
        my_list->current_pos = my_list->head; //현재위치를 헤드노드로 두어서 현재위치+1 이 첫노드가 되도록 설정
        for (int i = 0; i < intN; i++) {
            my_list->current_pos = my_list->current_pos->next;
        }
        Node* new = NewNode(data);
        Node* curnext;
        curnext = my_list->current_pos->next;
        new->prev = curnext->prev;
        new->next = my_list->current_pos->next;
        curnext->prev = new;
        my_list->current_pos->next = new;
        new->prev = curnext->prev;
        my_list->node_counting++;

        if (my_list->node_counting == 1) my_list->current_pos = my_list->head->next;
        else my_list->current_pos = my_list->current_pos->next;
    }//else()
    printf("현재 위치는 %c입니다.\n", my_list->current_pos->data);
}//add()

void clear(List* my_list) //연결리스트 전체 삭제 함수
{
    //head 다음 노드가 tail이 아닐 때까지 리스트에서 제거
    while (my_list->current_pos != my_list->tail) //seek가 참이면(NULL 이 아니면)
    {
        Node* cur; //removeFront() 참조
        Node* curnext;
        cur = my_list->head->next;
        curnext = cur->next;
        my_list->current_pos = cur;
        my_list->head->next = cur->next;
        cur->next->prev = cur->prev;
        free(cur);
        my_list->current_pos = curnext;

        my_list->node_counting--;
        printf("현재 위치는 %c입니다.\n", my_list->current_pos->data);
    }//while()
}//clear()

void replace(List* my_list, char data) { //현재위치의 노드의 값 대체 함수
    my_list->current_pos->data = data;
    printf("현재 위치는 %c입니다.\n", my_list->current_pos->data);
}

void is_empty(List* my_list) { //비었는지 묻는 함수
    if (my_list->node_counting == 0) printf("True\n");//비었으면 True출력
    else printf("False\n"); //안비었으면 False 출력

}
int data_count(List* my_list) {//노드의 총 개수 반환 함수
    int count = my_list->node_counting;
    return count;
}

int is_member(List* my_list, char data) { //데이터 조회, 인덱스 반환 함수
    int count = 1;//인덱스
    //head와 tail은 더미 노드입니다.
    Node* seek = my_list->head->next;//head의 next부터 검색합니다.
    while (seek != my_list->tail) //seek가 tail이 아니면
    {
        if (seek->data == data)//찾았을 때
        {
            return count;
        }
        seek = seek->next;//seek를 다음으로 이동
        count++;
    }
    return NULL;//못 찾았을 때

}

int main() {
    List my_list;//연결리스트 선언
    __Init__(&my_list);
    char com[10] = { 0, };//명령 입력받는 배열 선언
    int i = 0;// for문 변수 선언
    int j = 0;// for문 변수 선언
    char count; //traverse함수
    char zero='1';//add(&my_list, 0, 'x')때문에
    printf("사용자 추가 함수 1: 정렬되면서 노드 삽입 함수   명령어: +++\n");
    printf("사용자 추가 함수 2: 맨 앞의 노드 삭제 함수      명령어: F\n");
    printf("사용자 추가 함수 3: 거꾸로 출력함수             명령어: R\n\n");
    printf("add()의 명령어는 ++입니다.\n");
    printf("insert의 명령어는 +++입니다.\n\n");
    printf("더미노드를 사용해서 '<'는 현재위치가 0번쨰가 아니라 1번째\n\
로 가기 때문에 0번째로 갈때에는 <0 를 써주시기 바랍니다.\n");
    printf("ex) add(my_list,0, 'x') --> <0 ++x\n\n");
    printf("프로그램을 종료하려면 Q 를 입력하세요.\n");
    while (1) {
        printf("\n명령을 입력하세요. : ");
        scanf("%s", &com);//입력
        for (j = 0; j < 10; j++) {
            if (com[0] == '+') {
                if (com[1] == '+' && com[2] == '+') insert(&my_list, com[3]); //insert() 명령어: +++
                else if (com[1] == '+' && com[2] != '+') {
                    if (zero == '0') {
                        add(&my_list, '0', com[2]);//add() 명령어 +++
                        zero = '1';
                    }
                    else add(&my_list, 'N', com[2]);
                }
                else addTail(&my_list, com[1]); //addTail() 명령어: +
                break;
            }//생성함수들
            else if (com[j] == NULL) break; //불필요한 for문 동작 제어         
            else if (com[j] == '-') {
                delete(&my_list); //delete() 명령어 : -
                break;
            }//delete
            else if (com[0] >= 48 && com[0] <= 57 && com[1] == '=') {
                traverse_front(&my_list, com[0]);
                replace(&my_list, com[2]);
            }
            else if (com[0] == '<' && com[1] != '0') traverse_front(&my_list, '0');
            else if (com[0] == '<' && com[1] == '0') {
                zero = '0';
                traverse_front(&my_list, '0');
            }
            else if (com[0] == 'N') traverse_front(&my_list, 'N');
            else if (com[0] >= 48 && com[0] <= 57) traverse_front(&my_list, com[0]);
            else if (com[0] == '>') traverse_rear(&my_list, '0');
            else if (com[0] == 'P') traverse_rear(&my_list, 'P');
            else if (com[0] >= 48 && com[0] <= 57) traverse_rear(&my_list, com[0]);//traverse 시리즈들
            else if (com[i] == 'G') printf("%c  ", get_data(&my_list));//get_data() 명령어: G
            else if (com[0] == 'F') {
                removeFront(&my_list);
                break;
            }//removeFront() 명령어: F
            else if (com[0] == 'Q') break;//프로그램 종료 명령어
            else if (com[0] == 'C') {
                clear(&my_list);
                break;
            }//clear() 명령어: C
            else if (com[i] == '=') {
                replace(&my_list, com[i+1]);
                break;
            }//replace*() 명령어: =
            else if (com[0] == 'E') {
                is_empty(&my_list);
                break;
            }//is_empty() 명령어: E
            else if (com[0] == '#') {
                printf("%d \n",data_count(&my_list));
                break;
            }//data_count() 명령어: #
            else if (com[0] == '?') {
                printf("%d \n", is_member(&my_list, com[1]));
                break;
            }//is_member() 명령어: ?
            else if (com[0] == 'R') {
                break;
            }//reverse_print() 명령어: R 여기서 함수 실행하면 순방향출력도 되기 때문에 나가서 실행
            else printf("잘못된 명령어입니다.");
        }//for()
       
        if (com[0] == 'L') { //출력함수, 모든 명령어에 자동 출력이 되기때문에 if 문 사용
            printf("현재 위치는 %c입니다.\n", my_list.current_pos->data);
            print(&my_list);            
        }//if()
        else if (com[0] == 'Q') { //프로그램 종료ㅕ
            printf("프로그램을 종료합니다.\n");
            break;
        }//else if()
        else if (com[0] == 'R') reverse_print(&my_list); //반대로 출력함수
        else print(&my_list); // 모든 명령어에 자동 출력
    }//while(1)
    return 0;
}
