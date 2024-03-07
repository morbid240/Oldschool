'''
Please use the code template below to complete your assignment.
Your code must be written in pa0 method. 
Do not change any other code. 
The evaluation code uses this templete to run your test cases.
Any changes other than pa0 method would cause the evaluation program
failure and you will not get credit for your submission.

name: Malcolm Roddy
studentID: 030573684

assignment:PA0
'''


import sys

class Solution:

	def data_conversion(self, data, convert_to):
		if convert_to == "int":
			return int(data)

		if convert_to == "list":
			new_input = []
			data = data.split(",")		
			for item in data: 
				new_input.append(int(item))
			
			return new_input

		if convert_to == "bool":
			return bool(data)


	def pa0 (self, s: list ) -> list:
		sorted_list = s
		# your code must return a list
		# your bubble sort goes here
		size = len(sorted_list)
		swapped = False
		for i in range(size-1):
			for j in range(0, size-i-1):
				if sorted_list[j] > sorted_list[j+1]:
					swapped = True
					temp = sorted_list[j]
					sorted_list[j] = sorted_list[j+1]
					sorted_list[j + 1] = temp
		return sorted_list


if __name__ == '__main__':
	# argv takes the input as a string.
	# to run pa1 we need to convert argv (or input data)
	# to the datatype that pa0 accepts.
	# data_conversion function converts an string to 
	# convert_to variable suitable for pa1 program input. 
	# "convert_to" variable can be one of the followings:
	# "list", "int", "bool"
	# note: a list of integers should be entered as a 
	# comma separated sequence in command line as input for a program.
	# For example, myproject.py 1,2,3,4,5

    # Setting convert_to variable
	convert_to = "list"

	# Read the input string from the command line
	s = sys.argv[1]

	# Craeting an object from Solution class
	obj = Solution()

	# Call "data_conversion" method to convert s (input string )
	# to a desire input datatype that is set for convert_to
	s = obj.data_conversion(s, convert_to)

	# calling tha pa0 method to run the program
	ret = obj.pa0(s)

	print(ret)
