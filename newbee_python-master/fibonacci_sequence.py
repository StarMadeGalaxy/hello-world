def fibonacci(sequence, limit):     # Мой личный алгоритм
    sequence.append(0)              # Ужасно большой и медленный, но рабочий
    sequence.append(1)              # Попробую через рекурсию
    index = 1
    amount = 0
    while amount != limit - 1:
        fol_num = sequence[index] + sequence[index - 1]
        sequence.append(fol_num)
        index += 1
        amount += 1
    return sequence


def fibonacci_recursion(n):
    if n == 2 or n == 1:
        return 1
    else:
        return fibonacci_recursion(n - 1) + fibonacci_recursion(n - 2)


def fibonacci_2(limit):            # Мой личный алгоритм второй
    sequence = [0, 1]              # Поменьше и побыстрее, но рабочий
    for i in range(1, limit):
        fol_num = sequence[i] + sequence[i - 1]
        sequence.append(fol_num)
    return sequence


array = []
fibonacci(array, 16)
print(array)
print(len(array))

print(fibonacci_recursion(3))


