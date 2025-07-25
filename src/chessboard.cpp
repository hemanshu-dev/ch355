#include "chesspeice.h"
#include "ncursesw/ncurses.h"
#include <cstdint>
#include <sys/types.h>
#include <utility>

#include "chessboard.h"

/**
 * @brief
 * @param width
 * @param height
 */
ChessBoard::ChessBoard(uint16_t width, uint16_t height)
    : _currentWindowSize(std::make_pair(width, height)) {}

/**
 * @brief Initialize chessboard attribute like color size etc.
 */
void ChessBoard::init() {
  // Initialize color palatte.
  {
    init_pair(Colors::EMPTY_BLACK_CELL, COLOR_WHITE, COLOR_BLACK);
    init_pair(Colors::EMPTY_WHITE_CELL, COLOR_BLACK, COLOR_WHITE);
    init_pair(Colors::WHITE_PEICE_WHITE_CELL, COLOR_BLUE, COLOR_WHITE);
    init_pair(Colors::WHITE_PEICE_BLACK_CELL, COLOR_BLUE, COLOR_BLACK);
    init_pair(Colors::BLACK_PEICE_WHITE_CELL, COLOR_RED, COLOR_WHITE);
    init_pair(Colors::BLACK_PEICE_BLACK_CELL, COLOR_RED, COLOR_BLACK);
  }
  // Generate Chess Peices
  for (uint8_t index = 0; index < 8; index++) {
    _blackChessPeices[index + 8] = ChessPeiceFactory::getInstance()->getPeice(
        ChessPeiceFactory::PeiceType::PAWN, false, std::make_pair(index, 1));

    _whiteChessPeices[index + 8] = ChessPeiceFactory::getInstance()->getPeice(
        ChessPeiceFactory::PeiceType::PAWN, true, std::make_pair(index, 6));
  }

  _blackChessPeices[0] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::ROOK, false, std::make_pair(0, 0));
  _blackChessPeices[7] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::ROOK, false, std::make_pair(7, 0));

  _blackChessPeices[1] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::KNIGHT, false, std::make_pair(1, 0));
  _blackChessPeices[6] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::KNIGHT, false, std::make_pair(6, 0));

  _blackChessPeices[2] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::BISHOP, false, std::make_pair(2, 0));
  _blackChessPeices[5] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::BISHOP, false, std::make_pair(5, 0));

  _blackChessPeices[4] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::KING, false, std::make_pair(4, 0));
  _blackChessPeices[3] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::QUEEN, false, std::make_pair(3, 0));

  _whiteChessPeices[0] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::ROOK, true, std::make_pair(0, 7));
  _whiteChessPeices[7] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::ROOK, true, std::make_pair(7, 7));

  _whiteChessPeices[1] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::KNIGHT, true, std::make_pair(1, 7));
  _whiteChessPeices[6] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::KNIGHT, true, std::make_pair(6, 7));

  _whiteChessPeices[2] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::BISHOP, true, std::make_pair(2, 7));
  _whiteChessPeices[5] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::BISHOP, true, std::make_pair(5, 7));

  _whiteChessPeices[3] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::KING, true, std::make_pair(3, 7));
  _whiteChessPeices[4] = ChessPeiceFactory::getInstance()->getPeice(
      ChessPeiceFactory::PeiceType::QUEEN, true, std::make_pair(4, 7));
}

ChessBoard::~ChessBoard() {}

/**
 * @brief Print a Cell at 8x8 grid(chess board).
 *
 * @param rootWindow : Window to containing the chess board.
 * @param isWhiteCell : is the cell to be painted is white.
 *                  /// TODO: Remove this param
 *                  and instead use (xCellIndex + yCellIndex)&1 to determine
 *                  whether a cell is white or black.
 * @param xCellIndex : X index of the cell.
 * @param yCellIndex : Y Index of the cell.
 */
void ChessBoard::_printCell(WINDOW *rootWindow, bool isWhiteCell,
                            uint8_t xCellIndex, uint8_t yCellIndex) {
  //  const char *ch = isWhite ? whiteCell : blackCell;
  const char *ch = {"      "};
  for (uint8_t cellRow = 1; cellRow < 5; cellRow++) {
    mvwprintw(rootWindow, (yCellIndex * 4) + cellRow, (xCellIndex * 6) + 1,
              "%s", ch);
  }
}

/**
 * @brief Draw Chess board in the Window
 *
 * @param rootWindow : Window inside which the chess board is to be drawn.
 * @param ncols : Deprecated.
 * @param nrows : Deprecated.
 */
void ChessBoard::draw(WINDOW *rootWindow, uint16_t nrows, uint16_t ncols) {
  mvprintw(0, 4, "Window Size: %d %d", LINES, COLS);
  refresh();
  wclear(rootWindow);
  // Render ChessBoard.
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

  // Render Chess Peices on default locations.
  for (uint8_t index=0;index<16;index++){
    drawPeice(rootWindow,*_blackChessPeices[index]);
    drawPeice(rootWindow,*_whiteChessPeices[index]);
  }
  wrefresh(rootWindow);
  box(rootWindow, 0, 0);
 _setFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);
 _setFocusOnPeice(rootWindow,*_whiteChessPeices[_whitePeiceOnFocusIndex]);
}

