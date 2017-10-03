# Josh Weeks
# soundex.py
# CSCI 4140
# Collaborators: Ryan K.

import sys
import nltk
import re

def wordmap(token) :
  if token.isalpha():
    
    
    name = token.upper()
  
    soundex = ""
    # add initial character
    soundex += name[0]

    dictionary = {"BFPV": "1", "CGJKQSXZ":"2", "DT":"3", "L":"4", "MN":"5", "R":"6", "AEIOUY":".", "HW": ""}

    # loop through characters in name
    for character in name:
      # get dictionary key
      for key in dictionary.keys():
        # character is part of key
        if character in key:
          # number given by dictionary
          number = dictionary[key]
          # check for multiple occurances of a number
          if number != soundex[-1]:
            soundex += number
    # make . become a space replacing a,e,i,o,u,h,w,y
    soundex = soundex.replace(".", "")
    # first 4 characters
    soundex = soundex[:4].ljust(4, "0")
  
    return soundex
    
  else:
    soundex = ""
    return soundex
# Driver code for the program
# sys.argv[1] should be the name of the input file
# sys.argv[0] will be the name of this file

for line in open(sys.argv[1]).readlines():
  text = nltk.word_tokenize(line.lower())
  for token in text:
    print (wordmap(token),end=' ')
  print()  # This prints new line at the end of processing a line
