from printer import board_int_to_str, print_board

board_integer = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9],
]


def check_solvability(board):  # check if the board is correct initially
    for row in range(len(board)):
        for col in range(len(board)):
            if board[row][col] == 0:
                pass
            else:
                number = board[row][col]
                board[row][col] = 0
                if not check(number, row, col, board):
                    return False
                else:
                    board[row][col] = number
    return True


def check(number, y, x, board):  # check can we put a specific number on board[y][x]
    if board[y][x] != 0:
        return False

    for i in board[y]:  # check X-line (row)
        if i == number:
            return False
        else:
            pass

    for line in board:  # check Y-line  (column)
        if line[x] == number:
            return False
        else:
            pass

    # checking boxes
    X_box = x // 3  # here we create (y, x) for boxes in the board
    Y_box = y // 3  # so each box has its own coordinates

    # limits for boxes
    X_box_low_limit = X_box * 3  # for every box set limits of X and Y of the whole board
    X_box_high_limit = X_box * 3 + 3

    Y_box_low_limit = Y_box * 3
    Y_box_high_limit = Y_box * 3 + 3

    for row in range(Y_box_low_limit, Y_box_high_limit):
        for col in range(X_box_low_limit, X_box_high_limit):
            if board[row][col] == number:
                return False
            else:
                pass

    return True


def find_empty_cell(board):
    x = 0
    y = 0
    for row in board:
        for column in row:
            if column == 0:
                return y, x
            else:
                pass
            x += 1
        x = 0
        y += 1
    return False  # There's no empty cell


def solve(board):  # solving algorithm
    if not check_solvability(board):
        print("The board has no solution !")
        return False

    find_empty_spot = find_empty_cell(board)
    if not find_empty_spot:
        print("The board is solved !")
        return True
    else:
        y, x = find_empty_cell(board)  # (y, x)

    for guess in range(1, 10):  # trying all allowed number to set/./.
        if check(guess, y, x, board):  # check if we can place a number
            board[y][x] = guess
            if solve(board):
                return True
            else:
                board[y][x] = 0  # we can't use the previous number anymore, so we just backtrack
        else:
            pass
    #
    return False  # return False 'cause there's was no True before return False
    #     and therefore there is no solution for this case with that number


solve(board_integer)
print_board(board_int_to_str(board_integer))
