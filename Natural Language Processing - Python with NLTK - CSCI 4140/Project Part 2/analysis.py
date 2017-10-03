# Project Part 2
# Josh Weeks
# analysis.py

import nltk, re, pprint, sys
from nltk.corpus import conll2000
from nltk.corpus import treebank_chunk
from nltk.probability import FreqDist

test_sents = conll2000.chunked_sents('test.txt', chunk_types=['VP'])
train_sents = conll2000.chunked_sents('train.txt', chunk_types=['VP'])

# Calculate statistics
def get_seq(train_sents):
  tuples = []
  for row in train_sents:
    for t in row:
      nontree = []
      try:
        t.label()
      except AttributeError:
        nontree = []
      else:
        if(t.label() == 'VP'):
          leaves = t.leaves()
          tuples.append(leaves)
        
  return tuples



tups = get_seq(train_sents)



poslist = []

for alist in tups:
  newlist = [pos for (word, pos) in alist]
  poslist.append(' '.join(newlist))



def count_freq(tuples):
  fdist = FreqDist(tuples)
  for seq in fdist.most_common():
    print(seq)

count_freq(poslist)












