from tkinter import *


alphabet = "abcdefjhigklmnopqrstuvwxyz" * 2
space = ' '


def encrypt(event):  # Шифратор

    word = entry_word.get()  # Присваиваем значение от поля ввода в переменную
    key = entry_key.get()

    result = ''
    try:
        str(word)
        int(key)

        for i in word:
            if i == space:    # обработка пробела
                result += space
            else:
                index = alphabet.index(i)           # Ищем чему равен индекс буквы слова в алфавите
                key_index = int(index) + int(key)   # Затем к этому индексу добавляем ключ шифрования
                code_letter = alphabet[key_index]   # Уже с помощью нового индекса ищем букву в алфавите
                result += code_letter               # Каждую зашифрованную букву добавляем в переменную
    except ValueError:
        label_2['text'] = 'Enter a correct values.'
    except IndexError:
        label_2['text'] = 'The key can be in the range of 30.'
    else:
        label_2['text'] = '{}'.format(result)   # Изменяем текст баннера на наш полученный результат.


def decipher(event):    # Расшифратор

    word = enter_code.get()
    key = enter_key.get()

    result = ''

    try:
        str(word)
        int(key)

        for i in word:
            if i == space:
                result += space
            else:
                index = alphabet.index(i)           # Для расшифровки тот же алгоритм
                key_index = int(index) - int(key)   # Только мы отнимаем ключ от индекса чтобы получить начальную букву
                code_letter = alphabet[key_index]
                result += code_letter
    except ValueError:
        output['text'] = 'Enter a correct values.'
    except IndexError:
        output['text'] = 'The key can be in the range of 30.'
    else:
        output['text'] = '{}'.format(result)


root = Tk()
root.title("Caesar's code")
root.geometry("250x300")


# ИНТЕРФЕЙС ДЛЯ ШИФРОВКИ

name = Label(root, text="SCRAMBLER")

label = Label(root, text="Enter a word", bg="pink", fg="black", width=150)    # Надпись ввода слова

entry_word = Entry(root, width=40)  # Поле для ввода шифрования слова

label_1 = Label(root, text="Enter a key", bg="pink", fg="black", width=150)   # Надпись для ключа

entry_key = Entry(root, width=40)   # Поле для ввода ключа шифрования

label_2 = Label(root, text='<<<The result you will see here>>>', bg="pink", fg="black", width=150)    # Результат

button = Button(root, text="Encrypt", width=34, height=1)   # Кнопка шифрования
button.bind('<Button-1>', encrypt)

# ИНТЕРФЕЙС ДЛЯ РАСШИФРОВКИ

visual = Label(root, text="DECODER")  # Название части программы

code_word = Label(root, text="Enter a word", bg="pink", fg="black", width=150)    # Надпись ввода слова

enter_code = Entry(root, width=40)  # Поле для ввода расшифрования слова

code_key = Label(root, text="Enter a key", bg="pink", fg="black", width=150)   # Надпись для ключа расшифровки

enter_key = Entry(root, width=40)   # Поле для ввода ключа расшифования

output = Label(root, text='<<<The result you will see here>>>', bg="pink", fg="black", width=150)    # Результат

de_button = Button(root, text="Decipher", width=34, height=1)   # Кнопка расшифрования
de_button.bind('<Button-1>', decipher)


#   Пакуем каждый элемент интервейса
#   друг под другом как нам нужно.

name.pack()
label.pack()
entry_word.pack()
label_1.pack()
entry_key.pack()
button.pack()
label_2.pack()
visual.pack()   # Чтобы разделять шифратор от расшифратора в интерфейсе
code_word.pack()
enter_code.pack()
code_key.pack()
enter_key.pack()
de_button.pack()
output.pack()


root.mainloop()