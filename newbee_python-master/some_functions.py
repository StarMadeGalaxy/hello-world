from random import randint
from copy import deepcopy

def random_numbers(amount):
    numbers = []
    counter = 0
    while counter != amount:
        numbers.append(randint(0, 100))
        counter += 1
    return numbers


def right_half_dict(dictionary):        # Right part funcuion should be create before left
    right_dict = deepcopy(dictionary)
    counter = 0
    if len(dictionary) <= 1:
        return dictionary
    else:
        for key in dictionary.keys():
            if counter < int(len(dictionary) / 2):
                del right_dict[key]
                counter += 1
            else:
                break
    return right_dict


def left_half_dict(dictionary):        # Slice dictionary and get a right half of it
    left_dict = deepcopy(dictionary)   # Make copy of parent dict just for sure
    if len(dictionary) <= 1:
        return dictionary
    else:
        for key in right_half_dict(dictionary).keys():
            del left_dict[key]
    return left_dict
