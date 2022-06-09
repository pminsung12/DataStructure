#pragma warning (disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 10

char my_stack[10];
int top = -1;
char temp[10]; //print()와 is_member()위해 빈 스택 생성
int temptop = -1; //temp의 top


void push(char data);
void temp_push(char data);
char pop();
char temp_pop();
char peek();
void is_full();
int element_count();
void show_top();
void is_member(char data);
void replace(char data);
void clear();
void print();
void print_shape(); //사용자 추가 함수 1
void reverse_print(); //사용자 추가 함수 2
int space_remain(); //사용자 추가 함수 3



int main() {

	char com[10] = { 0, }; //명령 입력받는 배열
	printf("사용자 추가 함수 1: 스택의 모양에 따라 결과 출력함수  명령어: S \n");
	printf("사용자 추가 함수 2: 스택의 원소를 역순으로 출력       명령어: R \n");
	printf("사용자 추가 함수 3: 스택의 남은 공간 알려주는 함수    명령어: @ \n");
	int Flag = 1;
	int i; //반복문 변수
	int j;
	while (Flag) {
		printf("\n명령을 입력하세요: ");
		scanf("%s", &com);
		for (i = 0; i < 10; i++) { //여러개의 명령어 동시 입력받을 때 처리위해 반복문 사용
			
			if (com[0] == '+') { //push()
				push(com[1]);
				break;
			}
			else if (com[0] >= 48 && com[0] <= 57) { //0~9-
				for (j = 0; j < com[0] - 48; j++) {
					char manypop = pop();
					printf("%c이 사라집니다.\n", manypop);
				}
				break;
			}
			else if (com[0] == '-') {//pop()
				char popdata = pop();
				printf("%c이 사라집니다.", popdata);
				break;
			}
			else if (com[0] == 'P') {//peek()
				char toppeek = peek();
				printf("%c", toppeek);
				break;
			}
			else if (com[0] == 'F') {//is_full()
				is_full();
				break;
			}
			else if (com[0] == '#') { // element_count()
				int elecount = element_count();
				printf("%d \n", elecount);
				break;
			}
			else if (com[0] == 'T') {//show_top()
				show_top();
				break;
			}
			else if (com[0] == '?') {//is_member()
				is_member(com[1]);
				break;
			}
			else if (com[0] == 'C') {//clear()
				clear();
				printf("-");
				break;
			}
			else if (com[0] == '=') {//replace()
				replace(com[1]);
				break;
			}
			else if (com[0] == 'R') break;//reverse_print()
			else if (com[0] == 'S') break;//print_shape(), 출력의 default가 print_shape로 설정해서 break만 걸어둠.
			else if (com[0] == '@') {//space_remain()
				printf("%d \n", space_remain());
				break;
			}
			else if (com[0] == 'Q') break; //프로그램 종료
		}//for()
		if (com[0] == 'Q') printf("프로그램을 종료합니다.");
		else if (com[0] == 'L') print(); //print()
		else if (com[0] == 'R') reverse_print(); //reverse_print()
		else print_shape(); //print_shape()
	}//while()
	
	return 0;
}//main()

void push(char data) { //push()
	if (top == SIZE - 1) {
		printf("my_stack 스택 오버플로우가 발생했습니다.\n");
		return;
	}
	my_stack[++top] = data; //스택에 원소추가하고 top+1
}

void temp_push(char data) {//temp스택용 push
	if (temptop == SIZE - 1) {
		printf("temp 스택 오버플로우가 발생했습니다.\n");
		return;
	}
	temp[++temptop] = data;
}

char pop() { //pop()
	if (top == -1) {
		printf("my_stack 스택 언더플로우가 발생했습니다.\n");
		printf("Error: nothing to pop\n");//오류메시지 출력
		return;
	}
	return my_stack[top--]; //삭제하는 원소 반환하고 탑-1
}

char temp_pop() {//temp스택용 pop
	if (temptop == -1) {
		printf("temp 스택 언더플로우가 발생했습니다.\n");
		printf("Error: nothing to pop\n");
		return;
	}
	return temp[temptop--];
}

char peek() {
	if (top == -1) {
		printf("스택이 비어있습니다.\n");
		return;
	}
	return my_stack[top];//top원소 반환
}

void is_full() { //is_full()
	if (top == SIZE - 1) printf("True");
	else printf("False");
}

int element_count() {//element_count()
	return top + 1;
}

void show_top() {//show_top()
	if (top == -1) {
		printf("스택이 비어있습니다.\n");
		return;
	}
	else printf("(%d, %c)\n", top + 1, my_stack[top]);
}

void is_member(char data) {//is_member()
	if (top == -1) {//방어코드
		printf("스택이 비어있습니다.\n");
		return;
	}
	else {
		int confirm = 0; //데이터 확인용
		int count = top + 1;//데이터 개수
		for (int i = 0; i < count; i++) {//my_stack의 원소들 temp에 옮기기
			char end = pop();
			temp_push(end);
		}

		clear();
		for (int j = 0; j < count; j++) {//temp의 원소들을 다시 my_stack에 옮기면서 찾는 원소 있나 검사
			char temppop = temp_pop();
			push(temppop);
			if (my_stack[top] == data) confirm++;//있으면 confirm +1
		}
		if (confirm != 0) printf("True");
		else printf("False");
		printf("\n");
	}
}

void replace(char data) {//replace()
	if (top == -1) {
		printf("스택이 비어있습니다.\n");
		return;
	}
	else my_stack[top] = data;
	
}

void clear() {//clear()
	for (int i = top ; i >= 0; i--) {//스택 모든 원소들을 null값으로 초기화
		my_stack[top] = '\0';
		top--;
	}
}

void print() {//print()
	printf("현재위치는 %c 입니다. \n", my_stack[top]);
	int count = top + 1;//데이터 개수
	for (int i = 0; i < count; i++) {//my_stack원소들 temp로 옮기기
		char end = pop();
		temp_push(end);
	}

	clear();//my_stack 비우기
	for (int j = 0; j < count; j++) {
		char temppop = temp_pop();//다시 temp원소들을 my_stack으로 옮기며 출력
		push(temppop);
		printf("%c ", my_stack[top]);
	}
	printf("\n");
}

//스택의 모양에 맞춰서 전체 원소 출력해주는 함수
void print_shape() { //사용자 추가 1
	printf("\n현재위치는 %c 입니다. \n", my_stack[top]);
	printf("====스택의 꼭대기====\n");
	for (int i = top; i >= 0; i--) {
		printf(" %c \n", my_stack[i]);
	}
	printf("====스택의 바  닥====\n\n");
}
//스택의 원소들을 역순으로 출력해주는 함수
void reverse_print() {//사용자 추가 2
	char a;
	int toptop = top;
	for (int i = 0; i <= toptop; i++) {
		printf("%c ", my_stack[top]);
		a = pop();
	}
	printf("\n");
}
//스택의 메모리가 얼마나 남아있는지 알려주는 함수
int space_remain() { //사용자 추가 3
	return 10 - (top + 1);
}