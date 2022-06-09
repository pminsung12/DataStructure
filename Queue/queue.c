#include <stdio.h>
#define SIZE 10


char my_queue[SIZE];
int head = -1;
int tail = -1;

void enqueue(char data);
char dequeue();
char peek();
void is_full();
int data_count();
int show_head();
int show_tail();
void is_empty();
int is_member(char data);
void replace(char data);
void clear();
void print();
void print_shape();//ťçżëŔÚ Ăß°Ą 1
int remain_tail();//ťçżëŔÚ Ăß°Ą 2
void move_all();//ťçżëŔÚ Ăß°Ą 3

int main() {

	char com[20] = { 0, }; //¸íˇÉ ŔÔˇÂšŢ´Â ščż­
	printf("ťçżëŔÚ Ăß°Ą ÇÔźö 1: print_shape()  ¸íˇÉžî : S\n");
	printf("ťçżëŔÚ Ăß°Ą ÇÔźö 2: remain_tail()  ¸íˇÉžî : R\n");
	printf("ťçżëŔÚ Ăß°Ą ÇÔźö 3: move_all()  ¸íˇÉžî : M \n");
	int Flag = 1;
	int i; //šÝşššŽ şŻźö
	int j;

	while (Flag) {
		printf("\n¸íˇÉŔť ŔÔˇÂÇĎźźżä: ");
		fgets(com, sizeof(com), stdin);
		for (i = 0; i < sizeof(com); i++) { //żŠˇŻ°łŔÇ ¸íˇÉžî ľż˝Ă ŔÔˇÂšŢŔť ś§ Ăł¸ŽŔ§ÇŘ šÝşššŽ ťçżë
			if (com[i] == '\0')break;

			else if (com[i] == '+') { //enqueue()				
				enqueue(com[i + 1]);
			}
			else if (com[0] >= 48 && com[0] <= 57) { //0~9-
				for (j = 0; j < com[0] - 48; j++) {
					char manypop = dequeue();
					printf("%cŔĚ ťçśóÁý´Ď´Ů.\n", manypop);
				}
				break;
			}
			else if (com[i] == '-') {//dequeue()
				char popdata = dequeue();
				printf("%c°Ą ťçśóÁý´Ď´Ů.\n", popdata);
			}
			else if (com[i] == 'P') {//peek()
				char toppeek = peek();
				printf("%c", toppeek);
			}
			else if (com[i] == 'F') {//is_full()
				is_full();
			}
			else if (com[i] == '#') { // element_count()
				int elecount = data_count();
				printf("%d \n", elecount);
				break;
			}
			else if (com[i] == 'H') {//show_head()
				int num1 = show_head();
				printf("%d\n", num1);
			}
			else if (com[i] == 'T') {//show_tail()
				int num2 = show_tail();
				printf("%d\n", num2);
			}
			else if (com[i] == 'E') {//is_empty()
				is_empty();
			}
			else if (com[i] == '?') {//is_member()
				printf("%d", is_member(com[i + 1]));
			}
			else if (com[i] == '=') {//replace()
				replace(com[i + 1]);
			}
			else if (com[i] == 'C') {//clear()
				clear();
			}
			else if (com[i] == 'R') {//remain_tail()
				printf("´ő Áýžî łÖŔť źö ŔÖ´Â ľĽŔĚĹÍŔÇ žçŔş %dŔÔ´Ď´Ů.", remain_tail());
			}
			else if (com[i] == 'M') {//move
				move_all();
			}
			else if (com[i] == 'S') break;
			else if (com[i] == 'L') break;
			else if (com[i] == 'Q') {
				Flag = 0;
				break; //ÇÁˇÎą×ˇĽ Ážˇá
			}
		}//for()
		if (com[0] == 'Q') printf("ÇÁˇÎą×ˇĽŔť ÁžˇáÇŐ´Ď´Ů.\n");
		else if (com[0] == 'L') print(); //print()
		else if (com[0] == 'S') print_shape();//print_shape()
		else print_shape(); //print()
	}//while()
	return 0;
}


void enqueue(char data) {
	if (tail >= SIZE) {
		printf("ĹĽ żŔšöÇĂˇÎżě°Ą šßťýÇß˝Ŕ´Ď´Ů. \n");
		return;
	}
	
	my_queue[++tail] = data;
}

char dequeue() { //źąŔÔźąĂâ
	if (head == tail) {
		printf("ĹĽ žđ´őÇĂˇÎżě°Ą šßťýÇß˝Ŕ´Ď´Ů.\n");
		printf("Error(nothing to dequeue)\n");
		return;
	}
	int first_index = head + 1;
	head++;
	return my_queue[first_index];
}

