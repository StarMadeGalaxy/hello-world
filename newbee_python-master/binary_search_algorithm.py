list_1 = [1, 3, 5, 7, 8, 9, 34, 56]


def binary_search(item, numbers):   # Expect integer index of item
    start = 0
    end = len(numbers) - 1
    while start <= end:
        mid = start + round((end - start) / 2)
        guess = numbers[mid]
        if item == guess:
            return "Index of number {0} is {1}".format(item, mid)
        elif item < guess:
            end = mid - 1
        else:
            start = mid + 1
    return "Item not found"


print(binary_search(8, list_1))