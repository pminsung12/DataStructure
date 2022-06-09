
class Node:
    def __init__(self, key):
        self.key = key
        self.height = 1
        self.left = None
        self.right = None


class AVL:
    def __init__(self, root):
        self.root = root
        self.count = 0
    
    def CreateNode(self, key):
        new = Node(key)
        return new
    
    def create(self, key):
        self.root = Node(key)
    
    def search(self, root, key):
        if(root == None):
            return False
        
        #원하는 값을 찾았을 때
        if (key == root.key):
            return root
        
        #찾는 값보다 루트키 값이 큰 경우
        elif root.key > key:
            return self.search(root.left, key)
        
        #찾는 값보다 루트키 값이 작은 경우
        else:
            return self.search(root.right, key)
    
    def getHeight(self, node):
        if node == None:
            return False
        return node.height
    
    def setHeight(self, node):
        node.height = max(self.getHeight(node.left), self.getHeight(node.right)) + 1
        
    def balancingFactor(self, node):
        if node == None:
            return False
        leftChild = node.left
        rightChild = node.right
        return self.getHeight(leftChild) - self.getHeight(rightChild)
    
    def balance_factor(self, node, key):
        cur = self.search(node, key)
        return self.balancingFactor(cur)
    
    def rotateLL(self, node):
        leftchild = node.left
        node.left = leftchild.right
        leftchild.right = node
        self.setHeight(node)
        return leftchild
    
    def rotateRR(self, node):
        rightchild = node.right
        node.right = rightchild.left
        rightchild.left = node
        self.setHeight(node)
        return rightchild
    
    def rotateLR(self, node):
        leftchild = node.left
        node.left = self.rotateRR(leftchild)
        return self.rotateLL(node)
    
    def rotateRL(self, node):
        rightchild = node.right
        node.right = self.rotateLL(rightchild)
        return self.rotateRR(node)
    
    def balance(self, node):
        difference = self.balancingFactor(node)
        if difference >= 2:
            if self.balancingFactor(node.left) >= 1:
                node = self.rotateLL(node)
                print("Rotate LL")
            elif self.balancingFactor(node.left) < 0:
                node = self.rotateLR(node)
                print("Rotate LR")
        
        elif difference <= -2:
            if self.balancingFactor(node.right) <= -1:
                node = self.rotateRR(node)
                print("Rotate RR")
            
            elif self.balancingFactor(node.right) > 0:
                node = self.rotateRL(node)
                print("Rotate RL")
        
        self.setHeight(node)
        return node
    
    def insert_node(self, node, key):
        if node == None:
            return self.CreateNode(key)
        
        elif key < node.key:
            node.left = self.insert_node(node.left, key)
            self.root = self.balance(node)
        
        elif key > node.key:
            node.right = self.insert_node(node.right, key)
            self.root = self.balance(node)
            
        else:
            print("데이터 중복이 발생되었습니다.")
        
        return self.root
    
    def delete_balance(self, node):
        if (node == None):
            return False
        
        #왼쪽 하위 트리 출력
        left = self.delete_balance(node.left)
        
        #오른쪽 하위 트리 출력
        right = self.delete_balance(node.right)
        
        self.balance(node)
    
    def delete_node(self, node, key):
        parent = None
        t = node
        
        while (t != None and t.key != key):
            parent = t
            if key < parent.key:
                t = parent.left
            else:
                t= parent.right
        #탐색이 끝나고 키 값이 트리에 없으면 t는 null일 것이다.
        if t == None:
            print("Error : key is not in the tree")
            return
        #위에서 탐색을 못했을 경우를 다뤘기 때문에 이 아래부터는 탐색이
        #성공적으로 이루어졌다는 가정 하에 경우의 수를 따진다.
        
        #첫 번째: 단말노드였을 경우
        if (t.left == None and t.right == None):
            if parent != None:
                if parent.left == t:
                    parent.left = None
                else:
                    parent.right = None
            else: #부모 노드가 NULL이라면, 삭제하려는 노드가 루트 노드이다.
                self.root = None
        #두 번째: 하나의 서브트리만 가지는 경우
        elif (t.left == None or t.right ==None):
            if (t.left != None):
                child = t.left
            else:
                child = t.right
            if parent != None:
                if parent.left == t:
                    parent.left = child
                else:
                    parent.right = child
            else: #부모 노드가 NULL이라면 삭제되는 노드가 루트 노드이다.
                self.root = child
        #세 번째: 두개의 서브트리를 모두 가지는 경우
        else:
            #오른쪽 서브트리에서 가장 작은 값을 찾는다.
            suc_p = t
            suc = t.right
            while (suc.left != None):
                suc_p = suc
                suc = suc.left
            #후속자의 부모와 자식을 연결
            if(suc_p.left == suc):
                suc_p.left = suc.right
            #왼쪽 끝까지 내려왔지만 그 끝에 오른쪽 서브트리가 있을 수도 있는데
            #이 경우를 대비해 suc.right 값을 대입하는 것이다.
            else:
                suc_p.right = suc.right
            t.key = suc.key
            t = suc
        del t
        self.delete_balance(node)
    
    def PreOrderPrintTree(self, root):
        if(root == None):
            return
        print("%d"%root.key, end='')
        if (root.left != None or root.right != None):
            print("(", end='')
        if (root.left != None):
            self.PreOrderPrintTree(root.left)
        if (root.left != None):
            print(",", end='')
        if (root.right != None):
            self.PreOrderPrintTree(root.right)
        if (root.left != None or root.right != None):
            print(")", end='')
    
    def inorder_traversal(self, node):
        if(node != None):
            self.inorder_traversal(node.left)
            print("%d "%node.key, end = '')
            self.inorder_traversal(node.right)
    
    def right_root_left_traversal(self, node):
        if node != None:
            self.right_root_left_traversal(node.right)
            print("%d "%node.key, end = '')
            self.right_root_left_traversal(node.left)
    
    def height(self, node):
        if node == None:
            return 0;
        else:
            #서브트리들의 높이를 구해서
            lheight = self.height(node.left)
            rheight = self.height(node.right)
            #더 큰 것을 사용
            if lheight > rheight:
                return (lheight + 1)
            else:
                return (rheight + 1)
    
    def get_left_child(self, key):
        parent = self.search(self.root, key)
        if parent.left:
            lc = parent.left
            return lc.key
        else:
            return None
    
    def get_right_child(self, key):
        parent = self.search(self.root, key)
        if parent.right:
            rc = parent.right
            return rc.key
        else:
            return None
    
    def get_min(self, node):
        cur = node
        
        #제일 왼쪽 노드 찾아가기
        while (cur.left != None):
            cur = cur.left
        return cur.key
    
    def get_max(self, node):
        cur = node
        
        #제일 오른쪽 노드 찾아가기
        while (cur.right != None):
            cur = cur.right
        return cur.key
    
    def find_node(self, node, key):
        #순환으로 탐색 중 원하는 값을 찾았을 때
        if key == node.key:
            return
        #찾는 값보다 루트키값이 큰 경우
        elif node.key > key:
            print(" > Left", end = '')
            self.find_node(node.left, key)
        #찾는 값보다 루트키값이 작은 경우
        elif node.key < key:
            print(" > Right", end = '')
            self.find_node(node.right, key)
            
    def count_node(self):
        return (self.count - 1)
    
    def clear(self, node):
        if node != None:
            self.clear(node.right)
            self.clear(node.left)
            del node
        self.__init__(None)
    
    def PostOrderPrintTree(self, node):
        if node == None:
            return
        #왼쪽 하위 트리 출력
        self.PostOrderPrintTree(node.left)
        #오른쪽 하위 트리 출력
        self.PostOrderPrintTree(node.right)
        #부모 노드 출력
        print("%d "%node.key, end = '')
    
    def destroy_node(self, node): #사용자 추가 함수 2
        del node
    
    def destroy_tree(self, node): #사용자 추가 함수 3
        if node == None:
            return
        #왼쪽 하위 트리 소멸
        self.destroy_tree(node.left)
        #오른쪽 하위 트리 소멸
        self.destroy_tree(node.right)
        #루트 노드 소멸
        self.destroy_node(node)
        


