import heapq
import turtle as t

t.pensize(3)
t.color("black")
t.speed(0.01)

class Node:
    def __init__(self, val, freq, left=None, right=None):
        self.val = val
        self.freq = freq
        self.left = left
        self.right = right

    # 用于heapq比较大小
    def __lt__(self, other):
        return self.freq < other.freq
def move(x,y):
    t.penup()
    t.goto(x,y)
    t.pendown()

def round(x,y,z,h):
    t.pensize(4)
    t.color(h)
    move(x,y)
    t.circle(30)
    move(x-5,y+20)
    t.write(f"{z}",font=("宋体",10))
def line(x1, y1, x2, y2):  # 链接
    t.pensize(1)
    t.color("black")
    t.penup()
    t.goto(x1, y1)
    t.pendown()
    t.goto(x2, y2)
def build_huffman_tree(values, freqs):
    # 根据values和freqs构建哈夫曼树
    # values: 字符列表
    # freqs: 字符频率列表

    # 初始化叶子节点集合
    leaves = []
    for i in range(len(values)):
        leaves.append(Node(values[i], freqs[i]))
    heapq.heapify(leaves)

    # 对叶子节点进行合并，构建哈夫曼树
    x=0
    y=200
    while len(leaves) > 1:
        # 每次弹出两个权值最小的节点进行合并
        node1 = heapq.heappop(leaves)
        node2 = heapq.heappop(leaves)
        # 创建新节点
        new_node = Node(None, node1.freq + node2.freq, node1, node2)
        # 将新节点加入到集合中
        heapq.heappush(leaves, new_node)

    # 树根即为最后剩下的节点
    root = leaves[0]
    return root

def display_huffman_tree(root, x, y, a, b):  # 递归输出（a,b表示子节点向下或向外移动多少距离）
    if root:
        if root.val is None:
            round(x, y, root.val,"blue")
        else:
            round(x, y, root.freq,"red")
            #t.goto(x, y - 30)
            #t.write(root.freq, font=("宋体", 15, 'normal'))  # 输出名称
        if root.left:  # 如果存在
            line(x, y - 40, x - a, y - b+60)
            display_huffman_tree(root.left, x - a, y - b, a / 2, b - 30)  # 递归输出
        if root.right:
            line(x, y - 40, x + a, y - b+60)
            display_huffman_tree(root.right, x + a, y - b, a / 2, b - 30)

# 例子：构建哈夫曼树并打印
values=[]
freqs=[]
a=input().split(',')
for i in range(0,len(a),2):
    values.append(a[i])
    freqs.append(int(a[i+1]))
print(values)
print(freqs)
#values = ['a', 'b', 'c', 'd', 'e', 'f']
#freqs = [5, 9, 12, 13, 16, 45]
root = build_huffman_tree(values, freqs)
display_huffman_tree(root, 0, 300, 200, 200)
t.done()

