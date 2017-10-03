# Midterm question 7 Program
# Josh Weeks
# mt7.py
# command line form python3 mt7.py <document> <numSentences> <maxLength>
# <document> is the prefix of the Gutenberg book
# <numSentences> is the number of sentences to be printed
# <maxLength> is the maximum word length of a printable sentence

# Required imports
import nltk
import re,sys
from nltk.corpus import gutenberg
from operator import itemgetter

#--------------------------------------------------------------------------
# summarize(document,numSent,maxLength) calculates the numSent highest scoring
# sentences whose word length does not exceed maxLength and prints them out
# in the order they appear in document
# scoring is sum of word frequencies

def summarize(document,numSent,maxLength):

#  Use appropriate specification of nltk.Text to generate the words for
#  calculating the frequency distribution.  DO NOT normalize for case

  text = nltk.Text(nltk.corpus.gutenberg.words(document))
  fdist = nltk.FreqDist([w for w in text])

#  Use appropriate specification of nltk.sent_tokenize to generate the list
#  of sentences in the document.

  raw_text = nltk.corpus.gutenberg.raw(document)
  sents = nltk.sent_tokenize(raw_text)
  tokenized_sents2 = [nltk.word_tokenize(sent) for sent in sents]
  tokenized_sents = [sent for sent in tokenized_sents2 if len(sent) <= maxLength]

#  Use appropriate regular expression functionality to generate a parallel
#  list of the sentences in the document broken down into the actual words
#  (eliminating special characters)
#  NOTE: for our purpose words consist of 1 or more alphanumeric characters
#  NOTE: DO NOT normalize for case
  
  clean_sents = [[word for word in sent if re.search('\w+', word)]for sent in tokenized_sents]
  print(clean_sents[1])

#  Code to finish the processing goes here.  The form of the sentence to
#  be printed should be the form produced by breaking down the original list
#  into actual words

  sents_scores = []

  for sent_index in range(len(clean_sents)):
    sent = clean_sents[sent_index]
    score = 0
    score = sum(fdist[word] for word in sent)
    tup = sent, score
    sents_scores.append(tup)

  sents_scores = sorted(sents_scores, key=itemgetter(1), reverse=True)
  sents_scores = sents_scores[:numSent]
  
  list_sents = [sent for (sent, _) in sents_scores]

  string_answers = []

  for sent_index in range(len(list_sents)):
    sent = list_sents[sent_index]
    string_answer = ' '.join(sent)
    string_answers.append(string_answer)

  return '\n'.join(string_answers)

# summarize definition ends here
#--------------------------------------------------------------------------
# initial processing: grabs the command line arguments and calls summarize

docname = sys.argv[1]
numsentences = int(sys.argv[2])
maxL = int(sys.argv[3])
print(summarize (docname+".txt",numsentences,maxL))