/**
 * @brief Draw a Single chess peice.
 *
 * @param rootWindow
 * @param peice
 */
void ChessBoard::drawPeice(WINDOW *rootWindow, ChessPeice &peice) {
  const char **asset = peice.getAsset();
  const uint8_t yCellIndex = peice.getCoordinates().second;
  const uint8_t xCellIndex = peice.getCoordinates().first;

  // Render the peice.
  wattron(rootWindow,
          COLOR_PAIR(!((xCellIndex + yCellIndex) & 1)
                         ? (peice.isWhite ? Colors::WHITE_PEICE_WHITE_CELL
                                           : Colors::BLACK_PEICE_WHITE_CELL)
                         : (peice.isWhite ? Colors::WHITE_PEICE_BLACK_CELL
                                           : Colors::BLACK_PEICE_BLACK_CELL)));


  for (uint8_t cellRow = 1; cellRow < 4; cellRow++) {
    mvwprintw(rootWindow, (yCellIndex * 4) + cellRow + 1, (xCellIndex * 6) + 2,
              "%s", asset[cellRow - 1]);
  }
  wattroff(rootWindow,
           COLOR_PAIR(!((xCellIndex + yCellIndex) & 1)
                          ? (peice.isWhite ? Colors::WHITE_PEICE_WHITE_CELL
                                            : Colors::BLACK_PEICE_WHITE_CELL)
                          : (peice.isWhite ? Colors::WHITE_PEICE_BLACK_CELL
                                            : Colors::BLACK_PEICE_BLACK_CELL)));
}


/**
 * @brief : Set focus to peice on the left
 */
void ChessBoard::setFocusLeft(WINDOW* rootWindow){
  _removeFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);
  if(_blackPeiceOnFocusIndex & (1<<3)){
    _blackPeiceOnFocusIndex = ((_blackPeiceOnFocusIndex - 1) % 8 ) + 8;
  }
  else{
    _blackPeiceOnFocusIndex = ( _blackPeiceOnFocusIndex + 7 ) % 8;
  }
 _setFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);
}

/**
 * @brief : Draw borders around focused Chess Peice.
 *
 * @param peice : Pointer to ChessPeice around which to draw borders.
 */
void ChessBoard::_setFocusOnPeice(WINDOW *rootWindow, ChessPeice& peice) const{
  const char **asset = peice.getAsset();
  const char **borders  = peice.getBorderes();
  const uint8_t yCellIndex = peice.getCoordinates().second;
  const uint8_t xCellIndex = peice.getCoordinates().first;

  //Render Borders around the cell if the peice is on Focus.
  {
    wattron(rootWindow,
            COLOR_PAIR(!((xCellIndex + yCellIndex) & 1)
                           ? (peice.isWhite ? Colors::WHITE_PEICE_WHITE_CELL
                                            : Colors::BLACK_PEICE_WHITE_CELL)
                           : (peice.isWhite ? Colors::WHITE_PEICE_BLACK_CELL
                                            : Colors::BLACK_PEICE_BLACK_CELL)));

    for (uint8_t cellRow = 1; cellRow < 5; cellRow++) {
      mvwprintw(rootWindow, (yCellIndex * 4) + cellRow, (xCellIndex * 6) + 1,
                "%s", borders[cellRow - 1]);
    }
    wattroff(
        rootWindow,
        COLOR_PAIR(!((xCellIndex + yCellIndex) & 1)
                       ? (peice.isWhite ? Colors::WHITE_PEICE_WHITE_CELL
                                        : Colors::BLACK_PEICE_WHITE_CELL)
                       : (peice.isWhite ? Colors::WHITE_PEICE_BLACK_CELL
                                        : Colors::BLACK_PEICE_BLACK_CELL)));
    wattron(
        rootWindow,
        COLOR_PAIR(((xCellIndex + yCellIndex) & 1)&&(yCellIndex<7)
                       ? ((peice.isWhite) 
                              ? Colors::WHITE_PEICE_WHITE_CELL
                              : Colors::BLACK_PEICE_WHITE_CELL)
                       : ((peice.isWhite) 
                              ? Colors::WHITE_PEICE_BLACK_CELL
                              : Colors::BLACK_PEICE_BLACK_CELL)));
    mvwprintw(rootWindow, (yCellIndex * 4) + 5, (xCellIndex * 6) + 1, "%s",
              borders[4]);

    wattroff(rootWindow,
             COLOR_PAIR(((xCellIndex + yCellIndex) & 1)&&(yCellIndex<7)
                            ? ((peice.isWhite)
                                   ? Colors::WHITE_PEICE_WHITE_CELL
                                   : Colors::BLACK_PEICE_WHITE_CELL)
                            : ( (peice.isWhite)
                                   ? Colors::WHITE_PEICE_BLACK_CELL
                                   : Colors::BLACK_PEICE_BLACK_CELL)));
  }

  // Render the peice.
  {
    wattron(rootWindow,
            COLOR_PAIR(!((xCellIndex + yCellIndex) & 1)
                           ? (peice.isWhite ? Colors::WHITE_PEICE_WHITE_CELL
                                            : Colors::BLACK_PEICE_WHITE_CELL)
                           : (peice.isWhite ? Colors::WHITE_PEICE_BLACK_CELL
                                            : Colors::BLACK_PEICE_BLACK_CELL)));

    for (uint8_t cellRow = 1; cellRow < 4; cellRow++) {
      mvwprintw(rootWindow, (yCellIndex * 4) + cellRow + 1,
                (xCellIndex * 6) + 2, "%s", asset[cellRow - 1]);
    }

    wattroff(
        rootWindow,
        COLOR_PAIR(!((xCellIndex + yCellIndex) & 1)
                       ? (peice.isWhite ? Colors::WHITE_PEICE_WHITE_CELL
                                        : Colors::BLACK_PEICE_WHITE_CELL)
                       : (peice.isWhite ? Colors::WHITE_PEICE_BLACK_CELL
                                        : Colors::BLACK_PEICE_BLACK_CELL)));
  }
}

