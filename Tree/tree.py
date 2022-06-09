#!/usr/bin/env python
# coding: utf-8

# In[1]:


import re


# In[2]:


class Node:
    def __init__(self, data):
        self.data = data
        self.left_child = None
        self.right_siblings = None
        self.level = 0
        self.parent = None


# In[89]:


class Tree:
    def __init__(self, root) :
        self.root = root
        self.count = 0
        self.binary = 0
    
    def CreateNode(self, data):
        new = Node(data)
        return new
    
    def create(self, data):
        self.root = Node(data)
        self.count += 1
    
    def search(self, node, data):
        if node == None:
            return None
        if node.data == data:
            return node
        
        leftchild = self.search(node.left_child, data)
        if leftchild != None:
            return leftchild
        
        rightsiblings = self.search(node.right_siblings, data)
        if rightsiblings != None:
            return rightsiblings
    
    def PreOrderPrintTree(self, root):
        if root == None:
            return None
        
        if not self.binary:#일반트리
            print('%c '%root.data, end = '')
            if root.left_child:
                print("(", end = '')
            self.PreOrderPrintTree(root.left_child)
            if root.right_siblings == None:
                print(")", end = '')
            self.PreOrderPrintTree(root.right_siblings)
        else:
            print("%c"%root.data, end='')
            if (root.left_child != None or root.right_siblings != None):
                print("(", end='')
            if (root.left_child != None):
                self.PreOrderPrintTree(root.left_child)
            if (root.left_child != None):
                print(",", end='')
            if (root.right_siblings != None):
                self.PreOrderPrintTree(root.right_siblings)
            if (root.left_child != None or root.right_siblings != None):
                print(")", end='')
    
    def insert_node(self, p_node, c_list):
        parent = self.search(self.root, p_node)
        if parent == None:
            print("Error")
            return None
        
        if not self.binary:
            for i in range(0, len(c_list)):
                new = self.CreateNode(c_list[i])
                if parent.left_child == None:
                    new.parent = p_node
                    parent.left_child = new
                else:
                    leftchild = parent.left_child
                    while leftchild.right_siblings:
                        leftchild = leftchild.right_siblings
                    leftchild.right_siblings = new
                    new.parent = p_node
                self.count += 1
            self.give_level(self.root)
        else:
            if len(c_list) > 2:
                print("Error: 이진트리의 최대 자식의 수는 2입니다.")
                return
            for i in range(0, len(c_list)):
                new = self.CreateNode(c_list[i])
                if parent.left_child == None:
                    new.parent = p_node
                    parent.left_child = new
                elif parent.right_siblings == None:
                    new.parent = p_node
                    parent.right_siblings = new
                else:
                    print("Error: 이미 자식노드가 가득 차 있습니다.")
                    return None
                self.count += 1
    
    def insert_siblings(self, data, c_list):
        parent_data = self.get_parent(data)
        self.insert_node(parent_data, c_list)
    
    def get_parent(self, data):
        cur = self.search(self.root, data)
        Parent_data = cur.parent
        return Parent_data
    
    def get_sibling(self, data, node):
        if not self.binary:
            s_list = []
            if not node:
                return
            i = 0
            parent_data = self.get_parent(data)
            parent = self.search(self.root, parent_data)
            leftchild = parent.left_child
            while leftchild.right_siblings:
                if leftchild.data != data:
                    s_list.append(leftchild.data)
                    i += 1
                leftchild = leftchild.right_siblings
            s_list.append(leftchild.data)
            print(s_list)
        else:
            parent_data = self.get_parent(data)
            parent = self.seasrch(self.root, parent_data)
            if (data == parent.left_child.data) and (parent.right_siblings):
                print("{%c}"%parent.right_siblings.data)
            elif data == parent.right_siblings:
                printf("{%c}"%parent.left_child.data)
            else:
                print("No Siblings!")
    
    def get_child(self, node, data):
        if not node:
            return None
        c_list = []
        parent = self.search(self.root, data)
        if not self.binary:
            child = parent.left_child
            i = 0
            while child.right_siblings:
                c_list.append(child.data)
                child = child.right_siblings
                i += 1
            c_list.append(child.data)
            print("{", end = '')
            for j in range(0, len(c_list)):
                print("%c "%c_list[j], end = '')
            print("}")
    
    def level_of_node(self, data):
        cur = self.search(self.root, data)
        cur_level = cur.level
        return cur.level
    
    def level_of_tree(self, node):
        if not node:
            return 0
        
        elif not self.binary:#일반 트리
            l_level = self.level_of_tree(node.left_child) + 1
            r_level = self.level_of_tree(node.right_siblings)
            return max(l_level, r_level)
        else:#이진트리
            lheight = self.level_of_tree(node.left_child)
            r_height = self.level_of_tree(node.right_siblings)
            if lheight > rheight:
                return lheight + 1
            else:
                return rheight + 1
    
    def delete_node(self, node, data):
        if not self.binary:
            cur = self.search(self.root, data)
            if cur.left_child:
                print("단말노드가 아니어서 삭제할 수 없습니다.")
                return None
            #본격지우기
            if cur == self.root:
                self.root.data = None
                self.root.left_child = None
                print("빈 트리 입니다.")
                return
            else:
                parent_node = self.search(self.root, self.get_parent(data))
                if cur.right_siblings:
                    parent_node = self.search(self.root, self.get_parent(data))
                    leftchild = parent_node.left_child
                    if cur == leftchild:#첫번째 것을 삭제
                        parent_node.left_child = cur.right_siblings
                    else:#중간의 것
                        while leftchild.right_siblings != cur:
                            leftchild = leftchild.right_siblings
                        leftchild.right_siblings = cur.right_siblings
                else:#맨 마지막 것을 삭제
                    cur.data = None
                    leftchild = parent_node.left_child
                    if leftchild.right_siblings:
                        while leftchild.right_siblings != cur:
                            leftchild = leftchild.right_siblings
                        leftchild.right_siblings = None
                    else:
                        parent_node.left_child = None
                del cur
                self.count -= 1
        else:#이진트리
            parent = None
            t = node

            t = self.search(self.root, data)
            parent_data = self.get_parent(data)
            parent = self.search(self.root, parent_data)
            #탐색이 끝나고 키 값이 트리에 없으면 t는 null일 것이다.
            if t == None:
                print("Error : data is not in the tree")
                return
            #위에서 탐색을 못했을 경우를 다뤘기 때문에 이 아래부터는 탐색이
            #성공적으로 이루어졌다는 가정 하에 경우의 수를 따진다.

            #첫 번째: 단말노드였을 경우
            if (t.left_child == None and t.right_siblings == None):
                if parent != None:
                    if parent.left_child == t:
                        parent.left_child = None
                    else:
                        parent.right_siblings = None
                else: #부모 노드가 NULL이라면, 삭제하려는 노드가 루트 노드이다.
                    self.root = None
            #두 번째: 하나의 서브트리만 가지는 경우
            elif (t.left_child == None or t.right_siblings ==None):
                if (t.left_child != None):
                    child = t.left_child
                else:
                    child = t.right_siblings
                if parent != None:
                    if parent.left_child == t:
                        parent.left_child = child
                    else:
                        parent.right_siblings = child
                else: #부모 노드가 NULL이라면 삭제되는 노드가 루트 노드이다.
                    self.root = child
            #세 번째: 두개의 서브트리를 모두 가지는 경우
            else:
                #오른쪽 서브트리에서 가장 작은 값을 찾는다.
                suc_p = t
                suc = t.right_siblings
                while (suc.left_child != None):
                    suc_p = suc
                    suc = suc.left_child
                #후속자의 부모와 자식을 연결
                if(suc_p.left_child == suc):
                    suc_p.left_child = suc.right_siblings
                #왼쪽 끝까지 내려왔지만 그 끝에 오른쪽 서브트리가 있을 수도 있는데
                #이 경우를 대비해 suc.right 값을 대입하는 것이다.
                else:
                    suc_p.right_siblings = suc.right_siblings
                t.data = suc.data
                t = suc
            self.count -= 1
            del t
    
    def get_ancestors(self, data):
        anc = []
        i = 0
        cur = self.search(self.root, self.get_parent(data))
        while cur != self.root:
            anc.append(cur.data)
            cur = self.search(self.root, self.get_parent(cur.data))
            i += 1
        anc.append(cur.data)
        print(anc)
        print("")
    
    def get_descendants(self, data):
        anc = []
        cur = self.search(self.root, data)
        parent = cur.left_child
        while parent.left_child:
            anc.append(parent.data)
            parent = parent.left_child
        anc.append(parent.data)
        print(anc)
        print("")
    
    def degree_of_node(self, node, data):
        if not node:
            return None
        if not self.binary:#일반 트리
            c_list = []
            parent = self.search(self.root, data)
            child = parent.left_child
            while child.right_siblings:
                c_list.append(child.data)
                child = child.right_siblings
            c_list.append(child.data)
            return len(c_list)
    
        else:#이진 트리
            parent = self.search(self.root, data)
            if parent.left_child:
                if parent.right_siblings:
                    return 2
                return1
            return 0
    
    def degree_of_tree(self, node):
        if not node:
            return 0
        else:
            l_degree = self.degree_of_tree(node.left_child)
            r_degree = self.degree_of_tree(node.right_siblings)
            if l_degree > r_degree:
                return l_degree
            else:
                return r_degree + 1
    
    def count_node(self):
        return self.count
    
    def join_trees(self, data):
        class Tree2:
            def __init__(self, root) :
                self.root = root
                self.count = 0
                self.binary = 0
            
            def CreateNode(self, data):
                new = Node(data)
                return new

            def create(self, data):
                self.root = Node(data)

            def search(self, node, data):
                if(not node):
                    return None
                if node.data == data:
                    return node

                leftchild = self.search(node.left_child, data)
                if leftchild:
                    return leftchild

                rightsiblings = search(node.right_siblings, data)
                if rightsiblings:
                    return rightsiblings
            
            def insert_node(self, p_node, c_list):
                parent = self.search(self.root, p_node)
                if parent == None:
                    print("Error")
                    return None
    
                if not self.binary:
                    for i in range(0, len(c_list)):
                        new = self.CreateNode(c_list[i])
                        if parent.left_child == None:
                            new.parent = p_node
                            parent.left_child = new
                        else:
                            leftchild = parent.left_child
                            while leftchild.right_siblings:
                                leftchild = leftchild.right_siblings
                            leftchild.right_siblings = new
                            new.parent = p_node
                        self.count += 1
                    #self.give_level(self.root)
                else:
                    if len(c_list) > 2:
                        print("Error: 이진트리의 최대 자식의 수는 2입니다.")
                        return
                    for i in range(0, len(c_list)):
                        new = self.CreateNode(c_list[i])
                        if parent.left_child == None:
                            new.parent = p_node
                            parent.left_child = new
                        elif parent.right_siblings == None:
                            new.parent = p_node
                            parent.right_siblings = new
                        else:
                            print("Error: 이미 자식노드가 가득 차 있습니다.")
                            return None
                        self.count += 1
        tree2 = Tree2(None)
        tree2.create('U')
        tree2.insert_node('U', ['V','X','Y'])
        tree2.insert_node('V', ['Z'])
        
        
        new_root = self.CreateNode(data)
        self.root.right_siblings = tree2.root
        new_root.left_child = self.root
        self.root = new_root
        print("my_tree1과 my_tree2를 합쳤습니다.")
    
    def give_level(self, node):
        if not node:
            return None
        self.give_level(node.left_child)
        if node != self.root:
            if self.get_parent(node.data) == self.root.data:
                node.level = 1
            else:
                parent_data = self.get_parent(node.data)
                parent_node = self.search(self.root, parent_data)
                node.level = parent_node.level + 1
        self.give_level(node.right_siblings)
    
    def clear(self, node):
        if node != None:
            self.clear(node.right_siblings)
            self.clear(node.left_child)
            del node
        self.root = None
        self.count = 0
        
                
            
    


