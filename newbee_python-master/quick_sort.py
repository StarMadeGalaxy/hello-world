from random import randint


def random_numbers(amount):
    numbers = []
    counter = 0
    while counter != amount:
        numbers.append(randint(0, 100))
        counter += 1
    return numbers


array = [1, 4, 9, 11, 16, 20]       # Median expected - 11


def find_median_number(array):
    if len(array) == 1:
        return array[0]
    try:
        average = sum(array) / len(array)
    except ZeroDivisionError:
        return 0
    dif_list = [abs(i - average) for i in array]
    median = array[dif_list.index(min(dif_list))]
    return median


def qsort(array):
    if len(array) < 2:
        return array
    pivot = array[0]
    less_pivot = [i for i in array[1:] if i <= pivot]
    more_pivot = [i for i in array[1:] if i > pivot]
    return qsort(less_pivot) + [pivot] + qsort(more_pivot)


x = random_numbers(20)
print(qsort(x))
print(x)
