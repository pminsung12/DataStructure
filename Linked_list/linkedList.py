#!/usr/bin/env python
# coding: utf-8

# In[11]:
#jupyter notebook이라는 에디터를 사용해보았습니다.

class Node: #노드 생성 클래스
    def __init__(self,data,prev=None,next=None):
        self.data=data
        self.prev=prev
        self.next=next

class NodeMgmt: #node magnagement 클래스
    def __init__(self,data):
        self.head=Node(data)
        self.tail=self.head
        self.current_pos=0 #현위치 인덱스 저장 
        self.node_counting=0 #노드 전체 개수 저장
        
    def addTail(self,data): #맨 뒤에 넣기
        if self.head==None:
            self.head=Node(data)
            self.head.data=data
            self.tail==self.head
            self.current_pos += 1
            
        else:
            node=self.head
            while node.next:
                node=node.next
            new=Node(data)
            node.next=new #none이었던 node의 next를 new를 가리키게 변경
            new.prev=node
            self.tail=new
            self.current_pos = self.node_counting + 1
        
        self.node_counting+=1
            
    def delete(self): #현위치 노드삭제함수
        if self.head.data == None:
            print ("값이 존재하지 않습니다.")
            return
        elif self.current_pos == 0:
            print("헤드의 값은 삭제할 수 없습니다.")
            return
        
        node = self.head
        for i in range(1, self.current_pos+1):#현재위치 노드 찾기
            node = node.next
        if node.next: #처음, 중간 노드 삭제
            before_node = node.prev
            after_node = node.next
            before_node.next=after_node
            after_node.prev=before_node
        else: #마지막노드 삭제
            before_node = node.prev
            before_node.next = None
            self.current_pos -= 1
            
        self.node_counting -= 1
        del node
        return
    #현재위치 이후에 값추가 함수    
    def add(self, data): #add()
        if self.head == None: #첫 원소 추가
            self.head = Node(data)
            self.tail = self.head
            self.current_pos += 1
            self.node_counting += 1
            return True
        else: #두번째 이상부터 
            node = self.head
            for i in range(1, self.current_pos + 1):
                node = node.next
                if node == None:
                    return False
            new = Node(data)
            after_new = node.next
            new.next = after_new
            new.prev = node
            node.next = new
            if new.next == None:
                self.tail = new
            self.current_pos += 1
            self.node_counting += 1
            return True
    
    def insert_first(self, data): #insert_first()
        self.traverse_front(0)
        self.add(data)
    
    def get_data(self): #get_data()
        node=self.head
        for i in range(1,self.current_pos+1):
            node=node.next
        
        return node.data
    
    def traverse_front(self, count): #traverse_front()
        if self.head == None: #방어코드
            return False
        elif count == 'N': #N받을 때 마다 +1칸
            self.current_pos += 1            
        else: #바로 숫자로 명령 받았을 때
            intcount = int(count)
            self.current_pos = intcount       
        
        
    
    def traverse_rear(self, count): #traverse_rear()
        if self.head == None: #방어코드
            return False
        elif count == 'P': #N받을 때 마다 뒤로 1칸
            self.current_pos -= 1          
        else: #바로 숫자로 명령 받았을 때
            intcount = int(count)
            self.current_pos = intcount         


    def printing(self):#printing()
        if self.node_counting == 0:
            print("연결리스트가 비어있습니다.")
            print("")
            return
        
        node=self.head
        node=node.next#헤드는 비어있는 노드
        i=1
        print("현재 위치는 %d번째 노드입니다."%self.current_pos)
        while node:
            print("[%d]:%c "%(i, node.data),end=' ')
            node=node.next
            i+=1
        print("전체 노드 개수 : ", self.node_counting)
    
    def data_count(self): #data_count()
        return self.node_counting
    
    def is_member(self, data): #search_from_head
        if self.head==None:
            return False
        
        node=self.head
        i=0
        
        while node:
            if node.data == data:#찾았을 때
                self.current_pos = i
                return self.current_pos
                
            else:#찾는 데이터가 아니면
                node = node.next
                i += 1
        return False
    
    def clear(self): #clear()
        if self.head == None: #방어코드
            return False
         # initialize the current node 
        node = self.head 
        while node: 
            next = node.next # move next node 
            
            # delete the current node 
            del node.data 
              
            # set current equals prev node 
            node = next  
        
        self.current_pos = 0
        self.node_counting = 0
        print("연결리스트 클리어 완료")
    
    def replace(self, data):
        node = self.head
        for i in range(1, self.current_pos + 1):
            node = node.next
        node.data = data
    
    def is_empty(self): #is_empty()
        if self.node_counting==0:
            print(True)
        else:
            print(False)
    #뒤에서 부터 값검색 함수
    def search_from_tail(self, data): #사용자 추가 1
        if self.head==None: #노드에 데이터가 없는 경우
            return False
        
        node=self.tail
        i = 0
        while node:
            if node.data==data: 
                self.current_pos = self.node_counting - i
                return self.current_pos
            else:
                node=node.prev
                i += 1
        return False
    
    #before_data라는 값을 가진 노드 앞에만들겠다
    def insert_before(self, data, before_data): #사용자 추가 2, 이전노드에 값추가
        if self.head==None: #헤드가 없으면 노드를 만들면 됨
            self.head=Node(data)
            self.current_pos += 1
            self.node_counting+=1
            return True
        else:
            node = self.tail #노드가 만약 하나만 있어도 그건 헤드이자 테일이니까 fine
            while node.data != before_data:#before_data의 값을 가진 노드 찾기
                node = node.prev
                if node == None:
                    return False
            new = Node(data)
            before_new = node.prev
            before_new.next = new
            new.prev = before_new
            new.next = node
            node.prev = new
            #현재위치 인덱스 계산
            cur = self.head
            i = 1
            while cur != new:
                cur = cur.next
                i += 1
            self.current_pos = i
            self.node_counting += 1
            return True
    #역순으로 출력하는 함수
    def reverse_printing(self): #사용자 추가 3
        node=self.tail #tail에서 출발
        i=1
        print("현재 위치는 %d번째 노드입니다."%self.current_pos)
        while node.prev:
            print("[%d]:%c "%(i, node.data),end=' ')
            node=node.prev #한칸 이전으로 이동
            i+=1
        print("전체 노드 개수 : ", self.node_counting)
        print("")
                


