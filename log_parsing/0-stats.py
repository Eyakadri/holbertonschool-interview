#!/usr/bin/python3
"""
Module that parses a log and prints stats to stdout
"""
import sys

def print_stats(total_size, status_counts):
    """Print the current statistics"""
    print("File size: {}".format(total_size))
    for code in sorted(status_counts.keys()):
        print("{}: {}".format(code, status_counts[code]))

def main():
    """Main function to parse logs and print statistics"""
    # Valid status codes
    valid_codes = ['200', '301', '400', '401', '403', '404', '405', '500']
    
    # Initialize counters
    total_size = 0
    status_counts = {}
    line_count = 0
    
    try:
        for line in sys.stdin:
            line = line.strip()
            
            # Skip empty lines
            if not line:
                continue
            
            # Check if the line contains the required GET request pattern
            if '"GET /projects/260 HTTP/1.1"' not in line:
                continue
            
            # Split the line and check basic structure
            parts = line.split()
            if len(parts) < 9:
                continue
            
            try:
                # Extract file size (last element) and status code (second to last)
                file_size = int(parts[-1])
                status_code = parts[-2]
                
                # Basic validation: status code should be 3 digits
                if not status_code.isdigit() or len(status_code) != 3:
                    continue
                
                # Update total size
                total_size += file_size
                
                # Update status code count if it's valid
                if status_code in valid_codes:
                    status_counts[status_code] = status_counts.get(status_code, 0) + 1
                
                line_count += 1
                
                # Print statistics every 10 lines
                if line_count % 10 == 0:
                    print_stats(total_size, status_counts)
                    
            except (ValueError, IndexError):
                continue
        
        # Print final statistics if there are any processed lines
        if line_count > 0 and line_count % 10 != 0:
            print_stats(total_size, status_counts)
        elif line_count == 0:
            # Even if no valid lines were processed, print File size: 0
            print_stats(total_size, status_counts)
                
    except KeyboardInterrupt:
        # Print final statistics on keyboard interrupt
        print_stats(total_size, status_counts)

if __name__ == "__main__":
    main()