char peek() {
	if (head == tail) {
		printf("ĹĽ°Ą şńžîŔÖ˝Ŕ´Ď´Ů.\n");
		return;
	}
	return my_queue[head + 1];
}

void is_full() {
	if (tail >= SIZE) printf("True");
	else printf("False");
}

int data_count() {
	return tail - head;
}

int show_head() {
	return head + 2;//ťçżëŔÚŔÔŔĺżĄź­´Â ĂšľĽŔĚĹÍ°Ą ŔÎľŚ˝ş 1
}

int show_tail() {
	return tail + 1;//ťçżëŔÚ ŔÔŔĺżĄź­´Â ¸śÁö¸ˇ ľĽŔĚĹÍ°Ą tail + 1
}

void is_empty() {
	if (head == tail) printf("True");
	else printf("False");
}

int is_member(char data) {//FIFOšć˝ÄŔť °íˇÁÇŃ is_member()
	if (head == tail) {
		printf("ĹĽ°Ą şńžîŔÖ˝Ŕ´Ď´Ů.\n");
		return;
	}

	int count = 0;
	for (int i = 0; i < tail - head; i++) {
		if (my_queue[head + 1] == data) {
			count = 1;
		}
		char temp = my_queue[head + 1];
		for (int j = head + 1; j < tail; j++) {
			my_queue[j] = my_queue[j + 1];
		}
		my_queue[tail] = temp;
	}
	if (count == 1) return 1;
	else return -1;
}

void replace(char data) {
	if (head == tail) {
		printf("ĹĽ°Ą şńžîŔÖ˝Ŕ´Ď´Ů.\n");
		return;
	}
	my_queue[tail] = data;
}

void clear() {
	if (head == tail) {
		printf("ĹĽ°Ą şńžîŔÖ˝Ŕ´Ď´Ů.\n");
		return;
	}
	while (head == tail) {
		dequeue();
	}
	head = -1;//ĆÄŔĚ˝ă ¸¸ľé´Ů źöÁ¤
	tail = -1;//ĆÄŔĚ˝ă ¸¸ľé´Ů źöÁ¤
}

void print() { //FIFOšć˝ÄŔť ÁöĹ˛ ĂâˇÂšćšý
	printf("\nhead >> %d\n", head);
	for (int i = 0; i < tail - head; i++) {
		printf("%c ", my_queue[head + 1]);
		char temp = my_queue[head + 1];
		for (int j = head + 1; j < tail; j++) {
			my_queue[j] = my_queue[j + 1];
		}
		my_queue[tail] = temp;
	}
	printf("\ntail >> %d\n", tail);
}

//ĹĽŔÇ ą¸Áś¸Ś ŔĚÇŘÇĎąâ ĆíÇĎ°Ô ş¸żŠÁÖ´Â ĂâˇÂšć˝Ä
void print_shape() {//ťçżëŔÚ Ăß°Ą ÇÔźö 1
	printf("\nhead >> %d\n", head);
	printf("====ĹĽŔÇ žŐ====\n");
	for (int i = 0; i < tail - head; i++) {
		printf("   %c\n", my_queue[head + 1]);
		char temp = my_queue[head + 1];
		for (int j = head + 1; j < tail; j++) {
			my_queue[j] = my_queue[j + 1];
		}
		my_queue[tail] = temp;
	}
	printf("====ĹĽŔÇ ľÚ====\n");
	printf("tail >> %d\n", tail);
}

//ĹĽżĄ żřźŇ¸Ś ¸î°ł ´ő ÁýžîłÖŔť źö ŔÖłŞ
int remain_tail() {//ťçżëŔÚ Ăß°Ą ÇÔźö 2
	return SIZE - tail - 1;
}

//ĹĽ žŐżĄ °řšéŔ¸ˇÎ şńžîŔÖŔ¸¸é ľĽŔĚĹÍ žŐŔ¸ˇÎ Żąâąâ
void move_all() {//ťçżëŔÚ Ăß°Ą ÇÔźö 3
	if (head == tail) {
		printf("ĹĽ°Ą şńžîŔÖ˝Ŕ´Ď´Ů.\n");
		return;
	}
	while (head+1) {
		for (int j = head; j <= tail - 1; j++) {
			my_queue[j] = my_queue[j + 1];
		}
		head--;
		tail--;
	}
}
