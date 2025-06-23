#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__

#include "ncursesw/ncurses.h"
#include <cstdint>
#include <utility>
#include <vector>

#include "chesspeice.h"

class ChessBoard {
private:
  const std::pair<uint16_t, uint16_t> _minWindowSize{26, 26};
  std::pair<uint16_t, uint16_t> _currentWindowSize;
  void _printCell(WINDOW *rootWindow, bool isWhiteCell, uint8_t xCellIndex,
                  uint8_t yCellIndex);
  void _setFocusOnPeice(WINDOW *rootWindow, ChessPeice& peice) const;
  void _removeFocusOnPeice(WINDOW *rootWindow, ChessPeice& peice);
  
  std::vector<ChessPeice*> _blackChessPeices{16,nullptr};
  std::vector<ChessPeice*> _whiteChessPeices{16,nullptr};
  uint8_t _whitePeiceOnFocusIndex{3};    
  uint8_t _blackPeiceOnFocusIndex{7};    

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
  
  ~ChessBoard();
  explicit ChessBoard(uint16_t width, uint16_t height);
  void draw(WINDOW *rootWindow, uint16_t nrows, uint16_t ncols);
  void drawPeice(WINDOW* window, ChessPeice& ChessPeice);
  void rotate();
  void setFocusLeft(WINDOW* window);
  void setFocusRight(WINDOW* window);
  void setFocusUp(WINDOW* window);
  void setFocusDown(WINDOW* window);
  void update();
  void init();
};

#endif
