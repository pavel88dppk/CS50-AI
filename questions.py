import nltk
import sys
import os
import string
import numpy as np
import glob

FILE_MATCHES = 1
SENTENCE_MATCHES = 1


def main():

    # Check command-line arguments
    if len(sys.argv) != 2:
        sys.exit("Usage: python questions.py corpus")

    # Calculate IDF values across files
    files = load_files(sys.argv[1])
    file_words = {
        filename: tokenize(files[filename])
        for filename in files
    }
    file_idfs = compute_idfs(file_words)

    # Prompt user for query
    query = set(tokenize(input("Query: ")))

    # Determine top file matches according to TF-IDF
    filenames = top_files(query, file_words, file_idfs, n=FILE_MATCHES)

    # Extract sentences from top files
    sentences = dict()
    for filename in filenames:
        for passage in files[filename].split("\n"):
            for sentence in nltk.sent_tokenize(passage):
                tokens = tokenize(sentence)
                if tokens:
                    sentences[sentence] = tokens

    # Compute IDF values across sentences
    idfs = compute_idfs(sentences)

    # Determine top sentence matches
    matches = top_sentences(query, sentences, idfs, n=SENTENCE_MATCHES)
    for match in matches:
        print(match)


def load_files(directory):
    """
    Given a directory name, return a dictionary mapping the filename of each
    `.txt` file inside that directory to the file's contents as a string.
    """
    path = os.getcwd()
    newwpath = os.path.join(path, directory)
    files = {}
    os.chdir(directory)
    myFiles = glob.glob('*.txt')

    for file in myFiles:
        newpath = os.path.join(newwpath, file)
        with open(newpath, "r", encoding='utf8') as f:
            files[file] = f.read()

    return(files)


def tokenize(document):
    """
    Given a document (represented as a string), return a list of all of the
    words in that document, in order.
    Process document by coverting all words to lowercase, and removing any
    punctuation or English stopwords.
    """
    token = nltk.word_tokenize(document.lower())

    for word in token:
        if word in nltk.corpus.stopwords.words("english"):
            token.remove(word)
            continue
        for letter in word:
            if letter in string.punctuation:
                token.remove(word)
                break

    return token


def compute_idfs(documents):
    """
    Given a dictionary of `documents` that maps names of documents to a list
    of words, return a dictionary that maps words to their IDF values.
    Any word that appears in at least one of the documents should be in the
    resulting dictionary.
    """
    number = 0
    for key in documents:
        number += 1
    words = {}
    for key in documents:
        for word in documents[key]:
            seen = 0
            for key2 in documents:
                for word2 in documents[key2]:
                    if word2 == word:
                        seen += 1
                        break
            idf = np.log(number/seen)
            words[word] = idf

    return words

def top_files(query, files, idfs, n):
    """
    Given a `query` (a set of words), `files` (a dictionary mapping names of
    files to a list of their words), and `idfs` (a dictionary mapping words
    to their IDF values), return a list of the filenames of the the `n` top
    files that match the query, ranked according to tf-idf.
    """
    tf_idfs = {}
    for file in files:
        tf_idf = 0
        for word in query:
            tf_idf += files[file].count(word) * idfs[word]
        tf_idfs[file] = tf_idf

    ret = []
    counter = 0
    for n_match, value in sorted(tf_idfs.items(), key=lambda item: item[1], reverse=True):
        ret.append(n_match)
        counter += 1
        if counter == n:
            return ret


def top_sentences(query, sentences, idfs, n):
    """
    Given a `query` (a set of words), `sentences` (a dictionary mapping
    sentences to a list of their words), and `idfs` (a dictionary mapping words
    to their IDF values), return a list of the `n` top sentences that match
    the query, ranked according to idf. If there are ties, preference should
    be given to sentences that have a higher query term density.
    """
    top = {}
    density = {}
    list = []

    for sentence in sentences:
        idf = 0
        dens = 0
        for word in query:
            if word in sentences[sentence]:
                idf += idfs[word]
                dens += sentences[sentence].count(word) / len(sentences[sentence])
        top[sentence] = idf
        density[sentence] = dens

    for sentence in sentences:
        list.append([sentence, top[sentence], density[sentence]])

    ret = []
    counter = 0
    for sentence, idf_s, density_s in sorted(list, key=lambda item: (item[1], item[2]), reverse=True):
        ret.append(sentence)
        counter += 1
        if counter == n:
            return ret


def word_density(query, sentence):
    counter = 0
    sentence_l = len(sentence)

    for word in query:
        if word in sentence:
            counter += sentence.count(word)
    return (counter/sentence_l)


if __name__ == "__main__":
    main()
