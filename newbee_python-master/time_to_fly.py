mars_earth_year_angel = 191.387    # Угол который пройдет марс за земной год
full_turn = 360.0                  # Угол полного оборота вокруг Солнца

year = 0          # Переменная показывающая сколько лет пройдет
angle = 216   # Конечный угол окна запуска
delta_angle = []  # Массив изменения угла с течением времени
number = 1  # Номер года

while True:                     # Цикл прибавляющий угол за один год
    if 42.5 <= angle <= 44.3:   # Если угол в промежутке от 42,5 до 44.3
        break                   # Остановка цикла
    else:
        angle += mars_earth_year_angel  # Добавляем угол за год
        if angle >= full_turn:          # Если угол совершил оборот в 2π
            angle -= full_turn          # то отнимем от угла полный оборот
        year += 1                       # Счетчик времени
        delta_angle.append(angle)       # Добавление полученного угла в массив


for i in delta_angle:   # Вывод изменения угла в виде списка
    print("Угол спустя {0} года: {1}".format(number, i))    # Обозначим угол через n-год
    number += 1

print(" ")                                                                 # Для красоты вывода
print("↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭ИТОГИ↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭↭")        # Для красоты вывода
print("Количество пройденных лет:", year)                                   # Вывод пройденных лет
print("Угол между Марсом и Землей через {0} лет: {1}".format(year, angle))   # Вывод угла на экран
