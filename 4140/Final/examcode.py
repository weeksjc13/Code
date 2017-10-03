# Final
# Josh Weeks
# examcode.py

import nltk, re, pprint, sys
from nltk.corpus import conll2000
from nltk.corpus import treebank_chunk
from nltk.probability import FreqDist
from nltk.corpus import wordnet as wn

# number 5
print("number 5 \n")

wsj = nltk.corpus.treebank.tagged_words()
cfd2 = nltk.ConditionalFreqDist((tag, word) for(word, tag) in wsj)
targets = list(cfd2['VBN'])

ans = []

for i in range(len(wsj)):
  if wsj[i][1] == 'VBN':
    ans.append(wsj[i-1])
        
print("list length ", len(ans))
print("set length ", len(set(ans)))
print()

# number 4 supergloss(s) takes a synset s as its argument and returns a string consisting of the concatination of the definition of s and the definition of all the hypernyms and hyponyms of s... use newline character

print("number 4 \n")

def supergloss(s):
  string = ""
  string = string + wn.synset(s).definition() + "\n"
  string = string + "HYPONYMS: \n"
  for hypo in wn.synset(s).hyponyms():
    string = string + hypo.definition() + "\n"
  string = string + "HYPERNYMS: \n"
  for hyper in wn.synset(s).hypernyms():
    string = string + hyper.definition() + "\n"
  return string

print(supergloss('tree.v.03'))
print(supergloss('play.n.03'))


