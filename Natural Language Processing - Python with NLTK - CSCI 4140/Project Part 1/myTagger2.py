# Project Part 1
# Josh Weeks
# myTagger.py

import nltk
from nltk.corpus import brown
import random
import math

# Regular Expression tagger
patterns = [
     (r'.*ing$', 'VBG'),               # gerunds
     (r'.*ed$', 'VBD'),                # simple past
     (r'.*es$', 'VBZ'),                # 3rd singular present
     (r'.*ould$', 'MD'),               # modals
     # (r'.*/s$', 'NN$'),               # possessive nouns
     (r'.*s$', 'NNS'),                 # plural nouns
     (r'^-?[0-9]+(.[0-9]+)?$', 'CD')  # cardinal numbers
     # (r'.*', 'NN')                     # nouns (default)
]

documents = [(list(brown.words(fileid)), category)
             for category in brown.categories()
             for fileid in brown.fileids(category)]
random.shuffle(documents)

# N-fold cross validation for genre(category)
print("Results by genre") 
print('Test Fold' + ' '*(9) + 'Result' + ' '*(14))
subsize = int(len(documents))
for i in range(len(documents)):
  testing = documents[i * subsize:][:subsize]
  training = documents[:i * subsize] + documents[(i+1) * subsize:]
  t0 = nltk.DefaultTagger('NN')
  t1 = nltk.RegexpTagger(patterns, backoff = t0)
  t2 = nltk.UnigramTagger(training, backoff = t1)
  t3 = nltk.BigramTagger(training, backoff = t2)
  print(i, ' '*(15), round(t3.evaluate(training) * 100, 2))



documents = [list(brown.tagged_words(fileid), fileid)
             for category in brown.categories()
             for fileid in brown.fileids(category)]
random.shuffle(documents)

# N-fold cross validation for fileid(source)
print("Results by fileid") 
num_folds = 10
sub_size = int(len(documents)/num_folds)
print('Test Fold' + ' '*(9) + 'Result' + ' '*(14))
for i in range(num_folds):
  testing = documents[i * sub_size:][:sub_size]
  training = documents[:i * sub_size] + documents[(i+1) * sub_size:]
  t0 = nltk.DefaultTagger('NN')
  t1 = nltk.RegexpTagger(patterns, backoff = t0)
  t2 = nltk.UnigramTagger(train = training, backoff = t1)
  t3 = nltk.BigramTagger(training, backoff = t2)
  print(i, ' '*(15), round(t3.evaluate(training) * 100, 2))


brown_tagged_sents = brown.tagged_sents()

# N-fold cross validation for sentence
print("Results by sentence") 
subset_size = int(len(brown_tagged_sents)/num_folds)
# Table (Formatting)
print('Test Fold' + ' '*(9) + 'Result' + ' '*(14))
for i in range(num_folds):
  # Separating the Training and Testing Data
  testing_this_round = brown_tagged_sents[i * subset_size:][:subset_size]
  training_this_round = brown_tagged_sents[:i * subset_size] + brown_tagged_sents[(i+1) * subset_size:]
  # train using training_this_round CH 5 SEC 5.4 Combining Taggers
  t0 = nltk.DefaultTagger('NN')
  t1 = nltk.RegexpTagger(patterns, backoff = t0)
  t2 = nltk.UnigramTagger(training_this_round, backoff = t1)
  t3 = nltk.BigramTagger(training_this_round, backoff = t2)
  print(i, ' '*(15), round(t3.evaluate(training_this_round) * 100, 2))


