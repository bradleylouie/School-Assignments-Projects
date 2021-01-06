# School-Assignments-Projects
*SquareMatrix*

  Very basic class implementing the rule of the Big Five; uses raw pointers and simple arithmetic to create a 2D matrix with a few operations.
  
*KeywordsInFile*

  Reads two plaintext files - one containing keywords and the other a large text - constructing maps of the keywords and their occurrences within the text.
  Uses properties of BSTs and hashtables to look up these keywords, their total occurrences, and their occurrences per line in O(1) or O(logN) time.
  The contents of the files are parsed for contiguous alphabetical characters only - all others are converted to spaces before being streamed into the data structures as separate words (e.g. "it's" separates into "it" and "s").

*Field*

  Given a 2D vector of integers, computes the sum of all the numbers in a rectangle formed by two X,Y coordinates in O(1) time. This is accomplished by dynamically calculating all of the sums during the construction of the class. The coordinates given to the weight function do not have to be ordered from top to bottom nor left to right.
  It can also compute the cost of the cheapest path from the top-left corner of the field to the bottom-right where the only possible moves are right and down.
  
*AudioProcessor*

  Given a vector of signed integers, performs several audio-related functions such as compression, silence removal, stretching, and normalization.
