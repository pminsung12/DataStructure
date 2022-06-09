#!/usr/bin/env python
# coding: utf-8

# In[1]:


from collections import defaultdict


# In[3]:


class Graph: 
   
    def __init__(self,count): 
        self.count = 0 #No. of vertices 
        self.count_org = 0 
        self.graph = defaultdict(list) # 리스트를 value로 가지는 딕셔너리 생성
        self.graph_dict = {}
    
    def showVertices(self): #사용자 추가 함수 1
        """ returns the vertices of a graph """
        return list(self.graph_dict.keys())
    
    def showEdges(self): #사용자 추가 함수 2
        return self.graph_dict.values()
    
    def insertVertex(self, vertex):
        if vertex not in self.graph_dict:
            self.graph_dict.setdefault(vertex, [])
            self.count += 1
            self.count_org += 1
        else:
            print("Error: 이미 존재하는 vertex입니다.")
            return
    def insertEdge(self, u, v):
        #예외사항
        if u in self.graph_dict.keys():
            pass
        if v in self.graph_dict.keys():
            pass
        else:
            print("정점이 존재하지 않습니다.")
            return
        
        u_edge = self.graph_dict[u]
        if not u_edge:
            u_edge = []
        u_edge.append(v)
        self.graph_dict[u] = u_edge
        
        v_edge = self.graph_dict[v]
        if not v_edge:
            v_edge = []
        v_edge.append(u)
        self.graph_dict[v] = v_edge
    
    def num_of_vertex(self):
        vertices = self.graph_dict.keys()
        return len(vertices)
    
    def num_of_edge(self):
        allEdges = self.graph_dict.values()
        count = 0
        for list in allEdges:
            count += len(list)
        return count // 2
    
    def renameVertex(self, u, v):
        key = []
        list1 = []
        list2 = []
        for k in self.graph_dict.keys():
            keyMod = k.replace(u, v)
            key.append(keyMod)
        for h in self.graph_dict.values():
            for node in h:
                nodeMod = node.replace(u, v)
                list1.append(nodeMod)
            list2.append(list1)
            list1 = []
        item = zip(key, list2)
        corrected_dict = {a: b for a, b in item}
        self.graph_dict = corrected_dict
    
    def printing(self):
        if self.graph_dict is None:
            print("그래프가 비어있습니다.")
            return
        print(self.graph_dict)
    
    def path_exist(self, start, end, path = []):
        path = path + [start] 
        if start == end: 
            return path 
        if not self.graph_dict[start]:
            return None
        for node in self.graph_dict[start]: 
            if node not in path: 
                newpath = self.path_exist(node, end, path) 
                if newpath:
                    return newpath
        return None
    
    def adjacent(self, v):
        adj = self.graph_dict.get(v)
        print(adj)
    
    def addEdge(self,u,v,w): #가중치 적용 간선 추가 함수
        if w == 1:  #weight가 1이 default
            self.graph[u].append(v) 
        else:     
            self.graph[u].append(self.count) 
            self.graph[self.count].append(v) 
            self.count = self.count + 1
      
    def showPath(self, parent, j): 
        Path_len = 1
        if parent[j] == -1 and j < self.count_org : #Base Case : If j is source 
            print (j)
            return 0 # when parent[-1] then path length = 0     
        l = self.showPath(parent , parent[j]) 
        Path_len = l + Path_len 
  
        if j < self.count_org :  
            print (j) 
  
        return Path_len 
  
    def findShortestPath(self,start, end): #BFS활용한 edge계산 함수(다익스트라 활용)
  
        visited =[False]*(self.count) 
        parent =[-1]*(self.count) 
   

        BFS_queue=[] #BFS때문에 큐 생성
   
        BFS_queue.append(start) 
        visited[start] = True #visit 표시
   
        while BFS_queue : 
            s = BFS_queue.pop(0) 
              
            if s == end: 
                return self.showPath(parent, s) 
                
            for i in self.graph[s]: 
                if visited[i] == False: 
                    BFS_queue.append(i) 
                    visited[i] = True
                    parent[i] = s 


# def main():
#     g = Graph(4) 
#     g.addEdge(0, 1, 2) 
#     g.addEdge(0, 2, 2) 
#     g.addEdge(1, 2, 1) 
#     g.addEdge(1, 3, 1) 
#     g.addEdge(2, 0, 1) 
#     g.addEdge(2, 3, 2) 
#     g.addEdge(3, 3, 2) 
#     
#     print(g.graph)
#     start = 0; end = 3
#     print ("Shortest Path between %d and %d is  " %(start, end)), 
#     l = g.findShortestPath(start, end) 
#     print ("\nShortest Distance between %d and %d is %d " %(start, end, l)), 

# In[4]:


def main():
    
    my_graph = Graph(None) #graph의 count 0으로 초기화
    print("vertex의 최대 개수는 15개까지 입니다.")
    print("weight는 1,2만 가능합니다...ㅎㅎ...")
    print("간선추가 할 때 형식 : E(정점1, 정점2, weight(1 or 2))")
    Flag = 1 #while문
    print("사용자 추가 함수 1: 모든 vertex들 보여주기 명령어: @")
    print("사용자 추가 함수 2: 모든 edge들   보여주기 명령어 : #")
    print("사용자 추가 함수 3: 정점간의 total weight계산 함수 : L(u,v)")

    while Flag:
        com = input("\n명령을 입력하세요: ")
        for i in range(0, len(com)): #여러개의 명령어 한번에 받아올 때
            if com[i] == ' ':
                i += 1
            
            elif (com[i] == '+'):#insert vertex
                my_graph.insertVertex(com[i + 1])
                
            elif (com[0] == 'E' and com[1] == '('):#insert edge
                my_graph.insertEdge(com[2], com[4])
                u = int(com[2]) #형변환 반드시 해줘야함!
                v = int(com[4])
                w = int(com[6])
                my_graph.addEdge(u, v, w)
                my_graph.addEdge(v, u, w)
                break
            
            elif (com[0] == 'L' and com[1] == '('):
                start = int(com[2])
                end = int(com[4])
                print ("Shortest Path between %d and %d is  " %(start, end))
                l = my_graph.findShortestPath(start, end) 
                print ("\nShortest Distance between %d and %d is %d " %(start, end, l))
                break
            
            elif com[0] == 'A' and com[1] == '(':
                my_graph.adjacent(com[2])
                break
            
            elif com[i] == 'P' and com[i + 1] == '(':
                pe = my_graph.path_exist(com[i + 2], com[i + 4])
                if pe:
                    print("True")
                else:
                    print("False")
                #for 초기화 visit 초기화
            
            elif com[i] == 'X':
                print(my_graph.num_of_vertex())
            
            elif com[i] == 'H':
                print(my_graph.num_of_edge())
            
            elif com[i] == 'R' and com[i + 1] == '(':
                my_graph.renameVertex(com[i + 2], com[i + 4])
            
            elif com[i] == 'K':
                my_graph.clear()
                print("그래프가 Clear되었습니다.")
            
            elif com[i] == '@':
                print(my_graph.showVertices())
            
            elif com[i] == '#':
                print(my_graph.showEdges())
            
            elif com[i] == 'Q':#프로그램 종료 명령어 Q
                Flag = 0
                break
                
        if com[0] == 'Q':
            print("프로그램을 종료합니다.")
       
        else:
            my_graph.printing()


# In[6]:


main()


# In[ ]:




