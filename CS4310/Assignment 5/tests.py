from lcs import *

def test_case(X, Y, case):
	thearr = lcs(X, Y)
	print "Test case " + str(case) + ". X: " + X + " Y: " + Y
	print "LCS Table:"
	print str(thearr).replace('], ', ']\n').replace('[','').replace(']','').replace(',',' ')
	print "Length of subsequence: " + str(thearr[len(X)][len(Y)])
	print "Longest subsequence: " + str(reverse_lcs(X, Y, thearr)) + "\n\n"

#Case 1:
test_case("CGATAATTGAGA", "GTTCCTAATA", 1)
#Case 2:
test_case("ABCDEFGH", "ACFGIKHM", 2)
#Case 3:
test_case("GAC", "AGCAT", 3)
#Case 4:
test_case("MZJAWXU", "XMJYAUZ", 4)