def main():
    
    my_AVL = AVL(None)
    
    Flag = 1 #while문
    print("사용자 추가 함수 1: 후위순회 출력함수 명령어 : B  ")
    print("사용자 추가 함수 2: 노드 메모리 해제 함수 (트리파괴 함수에 쓰이기 때문에 따로 명령어 X)")
    print("사용자 추가 함수 3: 트리 파괴 함수 (트리를 파괴함과 동시에 프로그램 종료) 명령어 : T")
    print("명령어에 공백이 없도록 처리해주세요")
    print("delete를 할 때 오른쪽 서브트리에서 가장 작은 값을 찾기때문에")
    print("교수님의 결과값(왼쪽에서 가장 큰 것)이랑 다르게 나올 수 있습니다.")
    while Flag:
        
        com = input("\n명령을 입력하세요: ")
        for i in range(0, len(com)): #여러개의 명령어 한번에 받아올 때
            if com[i] == ' ':
                i += 1
            
            elif (com[i] == '+' and com[i + 1] == '^'):
                v = com[2:]
                intvalue=int(v)
                my_AVL.create(intvalue)
                my_AVL.count += 1
            
            elif (com[i] == '+'):
                v = com[1:]
                intvalue = int(v)
                my_AVL.insert_node(my_AVL.root, intvalue)
                my_AVL.count += 1
                
            elif (com[i] == 'D'):
                v = com[1:]
                intvalue = int(v)
                my_AVL.delete_node(my_AVL.root, intvalue)
                my_AVL.count -= 1
            
            elif com[i] == 'I':
                my_AVL.inorder_traversal(my_AVL.root)
                print("")
            
            elif com[i] == 'R':
                my_AVL.right_root_left_traversal(my_AVL.root)
                print("")
            
            elif com[i] == 'H':
                AVL_height = my_AVL.height(my_AVL.root)
                print("height >> %d [1부터 시작]"%AVL_height)
                
            elif com[i] == 'G':
                v = com[1:]
                intvalue=int(v)
                rc = my_AVL.get_right_child(intvalue)
                if rc != None:
                    print("right child >> %d"%rc)
                else:
                    print("NULL")
            
            elif com[i] == 'L':
                v = com[1:]
                intvalue=int(v)
                lc = my_AVL.get_left_child(intvalue)
                if lc != None:
                    print("left child >> %d"%lc)
                else:
                    print("NULL")
            
            elif com[i] == '#':
                count = my_AVL.count_node() + 1
                print("%d"%count)
            
            elif com[i] == 'B':
                v = com[1:]
                intvalue=int(v)
                bf = my_AVL.balance_factor(my_AVL.root, intvalue)
                print("balancing factor >> %d"%bf)
            
            elif com[i] == 'X':
                max = my_AVL.get_max(my_AVL.root)
                print("max >> %d"%max)
            
            elif com[i] == 'N':
                min= my_AVL.get_min(my_AVL.root)
                print("min >> %d"%min)
                
            elif com[i] == 'F':
                v = com[1:]
                intvalue = int(v)
                
                if my_AVL.search(my_AVL.root, intvalue) == False:
                    print("Error // Not Exist!")
                else:
                    print("Root", end = '')
                    my_AVL.find_node(my_AVL.root, intvalue)
                    print("")
            
            elif com[i] == 'C':
                my_AVL.clear(my_AVL.root)
            
            elif com[i] == 'O':
                my_AVL.PostOrderPrintTree(my_AVL.root)
                print("")
            
            elif com[i] == 'T':
                my_AVL.destroy_tree(my_AVL.root)
                Flag = 0
                break
            
            elif com[i] == 'P':
                break
            
            elif com[i] == 'Q':#프로그램 종료 명령어 Q
                Flag = 0
                break
                
        if com[0] == 'Q':
            print("프로그램을 종료합니다.")
        elif(com[0] == 'T'):
            print("트리가 파괴되었습니다.")
            print("프로그램을 종료합니다.")
        elif (com[0] == 'P'):
            print("(", end='')
            my_AVL.PreOrderPrintTree(my_AVL.root)
            print(")")
        else:
            print("(", end='')
            my_AVL.PreOrderPrintTree(my_AVL.root)
            print(")")



main()




