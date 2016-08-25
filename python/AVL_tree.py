class Tree:
    def __init__(self,data):
        self.root = Node(data)
    def insert(self,data):
        if self.root == None:
            self.root = Node(data)
        else:
            self.root = self.root.my_insert(data)
    def print_out(self):
        self.root.print_node()
    def remove(self,data):
        self.root = self.root.remove(data)
class Node:
    def __init__(self,data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1
    
    def bfactor(self):
        if self.left is None:
            if self.right is None:
                return 0
            else:
                return self.right.height
        else:
            if self.right is None:
                return self.left.height
            else:
                return self.right.height-self.left.height

    def fixheight(self):
        if self.left == None:
            if self.right == None:
                self.height = 1
            else:
                self.height = self.right.height+1
        else:
            if self.right is None:
                self.height = self.left.height+1
            else:
                self.height = max(self.left.height, self.right.height)+1
            
    def rotateright(self):
        q = self.left
        self.left = self.left.right
        q.right = self
        self.fixheight()
        q.fixheight()
        return q
    
    def rotateleft(self):
        p = self.right
        self.right = self.right.left
        p.left = self
        self.fixheight()
        p.fixheight()
        return p

    def balance(self):
        self.fixheight()
        if self.bfactor() == 2:
            if self.right is None:
                return self.rotateright()
            if self.right.bfactor()<0:
                self.right = self.right.rotateright()
            return self.rotateleft()
                
        if self.bfactor() == -2:
            if self.left is None:
                return self.rotateleft()
            if self.left.bfactor()>0:
                self.left = self.left.rotateleft()
            return self.rotateright()
        return self
    
    def my_insert(self,data):
        if data>=self.data:
            if self.right is None:
                self.right = Node(data)
                self.height = 2
                return self
            else:
                self.right = self.right.my_insert(data)
        if data<self.data:
            if self.left is None:
                self.left = Node(data)
                self.height = 2
                return self
            else:
                self.left = self.left.my_insert(data)
        node2=self.balance()
        return node2


    def print_node(self, level = 0):
        if self.right:
            self.right.print_node(level + 1)
            print( '\t' * level), (' /')
        print('\t' * level), self.data
        if self.left:
            print( '\t' * level), (' \\')
            self.left.print_node(level + 1)

    def print_Node(self):
        print self.data
        if self.left == None:
            if self.right == None:
                return
            else:
                self.right.print_Node()
        else:
            self.left.print_Node()
    def find_minimum(self):
        if self.left is None:
            return self
        else:
            return self.left.findminimum()

    def remove_minimum(self):
        if self.left is None:
            return self.right
        self.left = remove_minimum(self.left)
        return self.balance()

    def remove(self, data):
        if data < self.data:
            self.left = self.left.remove(data)
        if data > self.data:
            self.right = self.right.remove(data)
        if self.data == data:
            q = self.left
            r = self.right
            if r is None:
                return q
            min = r.find_minimum()
            min.right = r.remove_minimum()
            min.left = q
            return min.balance()
        return self.balance()


tree = Tree(10)
tree.insert(20)
tree.insert(5)
tree.insert(25)
tree.insert(30)
tree.print_out()
print "\n\n\n"
tree.remove(25)
tree.print_out()
