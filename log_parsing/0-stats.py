#!/usr/bin/python3
"""script to compute request statistics from stdin"""

import sys

stats = {}
valid_codes = {'200', '301', '400', '401', '403', '404', '405', '500'}
total_size, line_count = 0, 0

try:
    for line in sys.stdin:
        parts = line.split()
        if len(parts) < 9:
            continue
        try:
            size = int(parts[-1])
            status = parts[-2]
            total_size += size
            if status in valid_codes:
                stats[status] = stats.get(status, 0) + 1
            line_count += 1
            if line_count % 10 == 0:
                print("File size:", total_size)
                for code in sorted(stats):
                    print(f"{code}: {stats[code]}")
        except ValueError:
            continue
except KeyboardInterrupt:
    print("File size:", total_size)
    for code in sorted(stats):
        print(f"{code}: {stats[code]}")
    raise
