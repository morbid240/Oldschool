'''
1- Please use the code template below to complete your assignment.
2- Your code must be written in the pa1_quicksort method. 
3- You can define as many as functions needed but 
4- Your algorithms' execution must be started from the 
   pa1_quicksort method.
5- Do not change any other code. 
6- The evaluation code uses this template to run your test cases.
   Any changes other than the pa1_quicksort method would cause 
   the evaluation program error and you will not get credit for your
   submission.


name: Malcolm Roddy
studentID: 030573684

assignment:PA1
'''
import sys
import random
import time

class Solution:

	# this function returns a descending sorted array.
	def function_a (self, elements_count: int) -> list:
		output = []
		for i in range(elements_count,0, -1):
			output.append(i)
		return output

	# this function returns an ascending sorted array.	
	def function_b (self, elements_count: int) -> list:
		output = []
		for i in range(1, elements_count):
			output.append(i)
		return output

	# this function returns a randomly generated array	
	def function_c(self, elements_count: int, seed: int):
		output = []
		random.seed(seed)
		for i in range(0,elements_count+1):
			output.append(random.randint(1,1000000))

		return output

	# this function selects a correct action based on the input a, b or c.	
	def select_input(self, input_type: str, elements_count: int, seed: int) -> list:
		output = []
		if input_type == "a":
			output = self.function_a(elements_count)
		if 	input_type == "b":
			output = self.function_b(elements_count)
		if 	input_type == "c":
			output = self.function_c(elements_count, seed)
		return output	


	def pa1_quicksort (self, input_type: str, elements_count: int, seed: int) -> list:
		output = []
		query_list = self.select_input(input_type, elements_count, seed)
		
		n = len(query_list)

		# get the start time
		st = time.process_time()
		
    	# your quicksort algorithm comes here ...
		sys.setrecursionlimit(10**6)
		p = 0
		r = n - 1

		def partition(arr, l, h):
			i = l - 1
			p = arr[h] # set pivot
			for j in range(l, h):
				if arr[j] >= p:
					i += 1
					arr[i], arr[j] = arr[j], arr[i]
			arr[i + 1], arr[h] = arr[h], arr[i + 1]
			return i + 1

		def quicksort(arr, l, h):
			if l < h:
				pi = partition(arr, l, h)
				quicksort(arr, l, pi - 1)
				quicksort(arr, pi + 1, h)
		quicksort(query_list, p, r)

		# end of quicksort
		
		et = time.process_time()
		res = et - st

		return [query_list, res]


if __name__ == '__main__':
	# the input type is either a, b or c 
	# corresponding to function_a, function_b and functin_c.
	input_type = sys.argv[1]

	elements_count = int(sys.argv[2])

	# input seed as 2, so we have the same randomly 
	# generated array.
	# you can change it for your testing.
	seed = sys.argv[3]
	
	obj = Solution()
	# the return value is an array of array.
	ret = obj.pa1_quicksort(input_type, elements_count, seed)
	print(ret)

