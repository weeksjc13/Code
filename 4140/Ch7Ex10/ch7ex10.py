# ch7ex10
# Josh Weeks
# ch7ex10.py

# The bigram chunker scores about 90% accuracy. Study its errors and try to work out why it doesn't get 100% accuracy. Experiment with trigram chunking. Are you able to improve the performance any more?

import nltk.chunk
import nltk.corpus, nltk.tag



# training a chunker
# instead of training on (word, tag) sequences, we train on (tag, iob) sequences where iob is a chunk tag defined in conll2000 corpus
def conll_tag_chunks(chunk_sents):
    tag_sents = [nltk.chunk.tree2conlltags(tree) for tree in chunk_sents]
    return [[(t, c) for (w, t, c) in chunk_tags] for chunk_tags in tag_sents]



# chunker accuracy
# ngram taggers
def ubt_conll_chunk_accuracy(train_sents, test_sents):
    train_chunks = conll_tag_chunks(train_sents)
    test_chunks = conll_tag_chunks(test_sents)
 
    u_chunker = nltk.tag.UnigramTagger(train_chunks)
    print('u:', nltk.tag.accuracy(u_chunker, test_chunks))
 
    ub_chunker = nltk.tag.BigramTagger(train_chunks, backoff=u_chunker)
    print('ub:', nltk.tag.accuracy(ub_chunker, test_chunks))
 
    ubt_chunker = nltk.tag.TrigramTagger(train_chunks, backoff=ub_chunker)
    print('ubt:', nltk.tag.accuracy(ubt_chunker, test_chunks))
 
    ut_chunker = nltk.tag.TrigramTagger(train_chunks, backoff=u_chunker)
    print('ut:', nltk.tag.accuracy(ut_chunker, test_chunks))
 
    utb_chunker = nltk.tag.BigramTagger(train_chunks, backoff=ut_chunker)
    print('utb:', nltk.tag.accuracy(utb_chunker, test_chunks))
 
# conll chunking accuracy test
conll_train = nltk.corpus.conll2000.chunked_sents('train.txt')
conll_test = nltk.corpus.conll2000.chunked_sents('test.txt')
ubt_conll_chunk_accuracy(conll_train, conll_test)
 
# treebank chunking accuracy test
treebank_sents = nltk.corpus.treebank_chunk.chunked_sents()
ubt_conll_chunk_accuracy(treebank_sents[:2000], treebank_sents[2000:])
