from copy import deepcopy


def summa(parent, names, values):
    """

    Функция суммирует объекты списка с именами,
    значения которых находятся в другом списке,
    при этом индекс имени в данном списке
    соответствует значению этого же индекса в списке
    значений.

    :param list parent: Список с которого брать индесы для данного списка
    :param list names: Список, сумму элекментов которого нужно найти
    :param list values: Список с значениями
    :return: сумму значений из списка values по иднексам из parent по именам names
    :rtype: int
    """
    answer = 0
    for name in names:
            value = values[parent.index(name)]
            answer += value
    return answer


items = ['ball', 'book', 'ring', 'chair']

items_price = [2, 157, 90, 40]

items_weight = [1, 3, 0.5, 4]


def power_set(goods):
    combinations = []
    combinations.append([])
    for item in goods:
        new_combination = deepcopy(combinations)
        for thing in new_combination:
            thing.append(item)
        combinations += new_combination
    return combinations


def knackpack(power_set, max_weight):
    max_price = 0
    best_set = None
    for set in power_set:
        set_weight = summa(items, set, items_weight)
        set_price = summa(items, set, items_price)
        if set_weight <= max_weight:
            if set_price > max_price:
                best_set = set
            else:
                pass
        else:
            continue
    return best_set


def selection_sort(items):
    sorted_items = []
    for i in range(len(items)):
        sorted_items.append(max(items))
        items.remove(max(items))
    return sorted_items


def sort_items(items_1, items_price_1):
    sorted_items = []
    for i in range(len(items_1)):
        index = items_price_1.index(max(items_price_1))
        sorted_items.append(items_1[index])
        items_1.remove(items_1[index])
        items_price_1.remove(max(items_price_1))
    return sorted_items


def greedy_knackpack(expensive_items, items_1, items_weight_1, max_weight):
    bag_weight = 0
    return_list = []
    for i in expensive_items:
        if bag_weight + items_weight_1[items_1.index(i)] <= max_weight:
            bag_weight += items_weight_1[items_1.index(i)]
            return_list.append(i)
    return return_list


print(greedy_knackpack(sort_items(deepcopy(items), deepcopy(items_price)), items, items_weight, 4))

