# Josh Weeks
# CSCI 4140
# File: c2e08.py
# Collaborators: authors of Natural Language Process with Python 

# Define a conditional frequency distribution over the Names Corpus that allows
# you to see which initial letters are more frequent for males versus females.

import nltk
from nltk.corpus import names

cfd = nltk.ConditionalFreqDist(
  (fileid, name[0]) #name[0] is the first character
  for fileid in names.fileids() #loop through files
  for name in names.words(fileid)) #get words from each file

#testing

cfd.tabulate()
