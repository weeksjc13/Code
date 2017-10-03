# Josh Weeks
# piglatin.py
# CSCI 4140
# Collaborators: Ryan K.

import sys
import nltk
import re

def wordmap(token):
  newForm = token

  if token.isalpha():
    if len(token) == 1:
      return newForm
    # starts with vowel
    if re.search('^a|^e|^i|^o|^u', token):
      newForm = token + 'yay'
      return newForm
    # starts with consonant
    else:
      # y followed by a vowel is treated as a vowel
      if re.search('^yb|^yc|^yd|^yf|^yg|^yh|^yj|^yk|^yl|^ym|^yn|^yp|^yq|^yr|^ys|^yt|^yv|^yw|^yx|^yy|^yz', token):
        newForm = token + 'yay'
        return newForm
      firstLetter = token[0]
      end = firstLetter + 'ay'
      newForm = newForm[1:] + end
      return newForm

  else:
    # contains symbols
    return token

# Driver code for the program
# sys.argv[1] should be the name of the input file
# sys.argv[0] will be the name of this file

for line in open(sys.argv[1]).readlines():
  text = nltk.word_tokenize(line.lower())
  for token in text:
    print (wordmap(token),end=' ')
  print()  # This prints new line at the end of processing a line




