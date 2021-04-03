import os
import random
import re
import sys
import numpy as np

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """
    counter = len(corpus)
    probability = (1 - damping_factor) / counter

    if page not in corpus[page]:
        number = len(corpus[page])

    try:
        chance = (damping_factor / number)
    except:
        count = 0
        for word in corpus:
            count += 1
        dictionary = {}
        for word in corpus:
            dictionary[word] = 1 / count
        return dictionary

    dictionary = { page: probability }

    list = set()
    for word in corpus:
        if word in corpus[page] and word not in list:
            dictionary[word] = chance + float(probability)
            list.add(word)
        else:
            dictionary[word] = probability

    return dictionary


def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at random.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    counter = len(corpus)
    n = random.choice(range(counter))
    count = 0
    for string in corpus:
        if n == count:
            thing = string
        count += 1
    dict = {}
    for word in corpus:
        dict[word] = 0

    counter = 0

    while counter < SAMPLES:
        counter += 1
        dict[thing] += 1
        what = transition_model(corpus, thing, damping_factor)
        choice = pick_by_weight(what)
        thing = choice

    for word in corpus:
        dict[word] = dict[word] / SAMPLES

    return dict


def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    PageRank = {}
    for word in corpus:
        PageRank[word] = 1 / len(corpus)

    change = 1
    while change >= 0.001:
        for page in PageRank:
            prev = PageRank[page]
            PageRank[page] = ((1 - damping_factor) / len(corpus)) + damping_factor * second_part(corpus, page, PageRank)
            change = abs(prev - PageRank[page])

    sum = 0
    counter = 0
    while (sum - sum % 0.000000001) != 1:
        counter += 1
        sum = 0
        for page in PageRank:
            sum += PageRank[page]

        for page in PageRank:
            PageRank[page] *= (1 / sum)

        if counter == 10:
            break

    return PageRank


def pages_pointing(corpus, page):
    list_of_pages = []
    for html in corpus:
        if page in corpus[html]:
            list_of_pages.append(html)
    if len(list_of_pages) != 0:
        return list_of_pages
    else:
        return [html for html in corpus]


def second_part(corpus, page, pageranks):
    sum = 0
    linking_to = pages_pointing(corpus, page)

    for html in linking_to:
        if len(corpus[html]) == 0:
            for it in corpus:
                corpus[html].add(it)
        sum += (pageranks[html] / len(corpus[html]))

    return sum


def pick_by_weight(dictionary):
    #friends from StackOverflow helped me
    html = []
    probabilities = []
    for k,v in dictionary.items():
        html.append(k)
        probabilities.append(v)

    return np.random.choice(html, 1, p=probabilities)[0]

if __name__ == "__main__":
    main()
