#!/usr/bin/python3
"""Module to count keywords in Reddit hot articles recursively."""
import requests
import sys


def count_words(subreddit, word_list, after=None, word_counts=None):
    """
    Recursively queries Reddit API, counts keywords in hot article titles,
    and prints sorted results.

    Args:
        subreddit (str): The subreddit to search
        word_list (list): List of keywords to count
        after (str, optional): Pagination token for next page of results
        word_counts (dict, optional): Dictionary to accumulate word counts
    """
    if word_counts is None:
        word_counts = {}
        # Initialize word counts with lowercase keys
        for word in word_list:
            lower_word = word.lower()
            word_counts[lower_word] = word_counts.get(lower_word, 0)

    url = f"https://www.reddit.com/r/{subreddit}/hot.json"
    headers = {"User-Agent": "python:subreddit.keyword.counter:v1.0"}
    params = {"limit": 100}
    if after:
        params["after"] = after

    try:
        response = requests.get(url, headers=headers, params=params,
                                allow_redirects=False)
        if response.status_code != 200:
            return

        data = response.json()
        posts = data.get("data", {}).get("children", [])

        for post in posts:
            title = post.get("data", {}).get("title", "").lower()
            for word in word_counts:
                # Count exact word matches (whole words only)
                word_counts[word] += title.split().count(word)

        after = data.get("data", {}).get("after")
        if after:
            return count_words(subreddit, word_list, after, word_counts)
        else:
            # Filter out words with zero counts
            filtered_counts = {k: v for k, v in word_counts.items() if v > 0}

            # Sort by count descending, then alphabetically ascending
            sorted_counts = sorted(
                filtered_counts.items(),
                key=lambda item: (-item[1], item[0])
            )

        for word, count in sorted_counts:
            print(f"{word}: {count}")

    except Exception:
        return


if __name__ == '__main__':
    count_words(sys.argv[1], [x for x in sys.argv[2].split()])
