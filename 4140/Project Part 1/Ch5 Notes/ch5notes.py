# Chapter 5 code
# Josh Weeks
# ch5notes.py

import nltk
from nltk.corpus import brown

# CH 5 SEC 5.1 Unigram Tagging
print("\nUnigram Tagging\n")

brown_tagged_sents = brown.tagged_sents(categories = 'news')
brown_sents = brown.sents(categories = 'news')
unigram_tagger = nltk.UnigramTagger(brown_tagged_sents)

print("brown_tagged_sents[2007] -> \n", brown_tagged_sents[2007], "\n")
print("brown_sents[2007] -> \n", brown_sents[2007], "\n")
print("unigram_tagger.tag(brown_sents[2007]) -> \n", unigram_tagger.tag(brown_sents[2007]), "\n")


# CH 5 SEC 5.2 Separating the Training and Testing Data
print("\nSeparating the Training and Testing Data\n")

size = int(len(brown_tagged_sents) * 0.9)
print("size -> ", size, "\n")
train_sents = brown_tagged_sents[:size]
test_sents = brown_tagged_sents[size:]
unigram_tagger = nltk.UnigramTagger(train_sents)
print("unigram_tagged.evaluate(test_sents) -> ", unigram_tagger.evaluate(test_sents), "\n")


# CH 5 SEC 5.3 General N-gram Tagging
print("\nGeneral N-gram Tagging\n")

bigram_tagger = nltk.BigramTagger(train_sents)
print("bigram_tagger.tag(brown_sents[2007]) -> \n", bigram_tagger.tag(brown_sents[2007]), "\n")
unseen_sent = brown_sents[4203]
print("bigram_tagger.tag(unseen_sent) -> \n", bigram_tagger.tag(unseen_sent), "\n")
print("bigram_tagger.evaluate(test_sents) -> ", bigram_tagger.evaluate(test_sents), "\n")


# CH 5 SEC 5.4 Combining Taggers
print("\nCombining Taggers\n")

t0 = nltk.DefaultTagger('NN')
t1 = nltk.UnigramTagger(train_sents, backoff = t0)
t2 = nltk.BigramTagger(train_sents, backoff = t1)
print("t2.evaluate(test_sents) -> ", t2.evaluate(test_sents), "\n")


# CH 5 SEC 5.7 Performance Limitations
print("\nPerformance Limitations\n")

cfd = nltk.ConditionalFreqDist(
           ((x[1], y[1], z[0]), z[1])
           for sent in brown_tagged_sents
           for x, y, z in nltk.trigrams(sent))
ambiguous_contexts = [c for c in cfd.conditions() if len(cfd[c]) > 1]
sum_ambiguous_contexts = sum(cfd[c].N() for c in ambiguous_contexts) / cfd.N()
# 1/20 trigrams are ambigous, more than one meaning
print("sum(cfd[c].N() for c in ambiguous_contexts) / cfd.N() -> ", sum_ambiguous_contexts, "\n")

test_tags = [tag for sent in brown.sents(categories='editorial')
                for (word, tag) in t2.tag(sent)]
gold_tags = [tag for (word, tag) in brown.tagged_words(categories='editorial')]
#print("nltk.ConfusionMatrix(gold_tags, test_tags) -> \n", nltk.ConfusionMatrix(gold_tags, test_tags), "\n")
