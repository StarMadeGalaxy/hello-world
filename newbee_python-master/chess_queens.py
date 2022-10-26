def print_board(figure):    # Function for convenient list-in-list print
    counter = 0
    print("    0 1 2 3 4 5 6 7")
    print(" ")
    for i in figure:
        print('{0}   {1}'.format(counter, ' '.join(i)))
        counter += 1


def chess_board(size):      # Built a chess board
    board = []
    for i in range(size):
        board.append(['O'] * size)
    return board


def possible_moves_queen(height, row, board):   # board is list-in-list
    l_diagonal_start_height = height
    l_diagonal_start_row = row
    r_diagonal_start_height = height
    r_diagonal_start_row = row
    board[height][row] = '#'

    for h_move in range(len(board[height])):        # horizontal moves
        if board[height][h_move] == '#':
            continue
        else:
            board[height][h_move] = '*'

    for v_move in range(len(board)):     # vertical moves
        if board[v_move][row] == '#':
            continue
        else:
            board[v_move][row] = '*'

    while True:         # Find start positional of left diagonal
        if l_diagonal_start_height == 0 or l_diagonal_start_row == 0:
            break
        else:
            l_diagonal_start_row -= 1
            l_diagonal_start_height -= 1

    while True:     # building a left diagonal
        if l_diagonal_start_height == len(board) or l_diagonal_start_row == len(board):
            break
        else:
            if board[l_diagonal_start_height][l_diagonal_start_row] == '#':
                pass
            else:
                board[l_diagonal_start_height][l_diagonal_start_row] = '*'
        l_diagonal_start_row += 1
        l_diagonal_start_height += 1

    while True:     # Find start positional of right diagonal
        if r_diagonal_start_height == 0 or r_diagonal_start_row == len(board) - 1:
            break
        else:
            r_diagonal_start_row += 1
            r_diagonal_start_height -= 1

    while True:  # building a right diagonal
        if r_diagonal_start_height == len(board) or r_diagonal_start_row < 0:
            break
        else:
            if board[r_diagonal_start_height][r_diagonal_start_row] == '#':
                pass
            else:
                board[r_diagonal_start_height][r_diagonal_start_row] = '*'
        r_diagonal_start_row -= 1
        r_diagonal_start_height += 1
    return board


def find_queen_amount(board):
    amount = 0
    for height in range(len(board)):
        for row in range(len(board)):
            if board[height][row] == '#':
                amount += 1
    return amount






print_board(possible_moves_queen(4, 5, chess_board(8)))
