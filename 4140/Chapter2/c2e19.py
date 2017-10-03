# Josh Weeks
# CSCI 4140
# File: c2e21.py
# Collaborators: authors of Natural Language Process with Python

# Write a program to create a table of word frequencies by genre, like the one given
# in Section 2.1 for modals. Choose your own words and try to find words whose
# presence (or absence) is typical of a genre. Discuss your findings.

import nltk
from nltk.corpus import brown

def word_frequencies(text, words):
  cfd = nltk.ConditionalFreqDist(
    (genre, word)
    for genre in ['fiction', 'science_fiction', 'news', 'mystery', 'adventure']
    for word in text.words(categories=genre))

  return cfd.tabulate(samples=words)

#expect: science fiction
word_frequencies(brown, ['space', 'universe', 'alien', 'android', 'force', 'field', 'planet', 'future', 'ship'])

#words related to ship
word_frequencies(brown, ['fly', 'flying', 'flew', 'water', 'float', 'station', 'send', 'trade', 'merchant', 'recieve', 'smuggle'])

#words related to ship
word_frequencies(brown, ['send', 'sending', 'sent', 'deliver', 'delivered', 'package'])

#expect: unknown
word_frequencies(brown, ['death', 'dream'])

#words related to planet
word_frequencies(brown, ['terrain', 'blue', 'color', 'gas', 'big', 'large', 'small'])

#expect: news
word_frequencies(brown, ['today', 'job', 'jobs', 'money', 'found', 'discovered', 'discover'])

#expect: mystery
word_frequencies(brown, ['clue', 'clues', 'gun', 'murder', 'sleep', 'find', 'suspense'])


