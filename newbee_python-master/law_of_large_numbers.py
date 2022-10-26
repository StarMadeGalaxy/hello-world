from random import randint


def find_percent(number, amount):       # найти процент числа от всего количества
    percent = (number * 100) / len(amount)
    return percent


time_1 = 10     # Количество подбрасываний монетки
time_2 = 100
time_3 = 1000
time_4 = 10000

result_1 = []  # Все результаты подбрасываний
result_2 = []
result_3 = []
result_4 = []

amount_1 = 0    # Количество решек
amount_2 = 0
amount_3 = 0
amount_4 = 0

sequence_1 = []     # При нескольких повторениях эксперимента, последовательность процента решек
sequence_2 = []
sequence_3 = []
sequence_4 = []

# 1 - Решка, 0 - Орел

for i in range(15):
    for time in range(time_1):          # Серия циклов подбрасывания
        result_1.append(randint(0, 1))

    for time in range(time_2):
        result_2.append(randint(0, 1))

    for time in range(time_3):
        result_3.append(randint(0, 1))

    for time in range(time_4):
        result_4.append(randint(0, 1))


    for side_1 in result_1:         # Серия циклов вычисления количеста решек из подбрасывания
        if side_1 == 1:
            amount_1 += side_1

    for side_2 in result_2:
        if side_2 == 1:
            amount_2 += side_2

    for side_3 in result_3:
        if side_3 == 1:
            amount_3 += side_3

    for side_4 in result_4:
        if side_4 == 1:
            amount_4 += side_4


    sequence_1.append(find_percent(amount_1, result_1))
    sequence_2.append(find_percent(amount_2, result_2))
    sequence_3.append(find_percent(amount_3, result_3))
    sequence_4.append(find_percent(amount_4, result_4))

    result_1.clear()
    result_2.clear()
    result_3.clear()
    result_4.clear()

    amount_1 = 0
    amount_2 = 0
    amount_3 = 0
    amount_4 = 0


print("Результаты при подрасывании 10 монет: {}".format(sequence_1))
print("Результаты при подрасывании 100 монет: {}".format(sequence_2))
print("Результаты при подрасывании 1000 монет: {}".format(sequence_3))
print("Результаты при подрасывании 10000 монет: {}".format(sequence_4))
