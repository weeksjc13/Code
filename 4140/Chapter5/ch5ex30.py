import nltk
from nltk.corpus import brown

#Preprocess the Brown News data by replacing low frequency words with UNK, but leaving the tags untouched. Now train and evaluate a bigram tagger on this data. How much does this help? What is the contribution of the unigram tagger and default tagger now?

# getting the data ready

brown_tagged_sents = brown.tagged_sents(categories='news')

# finds the most common 100

fd = nltk.FreqDist(brown.words())
most_common = [tag for (tag,__) in fd.most_common(100)]

def unk(word, tag):
    if word in most_common:
        return word
    else:
        return 'UNK'

brown_tagged_sents = most_common

size = int(len(brown_tagged_sents) * 0.9)
train_sents = brown_tagged_sents[:size]
test_sents = brown_tagged_sents[size:]

t0 = nltk.DefaultTagger('NN')
t1 = nltk.UnigramTagger(train_sents, backoff=t0)
t2 = nltk.BigramTagger(train_sents, backoff=t1)

print(t2.evaluate(test_sents))
