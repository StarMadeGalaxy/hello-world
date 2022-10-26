numbers = [4, 7, 23, 6, 7, 32, 6]
numbers_2 = [2, 4, 5]


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


print(sum_numbers(numbers))
print(sum_numbers(numbers_2))
print(sum(numbers))
print(sum(numbers_2))
print(recursion_sum(numbers))
print(recursion_sum(numbers_2))