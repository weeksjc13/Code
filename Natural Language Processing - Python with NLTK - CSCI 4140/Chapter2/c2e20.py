# Josh Weeks
# CSCI 4140
# File: c2e20.py
# Collaborators: authors of Natural Language Process with Python

# Write a function word_freq() that takes a word and the name of a section of the
# Brown Corpus as arguments, and computes the frequency of the word in that sec-
# tion of the corpus.

import nltk
from nltk.corpus import brown

#Takes a word and a genre from the brown corpus. Gives frequency of given word in the genre's text.
def word_freq(word, genre): 
  fdist = nltk.FreqDist([w.lower() for w in nltk.corpus.brown.words(categories=genre)])
  return fdist[word]

#testing

ans = word_freq('the', 'news')
print(ans) #6386
