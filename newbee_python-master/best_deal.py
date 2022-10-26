from copy import deepcopy


price_list = {
    'Monday': 5,
    'Tuesday': 9,
    'Wednesday': 13,
    'Thursday': 2,
    'Friday': 6,
    'Saturday': 19,
    'Sunday': 4
}


price_list_2 = {
    5: 'Monday',
    9: 'Tuesday',
    13: 'Wednesday',
    2: 'Thursday',
    6: 'Friday',
    19: 'Saturday',
    4: 'Sunday'
}


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


def find_deal(offers_list):     # Значения цен должно быть в значениях словаря
    benefit = 0                                 # Маржинальный доход
    buy_day = None                              # День когда наивыгоднее купить
    sell_day = None                                # День когда наивыгоднее продать
    try:
        for price_1 in offers_list.values():        # Циклы для перебора всех пар
            for price_2 in offers_list.values():
                inter_val = price_2 - price_1       # Промежуточное значение маржи
                if inter_val > benefit:             # Если маржинальный доход существенен,
                    benefit = inter_val             # то добавляем в переменную выше
                    buy_day = price_list_2[price_1]
                    sell_day = price_list_2[price_2]
                else:
                    continue
    except KeyError:
        return "Uncorrect values"
    except ValueError:
        return "Uncorrect values"

    return buy_day, sell_day


def divide_deal(first, second, buy_day, sell_day, benefit):      # Numbers in keys
    pass


def merge_find_deal(offers_list):       # Prices in values
    buy_day = None  # День когда наивыгоднее купить
    sell_day = None
    benefit = 0  # Маржинальный доход
    if len(offers_list) == 1:
        for i in offers_list.keys():
            buy_day, sell_day = i, i
        return buy_day, sell_day
    firstHalf_offers = left_half_dict(offers_list)      # Left part for merge
    secondHalf_offers = right_half_dict(offers_list)    # Right part for merge
    return buy_day, sell_day

print(find_deal(price_list_2))
