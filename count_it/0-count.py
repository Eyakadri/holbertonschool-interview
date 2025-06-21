#!/usr/bin/python3
"""
Module for counting keywords in hot posts titles of a subreddit recursively.
"""

import requests


def count_words(subreddit, word_list, counts=None, after=None):
    """
    Queries the Reddit API recursively, parses titles of all hot articles,
    and prints a sorted count of given keywords (case-insensitive).

    Args:
        subreddit (str): The subreddit to query.
        word_list (list): List of keywords to count.
        counts (dict): Dictionary to accumulate counts (used internally).
        after (str): Token for pagination (used internally).
    """
    if counts is None:
        counts = {}

    keywords = [w.lower() for w in word_list]

    url = f'https://www.reddit.com/r/{subreddit}/hot.json'
    headers = {
        'User-Agent': 'Python3:keyword-counter:v1.0 (by /u/yourusername)'
    }
    params = {'limit': 100}
    if after:
        params['after'] = after

    try:
        response = requests.get(url, headers=headers,
                                params=params, allow_redirects=False)
        if response.status_code != 200:
            return 
        data = response.json()
    except Exception:
        return

    posts = data.get('data', {}).get('children', [])
    for post in posts:
        title = post.get('data', {}).get('title', '').lower()
        title_words = title.split()
        for keyword in set(keywords):
            count = sum(1 for word in title_words if word == keyword)
            if count > 0:
                counts[keyword] = counts.get(keyword, 0) + count

    after = data.get('data', {}).get('after', None)
    if after:
        return count_words(subreddit, word_list, counts, after)

    final_counts = {}
    for word in keywords:
        final_counts[word] = final_counts.get(word, 0) + counts.get(word, 0)

    filtered = {k: v for k, v in final_counts.items() if v > 0}

    for word, count in sorted(filtered.items(),
                              key=lambda x: (-x[1], x[0])):
        print(f"{word}: {count}")
