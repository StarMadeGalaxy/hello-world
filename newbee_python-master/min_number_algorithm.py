from random import randint

array = []

for i in range(15):
    array.append(randint(1, 100))


def min_number(catalog):
    small_number = catalog[0]                   # Сохраняем первый элемента массива, чтобы с ним сравнивать другие
    small_index = 0
    for index in range(1, len(catalog)):
        if catalog[index] < small_number:
            small_number = catalog[index]
            small_index = index
    return small_index


print(array, "- Main array")
print(min_number(array), '- Index of smallest number of array')
print(min(array), '- Smallest number of array')


if min_number(array) == array.index(min(array)):
    print(True)
else:
    print(False)