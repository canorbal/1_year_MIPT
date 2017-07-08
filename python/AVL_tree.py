###         AVL tree implementation         ###
### check https://habrahabr.ru/post/150732/ ###


class Tree:

    def __init__(self, data):
        self.root = Node(data)

    def insert(self, data):
        if self.root == None:
            self.root = Node(data)
        else:
            self.root = self.root.my_insert(data)

    def print_out(self):
        self.root.print_node()

    def remove(self, data):
        self.root = self.root.remove(data)

class Node:

    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1

    def bfactor(self):
        '''
        calculate balance factor of Node
        '''

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
        '''
        recalculate node heights
        '''

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
        '''
        function to balance Nodes
        '''

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

    def my_insert(self, data):
        '''
        insertion a node with data key
        '''

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

tree = Tree(10)
tree.insert(20)
tree.insert(5)
tree.insert(25)
tree.insert(30)
tree.insert(1)
tree.insert(45)
tree.insert(60)
tree.print_out()
