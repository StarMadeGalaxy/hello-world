def minimum(matrix):
    if len(matrix) == 0:
        return None

    row_index = 0
    col_index = 0

    total_sum = None

    for row in matrix:
        temp_sum = 0
        for col in row:
            temp_sum += col
        if total_sum is None:
            total_sum = temp_sum
        elif temp_sum < total_sum:
            total_sum = temp_sum
            row_index = matrix.index(row)

    total_sum = None

    for col in range(len(matrix[0])):
        temp_sum = 0
        for row in range(len(matrix)):
            temp_sum += matrix[row][col]
        if total_sum is None:
            total_sum = temp_sum
        elif temp_sum < total_sum:
            total_sum = temp_sum
            col_index = col

    return row_index, col_index


print(minimum([[7, 2, 7, 2, 8],
               [2, 9, 4, 1, 7],
               [3, 8, 6, 2, 4],
               [2, 5, 2, 9, 1],
               [6, 6, 5, 4, 5]]))

print(minimum([[-7, -2, -7, -2, -8],
               [-2, -9, -4, -1, -7],
               [-3, -8, -6, -2, -4],
               [-2, -5, -2, -9, -1],
               [-6, -6, -5, -4, -5]]))
