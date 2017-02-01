import sys

file_one = open(sys.argv[1])
file_two = open(sys.argv[2])

s1 = file_one.read()
s2 = file_two.read()

print len(s1)
print len(s2)

#Based on https://en.wikipedia.org/wiki/Longest_common_substring_problem#Pseudocode
L = [[0] * (len(s2) + 1) for i in range(len(s1) + 1)]
z = 0 #length of curent longest substring
ret = []
for i in range(1, len(s1)+1):
	for j in range(1, len(s2)+1):
		if s1[i-1] == s2[j-1]:
			if i == 1 or j == 1:
				L[i][j] = 1
			else:
				L[i][j] = L[i-1][j-1] + 1
			if L[i][j] > z:
				z = L[i][j]
				ret.append(i)
			elif L[i][j] == z:
				pass #this part confuses me
		else:
			L[i][j] = 0

print z
