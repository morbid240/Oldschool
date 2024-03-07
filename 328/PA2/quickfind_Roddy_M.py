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
	def pa2 (self, arr: list[int], k: int )	-> int:
		retval = 0
		print(arr, k)
		retval = self.kth_smallest(arr, 0, len(arr) - 1, k)

		return retval

	def kth_smallest(self, a, l, r, k):
		# Return False if k is out of bounds
		if k < 1 or k > r - l + 1:
			return False

		# Partition the array and find the position of the pivot element
		pos = self.partition(a, l, r)

		# If the pivot element is the kth smallest, return it
		if pos - l + 1 == k:
			return a[pos]

		# If the pivot element is greater than the kth smallest, search in the left subarray
		if pos - l + 1 > k:
			return self.kth_smallest(a, l, pos - 1, k)

		# If the pivot element is smaller than the kth smallest, search in the right subarray
		return self.kth_smallest(a, pos + 1, r, k - (pos - l + 1))

	def partition(self, a, l, r):
		# Choose the last element as the pivot
		pivot = a[r]

		# Partition the array such that elements smaller than pivot are on the left and larger on the right
		i = l - 1
		for j in range(l, r):
			if a[j] <= pivot:
				i += 1
				a[i], a[j] = a[j], a[i]
		a[i + 1], a[r] = a[r], a[i + 1]
		return i + 1



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

