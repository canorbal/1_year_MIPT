###         AVL tree implementation         ###
### check https://habrahabr.ru/post/150732/ ###


class Tree:
    """
    Interface for working with avl trees
    """
    def __init__(self, data):
        self.root = Node(data)

    def insert(self, data):
        if self.root is None:
            self.root = Node(data)
        else:
            self.root = self.root.insert(data)

    def print_out(self):
        self.root.print_node()

    def remove(self, data):
        self.root = self.root.remove(data)


class Node(object):
    """
    Node object interface
    """
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1

    def bfactor(self):
        """
        :return: difference between right and left subtrees
        """
        if self.left is None:
            if self.right is None:
                return 0
            else:
                return self.right.height
        else:
            if self.right is None:
                return self.left.height
            else:
                return self.right.height - self.left.height

    def fix_height(self):
        """
        Fix height value in current node
        """

        if self.left is None:
            if self.right is None:
                self.height = 1
            else:
                self.height = self.right.height + 1
        else:
            if self.right is None:
                self.height = self.left.height + 1
            else:
                self.height = max(self.left.height, self.right.height) + 1

    def rotate_right(self):
        q = self.left
        self.left = self.left.right
        q.right = self
        self.fix_height()
        q.fixheight()
        return q

    def rotate_left(self):
        p = self.right
        self.right = self.right.left
        p.left = self
        self.fix_height()
        p.fix_height()
        return p

    def balance(self):
        """
        Function to balance nodes
        """

        self.fix_height()

        if self.bfactor() == 2:
            if self.right is None:
                return self.rotate_right()
            if self.right.bfactor()<0:
                self.right = self.right.rotateright()
            return self.rotate_left()

        if self.bfactor() == -2:
            if self.left is None:
                return self.rotate_left()
            if self.left.bfactor() > 0:
                self.left = self.left.rotateleft()
            return self.rotate_right()

        return self

    def insert(self, data):
        """
        Insertion a node with data
        """

        if data >= self.data:
            if self.right is None:
                self.right = Node(data)
                self.height = 2
                return self
            else:
                self.right = self.right.insert(data)

        if data < self.data:
            if self.left is None:
                self.left = Node(data)
                self.height = 2
                return self
            else:
                self.left = self.left.insert(data)

        return self.balance()

    def print_node(self, level=0):

        if self.right:
            self.right.print_node(level + 1)
            print('\t' * level, ' /')
        print('\t' * level, self.data)
        if self.left:
            print('\t' * level, ' \\')
            self.left.print_node(level + 1)


if __name__ == "__main__":

    tree = Tree(10)
    tree.insert(20)
    tree.insert(5)
    tree.insert(25)
    tree.insert(30)
    tree.insert(1)
    tree.insert(45)
    tree.insert(60)
    tree.print_out()
