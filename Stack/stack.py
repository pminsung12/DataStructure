
# c코드랑 방식이 상당히 유사해 주석은 많이 스킵했습니다.
class Stack: #class 정의
    def __init__(self):
        self.list = [] #크기는 10
        self.temp = [] #크기는 10
        self.top = -1 #list의 top인덱스
        self.temptop = -1 #temp의 top
    
    def push(self, item):
        if (self.top == 9): #크기가 10이기 때문에
            print("list 스택 오버플로우가 발생했습니다.")
            return
        self.list.append(item)
        self.top += 1
    
    def temp_push(self, item):#temp의 push 함수
        if (self.temptop == 9):
            print("temp 스택 오버플로우가 발생했습니다.")
            return
        self.temp.append(item)
        self.temptop += 1
        
    def pop(self):
        if (self.top == -1):
            print("list 스택 언더플로우가 발생했습니다.")
            print("Error: nothing to pop")#오류메시지 출력
            return
        
        data = self.list[-1]
        del self.list[-1]
        self.top -= 1
        return data
    
    def temp_pop(self):#temp의 pop함수
        if (self.temptop == -1):
            print("temp 스택 언더플로우가 발생했습니다.")
            print("Error: nothing to pop")#오류메시지 출력
            return
        
        data = self.temp[-1]
        del self.temp[-1]
        self.temptop -= 1
        return data
        
    def peek(self):
        return self.list[-1]
    
    def is_full(self):
        if (self.top == 9):
            print(True)
        else:
            print(False)
    
    def element_count(self):
        return self.top + 1
    
    def show_top(self):
        if (self.top == -1):
            print("스택이 비어있습니다.")
            return
        else:
            print("(%d, %c)"%(self.top + 1, self.list[self.top]))
    
    def is_member(self, data):#is_member()
        if (self.top == -1):#방어코드
            printf("스택이 비어있습니다.")
            return
        else:
            confirm = 0#데이터 들어있는지 확인용
            count = self.top + 1
            for i in range(0, count):
                end = self.pop()
                self.temp_push(end)
            
            self.clear()#my_list클리어 해주고
            
            for j in range(0, count):
                temppop = self.temp_pop()
                self.push(temppop)
                if self.list[self.top] == data:
                    confirm += 1
            if confirm != 0:
                print(True)
            else:
                print(False)
    
    def replace(self, data):
        if self.top == -1:
            print("스택이 비어있습니다.")
            return
        else:
            self.list[self.top] = data
    
    def clear(self):
        """for i in range(self.top + 1, 0, -1):
            self.list[self.top] = '\0'
            self.top -= 1"""
        for i in range(0, self.top + 1):
            end = self.pop()
        
        self.top = -1
    
    def destroy(self): #사용자 추가 4
        for i in range(self.top + 1, 0, -1):
            self.list[self.top] = '\0'
            self.top -= 1 
        print("스택이 destroy 되었습니다.")
    
    def printing(self):
        if self.top == -1:
            print("스택에 데이터가 존재하지 않습니다.")
            print("-")
        
        else:
            print("현재위치는 %c 입니다."%self.list[self.top])
            count = self.top + 1
            for i in range(0, count):
                end = self.pop()
                self.temp_push(end)

            self.clear()

            for j in range(0, count):
                temppop = self.temp_pop()
                self.push(temppop)
                print("%c "%self.list[self.top], end='')
            print("")
    
    #비었는지 확인해주는 함수
    def is_empty(self): #사용자 추가 1
        if self.top == -1:
            print(True)
        else:
            print(False)
    
    #스택의 구조를 보여주는 함수
    def print_shape(self): #사용자 추가 2
        if self.top == -1:
            print("스택에 데이터가 존재하지 않습니다.")
            print("-")
        else:
            print("====스택의 꼭대기====")
            for i in range(self.top, -1, -1):
                print(" %c "%self.list[i])
            print("====스택의 바  닥====")
    
    #스택의 공간이 얼마나 남아있는지 알려주는 함수
    def space_remain(self):#사용자 추가 3
        return 9 - self.top
    
    

def main():
    my_stack = Stack()
    Flag = 1 #while문
    
    while Flag:
        print("사용자 추가 함수 1: is_empty()  명령어 : E ")
        print("사용자 추가 함수 2: print_shape()  명령어 : S")
        print("사용자 추가 함수 3: space_remain()  명령어 : @ ")
        print("사용자 추가 함수 4: destroy()  명령어 : D ")
        com = input("\n명령을 입력하세요: ")
        for i in range(0, len(com)):
            if com[i] == ' ':
                i += 1
            
            elif com[i] == '+':
                my_stack.push(com[i + 1])
            
            elif (com[i] >= '0' and com[i] <= '9'):
                num = int(com[i])
                for j in range(0, num - 1):
                    manypop = my_stack.pop()
                    if manypop:
                        print("%c가 사라집니다."%manypop)
                i = len(com)
            
            
            elif com[i] == '-':
                popdata = my_stack.pop()
                if popdata:
                    print("%c이 사라집니다."%popdata)
            
            elif com[i] == 'P':
                toppeak = my_stack.peek()
                print("%c"%toppeak)
            
            elif com[i] == 'F':
                my_stack.is_full()
            
            elif com[i] == '#':
                elecount = my_stack.element_count()
                print("%d"%elecount)
            
            elif com[i] == 'T':
                my_stack.show_top()
            
            elif com[i] == '?':
                my_stack.is_member(com[i + 1])
                break
            
            elif com[i] == 'C':
                my_stack.clear()
                print("-")
            
            elif com[i] == 'D':
                my_stack.destroy()
                break
            
            elif com[i] == '=':
                my_stack.replace(com[i + 1])
                break
            
            elif com[i] == 'E':#is_empty() 사용자 추가 1
                my_stack.is_empty()
            
            elif com[i] == 'S': #print_shape() 사용자 추가 2
                break
            
            elif com[i] == '@':#space_remain() 사용자 추가 3
                print("%d"%space_remain())
            
            elif com[i] == 'Q':#프로그램 종료 명령어 Q
                Flag = 0
                break
        if com[0] == 'L':#printing()
            my_stack.printing()
        elif com[0] == 'S':#print_shape()
            my_stack.print_shpae()
        elif com[0] == 'D':
            Flag = 0
        else:
            my_stack.printing()
    print("프로그램을 종료합니다.")



main()





