# Project Part 1
# Josh Weeks
# myTagger.py



import nltk
import random
import math
from nltk import word_tokenize
from nltk.corpus import brown



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



# N-fold cross validation for sentence
brown_tagged_sents = brown.tagged_sents()

num_folds = 10
subset_size = int(len(brown_tagged_sents)/num_folds)
print("Results by sentence") 
print('Test Fold' + ' '*(9) + 'Result')
for i in range(num_folds):
  
  # Separating the Training and Testing Data
  training_this_round = brown_tagged_sents[i * subset_size:][:subset_size]
  testing_this_round = brown_tagged_sents[:i * subset_size] + brown_tagged_sents[(i+1) * subset_size:]
  # train using training_this_round CH 5 SEC 5.4 Combining Taggers
  t0 = nltk.DefaultTagger('NN')
  t1 = nltk.RegexpTagger(patterns, backoff = t0)
  t2 = nltk.UnigramTagger(training_this_round, backoff = t1)
  t3 = nltk.BigramTagger(training_this_round, backoff = t2)
  print(i, ' '*(15), round(t3.evaluate(testing_this_round) * 100, 2))
print('\n')



# N-fold cross validation for genre
documents = [(brown.tagged_sents(categories = category), category)
             for category in brown.categories()]

training_list1, training_list2 = zip(*documents)

print("Results by genre")
num_folds = len(training_list1)
print('Test Fold' + ' '*(13) + 'Result' + ' '*(14))
for i in range(num_folds):
  # Separating the Training and Testing Data
  training_this_round = brown.tagged_sents(categories = training_list2[i])
  testing_this_round = brown.tagged_sents(categories = training_list2[:i] + training_list2[i+1:])
  # train using training_this_round CH 5 SEC 5.4 Combining Taggers
  t0 = nltk.DefaultTagger('NN')
  t1 = nltk.RegexpTagger(patterns, backoff = t0)
  t2 = nltk.UnigramTagger(training_this_round, backoff = t1)
  t3 = nltk.BigramTagger(training_this_round, backoff = t2)
  print(training_list2[i], ' '*(20-len(training_list2[i])), round(t3.evaluate(testing_this_round) * 100, 2))
print('\n')



# N-fold cross validation for fileid
documents = [(brown.tagged_sents(fileids = fileid), fileid)
             for category in brown.categories()
             for fileid in brown.fileids()]

training_list1, training_list2 = zip(*documents)

print("Results by fileid")
num_folds = 10
subset_size = int(len(brown.fileids())/num_folds)
print('Test Fold' + ' '*(9) + 'Result')
for i in range(num_folds):
  # Separating the Training and Testing Data
  training_this_round = brown.tagged_sents(fileids = training_list2[i * subset_size:][:subset_size])
  testing_this_round = brown.tagged_sents(fileids = training_list2[:i] + training_list2[i+1:])
  # train using training_this_round CH 5 SEC 5.4 Combining Taggers
  t0 = nltk.DefaultTagger('NN')
  t1 = nltk.RegexpTagger(patterns, backoff = t0)
  t2 = nltk.UnigramTagger(training_this_round, backoff = t1)
  t3 = nltk.BigramTagger(training_this_round, backoff = t2)
  print(i, ' '*(15), round(t3.evaluate(testing_this_round) * 100, 2))
print('\n')














