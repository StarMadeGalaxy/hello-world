def recursion_length(array):
    if array == []:
        return 0
    else:
        return 1 + recursion_length(array[1:])


def recursion_max(array):
    if len(array) == 2:
        return array[0] if array[0] > array[1] else array[1]
    temp_max = recursion_max(array[1:])
    return array[0] if array[0] > temp_max else temp_max


def sum_numbers(array):     # Simple linear algorithm with O(n) complexity
    total = 0
    for i in array:
        total += i
    return total


def recursion_sum(array):   # Sum of elements by usage recursion
    if len(array) == 0:
        return 0
    else:
        return array[0] + recursion_sum(array[1:])


massive = [1, 5, 7, 14, 3, 24]


print(recursion_max(massive))