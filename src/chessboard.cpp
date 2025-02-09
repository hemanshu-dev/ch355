#include "ncursesw/ncurses.h"
#include <cstdint>
#include <utility>

#include "chessboard.h"

ChessBoard::ChessBoard(uint16_t width, uint16_t height)
    : _currentWindowSize(std::make_pair(width, height)) {}

/**
 * @brief Initialize chessboard attribute like color size etc.
 */
void ChessBoard::init() {
  init_pair(Colors::EMPTY_BLACK_CELL, COLOR_BLACK, COLOR_RED);
  init_pair(Colors::EMPTY_WHITE_CELL, COLOR_WHITE, COLOR_BLUE);
  init_pair(Colors::WHITE_PEICE_WHITE_CELL, COLOR_WHITE,COLOR_BLUE);
  init_pair(Colors::WHITE_PEICE_BLACK_CELL, COLOR_WHITE, COLOR_BLUE);
}

ChessBoard::~ChessBoard() {}

/**
 * @brief Print a Cell at 8x8 grid(chess board).
 *
 * @param rootWindow : Window to containing the chess board.
 * @param isWhite : is the cell to be painted white.
 *                  /// TODO: Remove this param
 *                  and instead use (xCellIndex + yCellIndex)&1 to determine
 *                  whether a cell is white or black.
 * @param xCellIndex : X index of the cell.
 * @param yCellIndex : Y Index of the cell.
 */
void ChessBoard::_printCell(WINDOW *rootWindow, bool isWhite,
                            uint8_t xCellIndex, uint8_t yCellIndex) {

  //  const char *ch = isWhite ? whiteCell : blackCell;
  const char *ch = {"      "};
  for (uint8_t cellRow = 1; cellRow < 4; cellRow++) {
    mvwprintw(rootWindow, (yCellIndex * 3) + cellRow, (xCellIndex * 6) + 1,
              "%s", ch);
  }
}

/**
 * @brief Draw Chess board in the Window
 *
 * @param rootWindow : Window inside which the chess board is to be drawn.
 * @param nrows : Deprecated.
 * @param ncols : Deprecated.
 */
void ChessBoard::draw(WINDOW *rootWindow, uint16_t nrows, uint16_t ncols) {
  wclear(rootWindow);
  box(rootWindow, 0, 0);
  for (uint8_t xIndex = 0; xIndex < 8; xIndex++) {
    for (uint8_t yIndex = 0; yIndex < 8; yIndex++) {
      wattron(rootWindow,
              COLOR_PAIR(!((xIndex + yIndex) & 1) ? Colors::EMPTY_WHITE_CELL
                                                  : Colors::EMPTY_BLACK_CELL));
      _printCell(rootWindow, !((xIndex + yIndex) & 1), xIndex, yIndex);
      wattroff(rootWindow,
               COLOR_PAIR(!((xIndex + yIndex) & 1) ? Colors::EMPTY_WHITE_CELL
                                                   : Colors::EMPTY_BLACK_CELL));
    }
  }
  wrefresh(rootWindow);
  ChessPeice* peice = ChessPeiceFactory::getInstance()->
                        getPeice(ChessPeiceFactory::PeiceType::KNIGHT);
  drawPeice(rootWindow,*peice);
}

void ChessBoard::drawPeice(WINDOW* rootWindow, ChessPeice& peice){
    const char** asset = peice.getAsset();
    uint8_t yCellIndex = peice.getCoordinates().second;
    uint8_t xCellIndex = peice.getCoordinates().first;

    wattron(rootWindow,
              COLOR_PAIR(!((xCellIndex + yCellIndex) & 1) ? Colors::WHITE_PEICE_WHITE_CELL
                                                  : Colors::WHITE_PEICE_BLACK_CELL));
    
  for (uint8_t cellRow = 1; cellRow < 4; cellRow++) {
    mvwprintw(rootWindow, (yCellIndex * 3) + cellRow, (xCellIndex * 6) + 2,
              "%s", asset[cellRow-1]);
  }
    wattroff(rootWindow,
              COLOR_PAIR(!((xCellIndex + yCellIndex) & 1) ? Colors::WHITE_PEICE_WHITE_CELL
                                                  : Colors::WHITE_PEICE_BLACK_CELL));

  wrefresh(rootWindow);
}


/**
 * @brief Rotate the Board 180 degrees.
 */
void ChessBoard::rotate() {}

void ChessBoard::update() {}
