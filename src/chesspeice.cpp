#include "chesspeice.h"
#include "ncursesw/ncurses.h"
#include <cmath>
#include <utility>

ChessPeiceFactory *ChessPeiceFactory::_instance = nullptr;

ChessPeiceFactory::ChessPeiceFactory() {}
ChessPeice::~ChessPeice() {}


/**
 * @brief Get the instance of singleton class ChessPeiceFactory
 *
 * @return ChessPeiceFactory*
 */
ChessPeiceFactory *ChessPeiceFactory::getInstance() {
  if (!_instance) {
    _instance = new ChessPeiceFactory();
  }
  return _instance;
}


/**
 * @brief Return a pointer to a Subclass of type ChessPeice.
 *
 * @param peiceType : Category of chess peice.
 * @param isWhite   : Is the Chess Peice white.
 * @param coordinates : Coordinates where teh peice is supossed to be spawn.
 *
 * @return ChessPeice*
 */
ChessPeice *ChessPeiceFactory::getPeice(PeiceType peiceType, bool isWhite,
                            std::pair<uint8_t, uint8_t> coordinates) {
  switch (peiceType) {
  case PeiceType::KNIGHT: {
    return new Knight(isWhite, coordinates);
  }
  case PeiceType::ROOK: {
    return new Rook(isWhite, coordinates);
  }
  case PeiceType::PAWN: {
    return new Pawn(isWhite, coordinates);
  }
  case PeiceType::BISHOP: {
    return new Bishop(isWhite, coordinates);
  }
  case PeiceType::KING: {
    return new King(isWhite, coordinates);
  }
  case PeiceType::QUEEN: {
    return new Queen(isWhite, coordinates);
  }
  default: {
    return nullptr;
  }
  }
}

ChessPeice::ChessPeice(bool isWhitePeice,
                       std::pair<uint8_t, uint8_t> currentCoordinates)
    : isWhite(isWhitePeice), _currentCoordinates(currentCoordinates) {}

std::pair<uint8_t, uint8_t> ChessPeice::getCoordinates() const {
  return _currentCoordinates;
}


/**
 * @brief Change the coordinates of chessPeice.
 *
 * @param coordinates : new x , y coordinates of the chess peice.
 */
void ChessPeice::setCoordinates(const std::pair<uint8_t, uint8_t> &coordinates) {
  if (coordinates.first >= 0 && coordinates.first < 8 &&
      coordinates.second >= 0 && coordinates.second < 8) {
    this->_currentCoordinates = coordinates;
  }
}

const char **ChessPeice::getAsset() { return asset; }

void Knight::initAsset() {
  asset[0] = "▂▟▟ ";
  asset[1] = "▔▐▓ ";
  asset[2] = "▃▓▓▙";
}
void Pawn::initAsset() {
  asset[0] = "▟██▙";
  asset[1] = " ▟▙";
  asset[2] = "▟██▙";
}

void Rook::initAsset() {
  asset[0] = "▙▟▙▟";
  asset[1] = " ▓▓";
  asset[2] = "▟██▙";
}

void Bishop::initAsset() {
  asset[0] = "▜▓▛";
  asset[1] = "▀█▀";
  asset[2] = "▟█▙";
}

void King::initAsset() {
  asset[0] = "▜➕▛";
  asset[1] = " ▓▓";
  asset[2] = "▟██▙";
}

void Queen::initAsset() {
  asset[0] = "▜▟▙▛";
  asset[1] = " ▙▟ ";
  asset[2] = "▟▓▓▙";
}

Knight::Knight(bool isWhite, std::pair<uint8_t, uint8_t> coordinates)
    : ChessPeice(isWhite, coordinates) {
  this->initAsset();
}

Rook::Rook(bool isWhite, std::pair<uint8_t, uint8_t> coordinates)
    : ChessPeice(isWhite, coordinates) {
  this->initAsset();
}

Pawn::Pawn(bool isWhite, std::pair<uint8_t, uint8_t> coordinates)
    : ChessPeice(isWhite, coordinates) {
  this->initAsset();
}

Bishop::Bishop(bool isWhite, std::pair<uint8_t, uint8_t> coordinates)
    : ChessPeice(isWhite, coordinates) {
  this->initAsset();
}

King::King(bool isWhite, std::pair<uint8_t, uint8_t> coordinates)
    : ChessPeice(isWhite, coordinates) {
  this->initAsset();
}

Queen::Queen(bool isWhite, std::pair<uint8_t, uint8_t> coordinates)
    : ChessPeice(isWhite, coordinates) {
  this->initAsset();
}
