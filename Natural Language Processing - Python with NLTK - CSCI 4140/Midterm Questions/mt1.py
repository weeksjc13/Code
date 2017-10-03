# Josh Weeks
# CSCI 4140
# File: c2e08.py
# Collaborators: authors of Natural Language Process with Python 

import nltk
from nltk.corpus import brown
from collections import defaultdict

brown_tagged = brown.tagged_words(tagset='universal')

def find_ngrams(input_list, n):
  return list(zip(*[input_list[i:] for i in range(n)]))

bigrams = find_ngrams(brown_tagged, 2)

print()

# Which parts of speech never immediately follow a conjunction (a word with part of speech tag CONJ)?

pos2_bigrams_conj = [pos2 for ((word1, pos1),(word2,pos2)) in bigrams if pos1 == 'CONJ']

fdist = nltk.FreqDist(pos2_bigrams_conj)
ans = [pos for pos in set(pos2_bigrams_conj) if fdist[pos] == 0]
print(ans)

print()

# There exists no part of speech in the universal tagset that never immediately follow a conjuction in the brown corpus.

###

# Excluding NOUN and VERB, which are the three most frequent parts of speech that immediately follow a CONJ word?

pos2_bigrams_mostfreq = [pos2 for ((word1, pos1),(word2,pos2)) in bigrams if pos2 != 'NOUN' and pos2 != 'VERB' and pos1 == 'CONJ']

fdist2 = nltk.FreqDist(pos2_bigrams_mostfreq)
ans2 = [tag for (tag,_) in fdist2.most_common(3)]
print(ans2)

print()

# Excluding NOUN and VERB these are the three most frequent parts of speech that immediately follow a conjunction in the brown corpus: 1. DET 5772 2. ADJ 4272 3. ADV 3484
