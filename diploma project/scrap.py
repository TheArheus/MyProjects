import bs4 as bs
import urllib.request
import re
import heapq
import nltk
import lxml

def scrap(url):
    try:
        req = urllib.request.Request(url, headers={
            'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'
        })
    except:
        return False

    scraped_data = urllib.request.urlopen(req)
    article = scraped_data.read()

    parsed_article = bs.BeautifulSoup(article, 'lxml')

    text = parsed_article.find_all(text=True)

    article_text = ""
    blacklist = [
        '[document]',
        'noscript',
        'header',
        'html',
        'meta',
        'head',
        'input',
        'script',
    ]

    for p in text:
        if p.parent.name not in blacklist:
            article_text += p

    print(article_text)

    return article_text

def format_text(article_text, language):
    # Removing Square Brackets and Extra Spaces
    article_text = re.sub(r'\[[0-9]*\]', ' ', article_text)
    article_text = re.sub(r'\s+', ' ', article_text)

    # Removing special characters and digits
    if language == 'russian':
        formatted_article_text = re.sub('[^а-яёА-ЯЁ]', ' ', article_text)
        formatted_article_text = re.sub(r'\s+', ' ', formatted_article_text)
    else:
        formatted_article_text = re.sub('[^a-zA-Z]', ' ', article_text)
        formatted_article_text = re.sub(r'\s+', ' ', formatted_article_text)

    return article_text, formatted_article_text


def summarize(article_text, formatted_article_text, language, sent_count):
    sentence_list = nltk.sent_tokenize(article_text)
    stopwords = nltk.corpus.stopwords.words(language)

    word_frequencies = {}
    for word in nltk.word_tokenize(formatted_article_text):
        if word not in stopwords:
            if word not in word_frequencies.keys():
                word_frequencies[word] = 1
            else:
                word_frequencies[word] += 1

    maximum_frequncy = max(word_frequencies.values())

    for word in word_frequencies.keys():
        word_frequencies[word] = (word_frequencies[word] / maximum_frequncy)

    sentence_scores = {}
    for sent in sentence_list:
        for word in nltk.word_tokenize(sent.lower()):
            if word in word_frequencies.keys():
                if len(sent.split(' ')) < 30:
                    if sent not in sentence_scores.keys():
                        sentence_scores[sent] = word_frequencies[word]
                    else:
                        sentence_scores[sent] += word_frequencies[word]

    summary_sentences = heapq.nlargest(sent_count, sentence_scores, key=sentence_scores.get)

    return summary_sentences