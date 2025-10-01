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
            
            # Split the line to check basic format
            parts = line.split()
            if len(parts) < 9:
                continue
            
            # Check if the line contains the required GET request pattern
            if '"GET /projects/260 HTTP/1.1"' not in line:
                continue
            
            try:
                # Extract file size (last element) and status code (second to last)
                file_size = int(parts[-1])
                status_code = parts[-2]
                
                # Validate IP address format (first part)
                ip_parts = parts[0].split('.')
                if len(ip_parts) != 4:
                    continue
                
                # Check if all IP parts are valid numbers
                valid_ip = True
                for ip_part in ip_parts:
                    try:
                        ip_num = int(ip_part)
                        if ip_num < 0 or ip_num > 255:
                            valid_ip = False
                            break
                    except ValueError:
                        valid_ip = False
                        break
                
                if not valid_ip:
                    continue
                
                # Check if status code is a valid 3-digit number
                try:
                    int(status_code)
                    if len(status_code) != 3:
                        continue
                except ValueError:
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