# In[90]:


def main():
    my_tree = Tree(None)#트리 생성
    
    Flag = 1 #while문
    print("사용자 추가 함수 1: search(), 찾고자하는 데이터를 갖고있는 노드를 반환해주는 함수이다.");
    print("사용자 추가 함수 2: get left child() 명령어: F()");
    print("사용자 추가 함수 3: get right child() 명령어: H()");
    print("join trees()는 기존에 만들어져 있는 my_tree2를 사용자가 만든 트리와 합치는 과정입니다. 명령어: J(_)");
    print("레디 메이드 tree2 : U(V(Z),X,Y)")
    print("명령어에 공백이 없도록 처리해주세요");
    
    my_tree.binary = int(input("\n선택: 이진트리로 할려면 1을 입력하고, 일반트리는 0을 입력해주세요"))
    if my_tree.binary == 1:
        print("이진 트리로 구현됩니다.")
    else:
        print("일반트리로 구현됩니다.")
    
    while Flag:
        com = input("\n명령을 입력하세요: ")
        c_list = []
        for i in range(0, len(com)): #여러개의 명령어 한번에 받아올 때
            if com[i] == ' ':
                i += 1
            
            elif com[i] == '+' and com[i + 1] == '^':
                my_tree.create(com[i + 2])
                break
            
            elif com[i] == '+' and com[i + 2] == '(':
                for j in com:
                    text = re.sub('[^a-zA-Z]','',com).strip()
                for t in text[1:]:
                    c_list.append(t)
                if com[i - 1] == '=':#insert_siblings
                    my_tree.insert_siblings(com[2], c_list)
                    break
                else:
                    my_tree.insert_node(com[1], c_list)
                    break
            
            elif com[i] == 'S' and com[i + 1] == '(':
                my_tree.get_sibling(com[i + 2], my_tree.root)
                break
            
            elif com[i] == 'P' and com[i + 1] == '(':
                getparent = my_tree.get_parent(com[i + 2])
                print(getparent)
                break
            
            elif com[i] == 'C' and com[i + 1] == '(':
                my_tree.get_child(my_tree.root, com[i + 2])
                
            elif com[i] == 'L' and len(com) == 1:#level of tree
                    level_tree = my_tree.level_of_tree(my_tree.root) - 1
                    print(level_tree)
                    break
            
            elif com[i] == 'L'and com[i + 1] == '(':#level of node
                    level_node = my_tree.level_of_node(com[i + 2])
                    print(level_node)
            
            elif com[i] == '-':
                my_tree.delete_node(my_tree.root, com[i + 1])
                break
            
            elif com[i] == 'A' and com[i + 1] == '(':
                my_tree.get_ancestors(com[i + 2])
            
            elif com[i] == 'D' and com[i + 1] == '(':
                my_tree.get_descendants(com[i + 2])
            
            elif com[i] == 'G' and len(com) == 1:
                dgrtree = my_tree.degree_of_tree(my_tree.root)
                print(dgrtree)
             
            elif com[0] == 'G' and com[1] == '(':
                dgr = my_tree.degree_of_node(my_tree.root, com[i + 2])
                print(dgr)
                break
            
            elif com[i] == '#':
                counting = my_tree.count_node()
                print(counting)
            
            elif com[i] == 'J' and com[i + 1] == '(':
                my_tree.join_trees(com[i + 2])
            
            elif com[i] == 'K':
                my_tree.clear(my_tree.root)
            
            elif com[i] == 'T':
                print("트리를 출력합니다.")
                break
            
            elif com[0] == 'Q':
                Flag = 0
                break
            
        if com[0] == 'Q':
            print("프로그램을 종료합니다.")
        
        elif com[0] == 'T':
            print("(", end = '')
            my_tree.PreOrderPrintTree(my_tree.root)
            if my_tree.binary:
                print(")")
        
        else:
            print("(", end = '')
            my_tree.PreOrderPrintTree(my_tree.root)
            if my_tree.binary:
                print(")")
        


# In[91]:


main()


# In[15]:


c = "+A(B,C,D)"
text = re.sub('[^a-zA-Z]','',c).strip()
for t in text[1:]:
    print(t)


# In[ ]:




