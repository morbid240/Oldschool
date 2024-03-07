'''
Please use the code template below to complete your assignment.
Your code must go under pa2 method.
Do not change any other code.
The evaluation code uses this templete to run your test cases.
Any changes other than pa2 method would cause the evaluation method
stop working and you will not get credit for your submission.

name: Malcolm Roddy
studentID: 030573684

assignment:PA2
'''
import sys


class Solution:
    def pa2(self, arr: list[int], k: int) -> int:
        retval = 0
        print(arr, k)
        retval = self.find_kth_smallest(arr, k)
        # your code must return an integer
        # for example return True

        return retval
    def __init__(self):
        self.heap = []

    def root(self, i):
        return (i - 1) // 2

    def left(self, i):
        return 2 * i + 1

    def right(self, i):
        return 2 * i + 2

    def swap(self, i, j):
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

    def insert(self, k):
        self.heap.append(k)
        self.heapify_up(len(self.heap) - 1)

    def heapify_up(self, i):
        while i > 0 and self.heap[i] < self.heap[self.root(i)]:
            self.swap(i, self.root(i))
            i = self.parent(i)

    def extract_min(self):
        if len(self.heap) == 0:
            return None

        min_val = self.heap[0]
        last_val = self.heap.pop()

        if len(self.heap) > 0:
            self.heap[0] = last_val
            self.heapify_down(0)

        return min_val

    def heapify_down(self, i):
        smallest = i

        left = self.left(i)
        if left < len(self.heap) and self.heap[left] < self.heap[smallest]:
            smallest = left

        right = self.right(i)
        if right < len(self.heap) and self.heap[right] < self.heap[smallest]:
            smallest = right

        if smallest != i:
            self.swap(i, smallest)
            self.heapify_down(smallest)

    def find_kth_smallest(self, arr, k):
        for num in arr:
            if len(self.heap) < k:
                self.insert(num)
            else:
                if num < self.heap[0]:
                    self.extract_min()
                    self.insert(num)

        return self.heap[0]


# Please make your function call as
# PA2_yourname.py 2,3,4,5 4

if __name__ == '__main__':
    arr = []
    arrtemp = sys.argv[1].split(",")
    for item in arrtemp:
        arr.append(int(item))

    k = int(sys.argv[2])
    obj = Solution()
    ret = obj.pa2(arr, k)
    print(ret)