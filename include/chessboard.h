#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__

#include "ncursesw/ncurses.h"
#include <cstdint>
#include <utility>
class ChessBoard {
private:
  const std::pair<uint16_t, uint16_t> _minWindowSize{26, 26};
  std::pair<uint16_t, uint16_t> _currentWindowSize;
  const char *whiteCell = {"WWW"};
  const char *blackCell = {"bbb"};
  void _printCell(WINDOW *rootWindow, bool isWhite, uint8_t xCellIndex,
                  uint8_t yCellIndex);

public:
  enum Colors : short {
    EMPTY_WHITE_CELL = 1,
    EMPTY_BLACK_CELL = 2,
    WHITE_PEICE_WHITE_CELL = 3,
    WHITE_PEICE_BLACK_CELL = 4,
    BLACK_PEICE_WHITE_CELL = 5,
    BLACK_PEICE_BLACK_CELL = 6,
  };

  void operator=(const ChessBoard &) = delete;
  void operator=(const ChessBoard &&) = delete;
  ChessBoard(const ChessBoard &) = delete;

  explicit ChessBoard(uint16_t width, uint16_t height);
  ~ChessBoard();
  void draw(WINDOW *rootWindow, uint16_t nrows, uint16_t ncols);
  void rotate();
  void update();
  void init();
};

#endif
