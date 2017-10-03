# Josh Weeks
# CSCI 4140
# File: c2e16.py
# Collaborators: authors of Natural Language Process with Python 

# Write a program to generate a table of lexical diversity scores (i.e., token/type
# ratios), as we saw in Table 1-1. Include the full set of Brown Corpus genres
# ( nltk.corpus.brown.categories() ). Which genre has the lowest diversity (greatest
# number of tokens per type)? Is this what you would have expected?

# Answer: science_fiction has the lowest diversity. This makes sense because this genre
# often reuses nouns that are made up.

import nltk
from nltk.corpus import brown

def ld(corpus):
  for genre in corpus.categories():
    ld = len(corpus.words(categories=genre))/len(set(corpus.words(categories=genre))) #token/type, set elimating the duplicates
    print(genre + ':', ld) #formatting
  return 0

#testing

print(ld(brown))

