def board_int_to_str(board):
    string_board = []
    string_line = []
    for line in board:
        for column in line:
            string_line.append(str(column))
        string_board.append(string_line)
        string_line = []
    return string_board


def print_board(board):
    new_board = []
    counter = 0
    number_index = 0  # Index for number in row
    counter_vertical = 0
    print("X  0 1 2 | 3 4 5 | 6 7 8")
    print("Y  ---------------------")

    for line in board:
        new_line = [str(counter_vertical) + '|']
        counter_vertical += 1
        for i in range(len(line) + 2):  # +2 because row contains two |
            if counter == 3:
                new_line.append('|')
                counter = 0
            else:
                new_line.append(line[number_index])
                number_index += 1
                counter += 1
        new_board.append(new_line)
        new_line = []
        number_index = 0
        counter = 0

    row_counter = 0
    column_counter = 0

    # making horizontal lines
    for row in range(len(new_board) + 2):
        if row_counter == 3:
            print((" " * 2) + ('-' * ((len(new_board) + 2) * 2)))  # - symbol is too short for good-looking line
            row_counter = 0
        else:
            print(' '.join(new_board[column_counter]))
            row_counter += 1
            column_counter += 1
    return None


