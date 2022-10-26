from random import randint

counter = 0

random_numbers = []

while counter != 10:
    random_numbers.append(randint(0, 100))
    counter += 1

print(random_numbers)
print(max(random_numbers))

def max_number(list):
    max = list[0]
    for i in list:
        if i > max:
            max = i
        else:
            continue
    return max

print(max_number(random_numbers))