# In[12]:


my_list=NodeMgmt('\0')

flag=1 #while
print("연결리스트의 맨 처음에 원소를 추가할 경우에는 insert_first 함수를 이용해주세요")
print("insert_first 함수의 명령어 : { ")
print("add의 명령어: D")
print("(a, b, c, d)를 (x,y,z,a,b,c,d)로 만드는 명령어 예시: {x Dy Dz")
print("사용자 추가 함수 1, insert_before(data)의 명령어: _값1값2 ")
print("사용자 추가 함수 2, search_from_tail(data)의 명령어: T값 ")
print("사용자 추가 함수 3, reverse_printing()의 명령어: V ")
print("")
while flag: #무한루프
    com=input("명령을 입력하세요 : ")
    
    for i in range(0, len(com)): #여러 명령어 한꺼번에 처리 위해
        if com[i]==' ':#공백은 빨리 스킵!
            i += 1
                        
        elif com[i] == 'D': #add()
            my_list.add(com[i+1])
        
        elif (com[i] == '+' and com[i+1] != '+'): #addTail()
            my_list.addTail(com[i+1])
        
        elif com[i] == '{': #insert_first 사용자 추가 1 
            my_list.insert_first(com[i+1])
        
        elif com[i] == '_': #insert_before()
            my_list.insert_before(com[i+1],com[i+2])
        
        elif (com[i] == '<' and com[i] != '0'):
            my_list.traverse_front('1')
        
        elif (com[i] == 'N'):
            my_list.traverse_front('N')
        
        elif (com[0] >= '0' and com[0] <= '9'): #맨앞에 숫자가 나올 때
            my_list.traverse_front(com[0])
            if com[1] == 'G':
                print(my_list.get_data())
                continue
            elif com[1] == '=':
                my_list.replace(com[2])
                continue
        
        elif (com[i] == '>'):
            my_list.traverse_rear(my_list.node_counting)
        
        elif (com[i] == 'P'):
            my_list.traverse_rear('P')
        
        elif (com[i] == '-'):#delete()
            my_list.delete()
        
        elif com[i] == '#':#data_count()
            datacount = my_list.data_count()
            print(datacount)
            
        elif com[i] == 'C':#clear()
            my_list.clear()
        
        elif (com[i] == '?'):#is_member()
            ismember = my_list.is_member(com[i+1])
            print(ismember)
            
        elif com[i] == 'G': #get_data()
            g_data = my_list.get_data()
            print(g_data)
        
        elif com[i] == '=':
            my_list.replace(com[i+1])
        
        elif com[i] == 'E':#is_empty()
            my_list.is_empty()
        
        elif com[i] == 'T': #사용자 추가 2 search_from_tail()
            searchfromtail = my_list.search_from_tail(com[i+1])
            print(searchfromtail)
        
        elif com[i] == 'V':#사용자 추가 3 reverse_printing()
            break
            
        elif com[i] == 'Q':#프로그램 종료 명령어 Q
            flag = 0
            break
    if com[0] == 'V':
        my_list.reverse_printing()
    elif com[0] == 'C':
        continue
    else:
        my_list.printing()
        print("")
print("프로그램을 종료합니다.") 
            #my_list.add(com[i+1])

