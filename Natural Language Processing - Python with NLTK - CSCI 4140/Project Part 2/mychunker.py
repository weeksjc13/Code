# Project Part 2
# Josh Weeks
# myChunker.py

import nltk, re, pprint, sys
from nltk.corpus import conll2000
from nltk.corpus import treebank_chunk
from nltk.probability import FreqDist



train_sents = conll2000.chunked_sents('train.txt', chunk_types=['VP'])
test_sents = conll2000.chunked_sents('test.txt', chunk_types=['VP'])



print("--- Baseline chunker ---")
cp = nltk.RegexpParser("")
print(cp.evaluate(test_sents))
print()



class ConsecutiveVPChunkTagger(nltk.TaggerI):

  def __init__(self, train_sents):
    train_set = []
    for tagged_sent in train_sents:
      untagged_sent = nltk.tag.untag(tagged_sent)
      history = []
      for i, (word, tag) in enumerate(tagged_sent):
        featureset = vpchunk_features(untagged_sent, i, history)
        train_set.append( (featureset, tag) )
        history.append(tag)
    self.classifier = nltk.NaiveBayesClassifier.train(train_set)

  def tag(self, sentence):
    history = []
    for i, word in enumerate(sentence):
      featureset = vpchunk_features(sentence, i, history)
      tag = self.classifier.classify(featureset)
      history.append(tag)
    return zip(sentence, history)



class ConsecutiveVPChunker(nltk.ChunkParserI):
  def __init__(self, train_sents):
    tagged_sents = [[((w,t),c) for (w,t,c) in nltk.chunk.tree2conlltags(sent)]
                        for sent in train_sents]
    self.tagger = ConsecutiveVPChunkTagger(tagged_sents)

  def parse(self, sentence):
    tagged_sents = self.tagger.tag(sentence)
    conlltags = [(w,t,c) for ((w,t),c) in tagged_sents]
    return nltk.chunk.conlltags2tree(conlltags)



def vpchunk_features(sentence, i, history):
  word, pos = sentence[i]
  if i == 0:
    prevword, prevpos = "<START>", "<START>"
  else:
    prevword, prevpos = sentence[i-1]
  if i == len(sentence)-1:
    nextword, nextpos = "<END>", "<END>"
  else:
    nextword, nextpos = sentence[i+1]
  return {"pos": pos,
          "word": word,
          "prevpos": prevpos,
          "nextpos": nextpos,
          "prevpos+pos": "%s+%s" % (prevpos, pos),
          "pos+nextpos": "%s+%s" % (pos, nextpos),
          #"tags-since-startwithv": tags_since_startwithvb(sentence, i)}
          "tags-since-vbd": tags_since_vbd(sentence, i)}
          #"tags_since_vbz": tags_since_vbz(sentence, i)}


#scores are higher then tag_since_vbd
def tags_since_vbd(sentence, i):
  tags = set()
  for word, pos in sentence[:i]:
    if (pos == 'VBD'):
      tags = set()
    else:
      tags.add(pos)
  return '+'.join(sorted(tags))

#scores are lower than tags_since_vbz
def tags_since_vbz(sentence, i):
  tags = set()
  for word, pos in sentence[:i]:
    if (pos == 'VBZ'):
      tags = set()
    else:
      tags.add(pos)
  return '+'.join(sorted(tags))

#starts with v, scores lower than tags_since_vbd
def tags_since_startwithvb(sentence, i):
  tags = set()
  for word, pos in sentence[:i]:
    if (pos.startswith('VB')):
      tags = set()
    else:
      tags.add(pos)
  return '+'.join(sorted(tags))




print("--- My VP chunker ---")
chunker = ConsecutiveVPChunker(train_sents)
print(chunker.evaluate(test_sents))
print()
