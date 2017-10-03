# Josh Weeks
# CSCI 4140
# File: c2e21.py
# Collaborators: authors of Natural Language Process with Python

# Write a program to guess the number of syllables contained in a text, making
# use of the CMU Pronouncing Dictionary.

import nltk
from nltk.corpus import cmudict
from nltk.corpus import brown

def guess_syllables(text):
  lowercase = [w.lower() for w in text]
  entries = nltk.corpus.cmudict.entries() 
  arpabet_vowels = ['AO', 'AA', 'IY', 'UW', 'EH', 'IH', 'UH', 'AH', 'AX', 'AE', 'EY', 'AY', 'OW', 'AW', 'OY', 'ER']
  english_vowels = ['a', 'e', 'i', 'o', 'u']
  words = [] #list of words
  prons = [] #list of pronunciation
  index = 0
  count = 0

  #fill words and prons with all cmudict word and pron
  for word, pron in entries:
    words.append(word)
    prons.append(pron)

  #count syllables in given text
  for word in lowercase:
    #count syllables with cmudict pronunciations
    if word in words:
      index = words.index(word) 
      for vowel in arpabet_vowels:
        for pron in prons[index]:
          if vowel in pron:
            count = count + 1 #increment count by arphabet vowels
    #count syllables without cmudict pronunciations when the word does not exist in words
    else:
      for vowel in english_vowels:
        count = count + word.count(vowel) #increment count syllables by english vowels

  return count

#testing

sent = 'Hello have a good day'.split()
ans = guess_syllables(sent)
print(ans) #6 syllables

