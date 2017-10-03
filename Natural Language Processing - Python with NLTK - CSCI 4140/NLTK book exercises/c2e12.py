# Josh Weeks
# CSCI 4140
# File: c2e12.py
# Collaborators: authors of Natural Language Process with Python 

# The CMU Pronouncing Dictionary contains multiple pronunciations for certain
# words. How many distinct words does it contain? What fraction of words in this
# dictionary have more than one possible pronunciation?

# Answer: 123455 distinct words. 9241/123455 fraction of words with more than
# one pronunciation.

import nltk
from nltk.corpus import cmudict

cmu = cmudict.dict()

key_count = 0

#find distinct words
for key in cmu.keys():
  key_count = key_count + 1

mult_pron_count = 0

#find words with more than one pronunciation
for key in cmu.keys():
  if(len(cmu[key]) > 1):
    mult_pron_count = mult_pron_count + 1

#testing

print(mult_pron_count) #9241 words with more than one pronunciation
print(' / ')
print(key_count) #123455 distinct