/**
 * @brief : Remove focus from the chess peice.
 *
 * @param window
 * @param peice
 */
void ChessBoard::_removeFocusOnPeice(WINDOW* window, ChessPeice& peice) {
  uint8_t xCellIndex = peice.getCoordinates().first;
  uint8_t yCellIndex = peice.getCoordinates().second;
  wattron(window,
         COLOR_PAIR(!((xCellIndex + yCellIndex) & 1) ? Colors::EMPTY_WHITE_CELL
                                             : Colors::EMPTY_BLACK_CELL));
  _printCell(window, !((xCellIndex + yCellIndex) & 1), xCellIndex, yCellIndex);
  wattroff(window,
          COLOR_PAIR(!((xCellIndex + yCellIndex) & 1) ? Colors::EMPTY_WHITE_CELL
                                              : Colors::EMPTY_BLACK_CELL));
  drawPeice(window,peice);

  // Repaint the row below chess Peice.
  wattron(window,
         COLOR_PAIR((((xCellIndex + yCellIndex) & 1) && yCellIndex < 7)
                        ? ((peice.isWhite) ? Colors::WHITE_PEICE_WHITE_CELL
                                           : Colors::BLACK_PEICE_WHITE_CELL)
                        : ((peice.isWhite) ? Colors::WHITE_PEICE_BLACK_CELL
                                           : Colors::BLACK_PEICE_BLACK_CELL)));
  mvwprintw(window, (yCellIndex * 4) + 5, (xCellIndex * 6) + 1, "%s","      ");

  wattroff(window, COLOR_PAIR((((xCellIndex + yCellIndex) & 1) && yCellIndex < 7)
                                     ? ((peice.isWhite)
                                            ? Colors::WHITE_PEICE_WHITE_CELL
                                            : Colors::BLACK_PEICE_WHITE_CELL)
                                     : ((peice.isWhite)
                                            ? Colors::WHITE_PEICE_BLACK_CELL
                                            : Colors::BLACK_PEICE_BLACK_CELL)));
  if(yCellIndex>=7){
    box(window,0,0);
  }
}


/**
 * @brief Move the focus to chess peice on the right.
 *
 * @param rootWindow
 */
void ChessBoard::setFocusRight(WINDOW* rootWindow){
  _removeFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);
  if(_blackPeiceOnFocusIndex & (1<<3)){
    _blackPeiceOnFocusIndex = ((_blackPeiceOnFocusIndex + 1) % 8 ) + 8;
  }
  else{
    _blackPeiceOnFocusIndex = ( _blackPeiceOnFocusIndex + 1 ) % 8;
  }
 _setFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);

}


/**
 * @brief Move the focus to chess peice above.
 *
 * @param rootWindow
 */
void ChessBoard::setFocusUp(WINDOW* rootWindow){
  _removeFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);
  if(_blackPeiceOnFocusIndex & (1<<3)){
    _blackPeiceOnFocusIndex = (_blackPeiceOnFocusIndex - 8);
  }
  else{
    _blackPeiceOnFocusIndex = ( _blackPeiceOnFocusIndex + 8 ) ;
  }
  _setFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);

}


/**
 * @brief Move the Focus to chess peice below.
 *
 * @param rootWindow
 */
void ChessBoard::setFocusDown(WINDOW* rootWindow){
  _removeFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);
  if(_blackPeiceOnFocusIndex & (1<<3)){
    _blackPeiceOnFocusIndex = (_blackPeiceOnFocusIndex - 8);
  }
  else{
    _blackPeiceOnFocusIndex = ( _blackPeiceOnFocusIndex + 8 ) ;
  }
  _setFocusOnPeice(rootWindow,*_blackChessPeices[_blackPeiceOnFocusIndex]);
}

/**
 * @brief Rotate the Board 180 degrees.
 */
void ChessBoard::rotate() {}

void ChessBoard::update() {}
