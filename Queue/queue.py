
class Queue:
    def __init__(self):
        self.list = []
        self.head = -1
        self.tail = -1
        
    def enqueue(self, data):
        if (self.tail >=  10):
            print("큐 오버플로우가 발생했습니다.")
            return
        self.tail += 1
        self.list.append(data)
    
    def dequeue(self):
        if (self.head == self.tail):
            print("큐 언더플로우가 발생했습니다.")
            print("Error(nothing to dequeue)")
            return
        first_index = self.head + 1
        self.head += 1
        return self.list[first_index]
    
    def peek(self):
        if (self.head == self.tail):
            print("큐가 비어있습니다.")
            return
        return self.list[self.head + 1]
    
    def is_full(self):
        if (self.head == self.tail):
            print("True")
        else:
            print("False")
    
    def data_count(self):
        return self.tail - self.head
    
    def show_head(self):
        return self.head + 2 #사용자 입장에서는 맨 처음이 1
    
    def show_tail(self):
        return self.tail + 1 #사용자 입장
    
    def is_empty(self):
        if (self.head == self.tail):
            print("True")
        else:
            print("False")
    
    def is_member(self, data): #FIFO 방식을 고려한 is_member()
        if (self.head == self.tail):
            print("큐가 비어있습니다.")
            return
        
        count = 0
        for i in range(0, self.tail - self.head):
            if self.list[self.head + 1] == data:
                count = 1
            temp = self.list[self.head + 1]
            for j in range(self.head + 1, self.tail):
                self.list[j] = self.list[j + 1]
            self.list[self.tail] = temp
        if count == 1:
            return 1
        else:
            return -1
    
    def replace(self, data):
        if (self.head == self.tail):
            print("큐가 비어있습니다.")
            return
        self.list[self.tail] = data
        
    def clear(self):
        if(self.head == self.tail):
            print("큐가 비어있습니다.")
            return
        while (self.head == self.tail):
            self.dequeue()
        self.head = -1
        self.tail = -1
    
    def printing(self):#FIFO 방식을 고려한 출력함수
        print("head >> ", self.head)
        for i in range(0, self.tail - self.head):
            print("%c "%self.list[self.head + 1], end = '')
            temp = self.list[self.head + 1]
            for j in range(self.head + 1, self.tail):
                self.list[j] = self.list[j + 1]
            self.list[self.tail] = temp
        print("\ntail >> ", self.tail)
    
    #큐의 구조대로 출력    
    def print_shape(self): #사용자 추가 함수 1
        print("")
        print("head >> ", self.head)
        print("====큐의 앞====")
        for i in range(0, self.tail - self.head):
            print("   %c"%self.list[self.head + 1])
            temp = self.list[self.head + 1]
            for j in range(self.head + 1, self.tail):
                self.list[j] = self.list[j + 1]
            self.list[self.tail] = temp
        print("====큐의 뒤====")
        print("tail >> ", self.tail)
        print("")
    
    #큐에 원소를 몇 개 더 집어넣을 수 있나
    def remain_tail(self): #사용자 추가 함수 2
        return 10 - self.tail - 1
    
    #큐 앞에 공백으로 비어있으면 데이터 앞으로 땡기기
    def move_all(self): #사용자 추가 함수 3
        if(self.head == self.tail):
            print("큐가 비어있습니다.")
            return
        while (self.head + 1):
            for j in range(self.head, self.tail):
                self.list[j] = self.list[j + 1]
            self.head -= 1
            self.tail -= 1
    


def main():
    my_queue = Queue()
    Flag = 1 #while문
    print("큐의 SIZE >> 10")
    print("사용자 추가 함수 1: print_shape()  명령어: S")
    print("사용자 추가 함수 2: remain_tail()  명령어: R")
    print("사용자 추가 함수 3: move_all()  명령어 : M ")
    while Flag:
        
        com = input("\n명령을 입력하세요: ")
        for i in range(0, len(com)): #여러개의 명령어 한번에 받아올 때
            if com[i] == ' ':
                i += 1
            
            elif com[i] == '+':#enqueue()
                my_queue.enqueue(com[i + 1])
            
            elif (com[i] >= '0' and com[i] <= '9'):
                num = int(com[i])
                for j in range(0, num):
                    manydq = my_queue.dequeue()
                    if manydq:
                        print(manydq, "가 사라집니다.")
                i = len(com)
            
            elif com[i] == '-':
                popdata = my_queue.dequeue()
                print(popdata, "가 사라집니다.")
            
            elif com[i] == 'P':
                toppeek = my_queue.peek()
                print(toppeek)
                
            elif com[i] == 'F':
                my_queue.is_full()
            
            elif com[i] == '#':
                elecount = my_queue.data_count()
                print(elecount)
                break
            
            elif com[i] == 'H':
                num1 = my_queue.show_head()
                print(num1)
            
            elif com[i] == 'T':
                num2 = my_queue.show_tail()
                print(num2)
                
            elif com[i] == 'E':
                my_queue.is_empty()
            
            elif com[i] == '?':
                ismember = my_queue.is_member(com[i + 1])
                print(ismember)
            
            elif com[i] == '=':
                my_queue.replace(com[i + 1])
            
            elif com[i] == 'C':
                my_queue.clear()
                
            elif com[i] == 'R':
                print("더 집어넣을 수 있는 데이터의 양은 %d 입니다."%my_queue.remain_tail())
            
            elif com[i] == 'L':
                continue
            
            elif com[i] == 'M':
                my_queue.move_all()
            
            elif com[i] == 'Q':#프로그램 종료 명령어 Q
                Flag = 0
                break
        
        if com[0] == 'L':#printing()
            my_queue.printing()
        elif com[0] == 'Q':
            print("프로그램을 종료합니다.")
        elif com[0] == 'S':
            my_queue.print_shape()
        else:
            my_queue.printing()


main()

