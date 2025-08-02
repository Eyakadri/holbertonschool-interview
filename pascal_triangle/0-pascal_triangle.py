#!/usr/bin/python3

def pascal_triangle(n):
    """
    Generate Pascal's Triangle up to n rows.
    Args: n (int): The number of rows to generate.
    Returns:List[List[int]]: Pascal's Triangle as a list of lists.
    """
    if n <= 0:
        return []

    triangle = [[1]]

    for i in range(1, n):
        row = [1]
        prev_row = triangle[i - 1]

        for j in range(1, i):
            row.append(prev_row[j - 1] + prev_row[j])

        row.append(1)
        triangle.append(row)

    return triangle
