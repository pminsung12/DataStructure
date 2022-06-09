#!/usr/bin/env python
# coding: utf-8

# In[108]:


class Graph:
    def __init__(self, data):
        self.graph_dict = {}

    def showVertices(self): #사용자 추가 함수 1
        """ returns the vertices of a graph """
        return list(self.graph_dict.keys())
    
    def showEdges(self): #사용자 추가 함수 2
        return self.graph_dict.values()
    
    def show_path(self, start, end, path =[]): #사용자 추가 함수 3
        path = path + [start] 
        if start == end: 
            return path 
        if not self.graph_dict[start]:
            return None
        for node in self.graph_dict[start]: 
            if node not in path: 
                newpath = self.show_path(node, end, path) 
                if newpath:  
                    return newpath 
        return None
    
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
    
    def is_connected(self):
        for i in self.graph_dict.keys():
            for j in self.graph_dict.keys():
                pe = self.path_exist(i, j)
                if not pe:
                    return None
        return 1
    
    def insertVertex(self, vertex):
        if vertex not in self.graph_dict:
            self.graph_dict.setdefault(vertex, [])
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
    
    def printing(self):
        if self.graph_dict is None:
            print("그래프가 비어있습니다.")
            return
        print(self.graph_dict)
        
    def deleteVertex(self, v):
        del self.graph_dict[v]
        #edge들도 지워주는 작업
        for edge_list in self.graph_dict.values():
            if edge_list:
                for edge in edge_list:
                    if v in edge:
                        edge_list.remove(edge)
        
        
    
    def deleteEdge(self, u, v):
        #예외사항
        if u in self.graph_dict:
            pass
        elif v in self.graph_dict:
            pass
        else:
            print("정점이 존재하지 않습니다.")
            return
        
        #본격 지우기
        u_edge = self.graph_dict.get(u)
        if not u_edge:
            print("Error")
            return None
        if v in u_edge:
            u_edge.remove(v)
        
        v_edge = self.graph_dict.get(v)
        if not v_edge:
            print("Error")
            return None
        if u in v_edge:
            v_edge.remove(u)
    
    def degree_of_vertex(self, v):
        edges = self.graph_dict.get(v)
        if edges:
            return len(edges)
        return 0
    
    def adjacent(self, v):
        adj = self.graph_dict.get(v)
        print(adj)
    
    def is_empty(self):
        if self.graph_dict:
            return False
        else:
            return True
    
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
    
    def clear(self):
        self.graph_dict.clear()
        return
    
    


# In[109]:


def main():
    
    my_graph = Graph(None) #graph의 count 0으로 초기화
    print("vertex의 최대 개수는 15개까지 입니다.")
    Flag = 1 #while문
    print("사용자 추가 함수 1: 모든 vertex들 보여주기 명령어: @")
    print("사용자 추가 함수 2: 모든 edge들   보여주기 명령어 : #")
    print("사용자 추가 함수 3: vertex간의 path 보여주기 명령어 : S(vertex1, vertex2)")

    while Flag:
        com = input("\n명령을 입력하세요: ")
        for i in range(0, len(com)): #여러개의 명령어 한번에 받아올 때
            if com[i] == ' ':
                i += 1
            
            elif (com[i] == '+'):#insert vertex
                my_graph.insertVertex(com[i + 1])
                
            elif (com[0] == 'E' and com[1] == '('):#insert edge
                my_graph.insertEdge(com[2], com[4])
                break
            
            elif com[i] == '-':
                my_graph.deleteVertex(com[i + 1])
            
            elif com[0] == 'D' and com[1] == '(':
                my_graph.deleteEdge(com[i + 2], com[i + 4])
                break
            
            elif com[i] == 'V' and com[i + 1] == '(':
                print(my_graph.degree_of_vertex(com[i + 2]))
            
            elif com[0] == 'C':
                ic = my_graph.is_connected()
                if ic:
                    print("True")
                else:
                    print("False")
                break
                #for visit 초기화
                
            elif com[i] == 'S' and com[i + 1] == '(':
                print(my_graph.show_path(com[i + 2], com[i + 4]))
            
            elif com[i] == 'N':
                ie = my_graph.is_empty()
                if ie:
                    print("True")
                else:
                    print("False")
            
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
               



main()



