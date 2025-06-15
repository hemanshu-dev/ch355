#ifndef __APP_H__
#define __APP_H__

#include "ncursesw/ncurses.h"               
#include "chessboard.h"

/**
 * @brief Singleton Class than handles initialization, logging, networking etc.
 */
class ChessApp {
private:
  /// Pointer to Bounding rectangle of the chessboard.
  WINDOW *rootWindow;
  ChessBoard _chessBoard;
  static ChessApp *_app;

  void _initLogging();
  ChessApp();

public:
  ~ChessApp();
  void operator=(const ChessApp &) = delete;
  void operator=(const ChessApp &&) = delete;
  ChessApp(const ChessApp &) = delete;

  void handleArgs(int argc, char *argv[]);
  void run();
  void init();
  static ChessApp *getInstance();
};

#endif
