from random import randint
from copy import deepcopy


def appstart(list, element):
    added_list = [element]
    added_list += list
    return added_list


def min_number(catalog):
    small_number = catalog[0]
    for i in catalog:
        if i < small_number:
            small_number = i
        else:
            continue
    return small_number


def max_number(catalog):
    big_number = catalog[0]
    for i in catalog:
        if i > big_number:
            big_number = i
        else:
            continue
    return big_number


def selection_sort(items):
    sorted_items = []
    while len(items) != 0:
        sorted_items.append(max_number(items))
        items.remove(max_number(items))
    return sorted_items

array = []

for i in range(15):
    array.append(randint(1, 100))


def double_selection_sort(elements):
    sorted_items = []
    while len(elements) > 0:
        sorted_items.append(max_number(elements))
        elements.remove(max_number(elements))
        if len(elements) > 0:

            elements.remove(min_number(elements))
        else:
            break
    return sorted_items


print(array)
print(min_number([0]))
print(max_number(deepcopy(array)))
print(selection_sort(deepcopy(array)))
print(double_selection_sort(deepcopy(array)))