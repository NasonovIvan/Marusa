#крестики-нолики

#объявление констант
X = "x"
O = "O"
EMPTY = "."
TIE = "xO"

def read_board(n):
  """Считывает доску с консоли"""
  board = []
  for i in range(n * n):
    input(i)
    board.append(i)
  return board 

def winner(board):
  """Определяет победителя"""
  WAYS_TO_WIN = ((0, 1, 2), 
                 (3, 4, 5),
                 (6, 7, 8), 
                 (0, 3, 6),
                 (1, 4, 7),
                 (2, 5, 8),
                 (0, 4, 8),
                 (2, 4, 6))
  for i in WAYS_TO_WIN:
    if board[i[0]] == board[i[1]] == board[i[2]] != EMPTY:
      winner = board[i[0]]
      return winner
    if EMPTY not in board:
      return TIE
  return None

def congrat_winner(the_winner, computer, human):
  """Поздравляет победителя игры"""
  if the_winner != TIE:
    print(the_winner)
  elif the_winner == TIE:
    print(TIE)

def main():
  n = int(input())
  board = read_board(n)
  print(board)
  #the_winner = winner(board)
  #congrat_winner(the_winner, computer, human)

#запуск программы
main()
