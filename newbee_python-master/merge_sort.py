from random import randint


def random_numbers(amount):
    numbers = []
    counter = 0
    while counter != amount:
        numbers.append(randint(0, 100))
        counter += 1
    return numbers


def merge(left, right):
    # Merge two sorted lists into third sorted list
    merged = [None] * (len(left) + len(right))         # Create a merged list size of two input together
    index_left = 0      # Index of first list
    index_right = 0     # Index of second list
    index_merged = 0    # Index of merged list
    # While indexes of input lists less than their length
    # Compare first numbers and lower add to merged list
    # Then throwing out it from list by increasing index
    while (index_left < len(left)) and (index_right < len(right)):
        if left[index_left] <= right[index_right]:
            merged[index_merged] = left[index_left]
            index_left += 1
            index_merged += 1
        else:
            merged[index_merged] = right[index_right]
            index_right += 1
            index_merged += 1
    # If first cycle stop working and if one of input lists bigger than other
    # Just adding remaining numbers
    while index_right < len(right):
        merged[index_merged] = right[index_right]
        index_right += 1
        index_merged += 1
    while index_left < len(left):
        merged[index_merged] = left[index_left]
        index_left += 1
        index_merged += 1
    return merged


def merge_sort(unsorted):
    if len(unsorted) == 1:
        return unsorted
    left_part = unsorted[:int(len(unsorted) / 2)]
    right_part = unsorted[int(len(unsorted) / 2):]
    return merge(merge_sort(left_part), merge_sort(right_part))


list_to_sort = random_numbers(200)
print(list_to_sort)
print(merge_sort(list_to_sort))