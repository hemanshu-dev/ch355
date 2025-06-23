#include <cstdio>
#include <iostream>
#include <cwchar>
#include <ostream>
#include "app.h"
#include "ncursesw/ncurses.h"
#include <clocale>

ChessApp *ChessApp::_app = nullptr;

ChessApp::ChessApp():_chessBoard(COLS,LINES) {}

/**
 * @brief
 *
 * @return Return a reference to ChessApp.
 */
ChessApp *ChessApp::getInstance() {
  if (!_app) {
    _app = new ChessApp();
  }
  return _app;
}

/**
 * @brief Clearing the screen and all the related data structs.
 */
ChessApp::~ChessApp() {
  delwin(rootWindow);
  endwin();
  delete _app;
}

void ChessApp::_initLogging() { return; }

/**
 * @brief Handles all the args passed to the binary.
 *
 * @param argc : Total number of args. index starts from 1.
 * @param argv[] : Arguments list.
 */
void ChessApp::handleArgs(int argc, char *argv[]) {
  if (argc <= 1) {
    return;
  }
}

/**
 * @brief Event loop
 */
void ChessApp::run() {
  int ch;
  while ((ch = wgetch(rootWindow)) != 113) {
    mvprintw(1, 4, "KEY_EVENT:  %d", ch);
//    refresh();
    switch (ch) {
    // Handle terminal resize event.

    case KEY_RESIZE:{
      clear();
      wborder(rootWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
      wrefresh(rootWindow);
      delwin(rootWindow);

      rootWindow = newwin(34, 50, 2, 5);
      mvprintw(0, 4, "Window Size: %d %d", LINES, COLS);
      refresh();
      _chessBoard.draw(rootWindow,12,12);  
//      _chessBoard.setFocusLeft(rootWindow);
      box(rootWindow, 0, 0);
      break;
    }
    // Handle for Left Key                     
    case 68:{
      // Change the focus to neighboring peice.
     _chessBoard.setFocusLeft(rootWindow);
     break;
    }
    // Right
    case 67:{
     _chessBoard.setFocusRight(rootWindow);
     break;
    }
    // UP
    case 65:{
     _chessBoard.setFocusUp(rootWindow);
     break;
    }
    // Down
    case 66:{
     _chessBoard.setFocusDown(rootWindow);
     break;
    }
    default:
      break;
    }
  }
  // Clear up screen
  delwin(rootWindow);
  endwin();
  return;
}

void ChessApp::init() {
  _initLogging();
  setlocale(LC_ALL, "");
  initscr();

  // Hide Cursor.  
  curs_set(0);
  start_color();

  // Disable Line Buffering and dont wait for carriage return. Makes character 
  // typed by user immidiately available to the program.
  cbreak();
  noecho();
  keypad(rootWindow, true);
  refresh();

  // Initial chess board outline.
  clear();
  rootWindow = newwin(34, 50, 2, 5);
  _chessBoard.init();
  _chessBoard.draw(rootWindow,12,12);
}
