# Josh Weeks
# CSCI 4140
# File: c2e15.py
# Collaborators: authors of Natural Language Process with Python

# Write a program to find all words that occur at least three times in the Brown
# Corpus

import nltk
from nltk.corpus import brown

# word_freq takes corpus and a number. The number represents the minimum number of occurances
# of all words to be displayed from the given corpus.
def word_freq(corpus, number):
  fdist = nltk.FreqDist([w.lower() for w in corpus.words()])
  words = [' '] #will contain list of words that occur > number
  for word in fdist:
    if fdist[word] >= number:
      words.append(word) #append the word if it occurs more than the given number parameter
  return words

#testing

#print(many_words(brown, 3)) #this prints the list of the words

print('number of words that occur three or more times: ') 
print(len(word_freq(brown, 3)))

