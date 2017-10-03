# Josh Weeks
# CSCI 4140
# File: c2e04.py
# Collaborators: authors of Natural Language Process with Python 

# Read in the texts of the State of the Union addresses, using the state_union corpus
# reader. Count occurrences of men , women , and people in each document. What has
# happened to the usage of these words over time?

# Answer: 'people' was used more than 'men' or 'women'. 'men' was used more than
# 'women' in most years. In the span of years 2004-2006, 'women' was used equally or
# more often than 'men'.

import nltk
from nltk.corpus import state_union

cfd = nltk.ConditionalFreqDist(
  (target, fileid[:4])  # first 4 letter in fileid
  for fileid in state_union.fileids()
  for w in state_union.words(fileid)
  for target in ['men', 'women', 'people']
  if w.startswith(target) and w.endswith(target))

#testing

cfd.tabulate()  # had to zoom out in terminal to get a decent view

