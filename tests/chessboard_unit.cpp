#include "gtest/gtest.h"
#include "chessboard.h"
#include "ncursesw/ncurses.h"

class ChessBoardTest: public testing::Test{
protected:
  ChessBoardTest():_chessBoard(new ChessBoard(64,32)){
    _rootWindow = newwin(34, 50, 2, 5);
    _chessBoard->init();
  }

  ~ChessBoardTest(){
    delwin(_rootWindow);
    delete _chessBoard;
  }

  WINDOW* _rootWindow{nullptr};
  ChessBoard* _chessBoard{nullptr};
};

TEST_F(ChessBoardTest,defaultCtor){
  EXPECT_EQ(3, _chessBoard->getCurrentWhitePeiceIndex());
  EXPECT_EQ(7, _chessBoard->getCurrentBlackPeiceIndex());
}

TEST_F(ChessBoardTest, arrowKeyEvent){
  _chessBoard->setFocusRight(_rootWindow);

  // Right Arrow key event validation.
  EXPECT_EQ(0, _chessBoard->getCurrentBlackPeiceIndex());
  EXPECT_NE(nullptr, 
          _chessBoard->getBlackPeiceOnIndex(
              _chessBoard->getCurrentBlackPeiceIndex()));

  // Down Arrow Key validation.
  _chessBoard->setFocusDown(_rootWindow);
  EXPECT_EQ(8, _chessBoard->getCurrentBlackPeiceIndex());
  EXPECT_NE(nullptr, 
          _chessBoard->getBlackPeiceOnIndex(
              _chessBoard->getCurrentBlackPeiceIndex()));

  // Up Arrow Key validation.
  _chessBoard->setFocusUp(_rootWindow);
  _chessBoard->setFocusUp(_rootWindow);
  EXPECT_EQ(8, _chessBoard->getCurrentBlackPeiceIndex());
  EXPECT_NE(nullptr, 
          _chessBoard->getBlackPeiceOnIndex(
              _chessBoard->getCurrentBlackPeiceIndex()));
  
  // Left Arrow key validation.
  _chessBoard->setFocusLeft(_rootWindow);
  EXPECT_EQ(15, _chessBoard->getCurrentBlackPeiceIndex());
  EXPECT_NE(nullptr, 
          _chessBoard->getBlackPeiceOnIndex(
              _chessBoard->getCurrentBlackPeiceIndex()));
  
}
