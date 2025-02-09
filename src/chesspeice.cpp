#include "chesspeice.h"
#include <utility>

ChessPeiceFactory *ChessPeiceFactory::_instance = nullptr;

ChessPeiceFactory::ChessPeiceFactory() {}
ChessPeice::~ChessPeice() {}

ChessPeiceFactory *ChessPeiceFactory::getInstance() {
  if (!_instance) {
    _instance = new ChessPeiceFactory();
  }
  return _instance;
}

ChessPeice *ChessPeiceFactory::getPeice(PeiceType peiceType) {
  return new Knight(true, std::make_pair(5, 5));
}

ChessPeice::ChessPeice(bool isWhite,
                       std::pair<uint8_t, uint8_t> currentCoordinates)
    : _isWhite(isWhite), _currentCoordinates(currentCoordinates) {}

std::pair<uint8_t, uint8_t> ChessPeice::getCoordinates()const 
{ return _currentCoordinates; }

Knight::Knight(bool isWhite, std::pair<uint8_t, uint8_t> coordinates)
    : ChessPeice(isWhite, coordinates) {}

const char **Knight::getAsset() { return asset; }
