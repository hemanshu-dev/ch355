#ifndef __CHESSPEICE_H__
#define __CHESSPEICE_H__

#include <cstdint>
#include <utility>

class ChessPeice;

class ChessPeiceFactory {
private:
  ChessPeiceFactory();
  static ChessPeiceFactory *_instance;

public:
  enum class PeiceType : uint8_t {
    KING = 0,
    QUEEN = 1,
    BISHOP = 2,
    ROOK = 3,
    KNIGHT = 4,
    PAWN = 5
  };

  ~ChessPeiceFactory();
  void operator=(const ChessPeiceFactory &) = delete;
  void operator=(const ChessPeiceFactory &&) = delete;
  ChessPeiceFactory(const ChessPeiceFactory &) = delete;

  ChessPeice *getPeice(PeiceType peiceType);
  static ChessPeiceFactory *getInstance();
};

class ChessPeice {
private:
  const uint8_t _defaultLocationX{0};
  const uint8_t _defaultLocationY{0};
  const bool _isWhite{true};
  std::pair<uint8_t, uint8_t> _currentCoordinates;

public:
  explicit ChessPeice(bool isWhite,std::pair<uint8_t,uint8_t>currentCoordinates);
  virtual ~ChessPeice();
  std::pair<uint8_t, uint8_t> getCoordinates() const;
  virtual const char **getAsset() = 0;
};

class Knight : public ChessPeice {
  // KNIGHT
  //  ▂▟▟
  //  ▔▐▓
  //  ▃▓▓▙
private:
  const char *asset[3]{"▂▟▟ ", "▔▐▓ ", "▃▓▓▙"};

public:
  explicit Knight(bool isWhite, std::pair<uint8_t, uint8_t> coordinates);
  const char **getAsset() override;
};

class Pawn : public ChessPeice {
  // PAWN
  //    ▟██▙
  //     ▟▙
  //    ▟██▙
private:
  const char *asset[3]{"▟██▙", " ▟▙ ", "▟██▙"};
};

class Bishop : public ChessPeice {
  // BISHOP
  //     ▜▓▛
  //     ▀█▀
  //     ▟█▙
};

class Rook : public ChessPeice {
  // ROOK
  //    ▙▟▙▟
  //     ▓▓
  //    ▟██▙
};

class Queen : public ChessPeice {
  // QUEEN
  //    ▜▟▙▛
  //     ▙▟          ▙
  //    ▟▓▓▙
};

class King : public ChessPeice {
  // KING
  //   ▜➕▛
  //    ▓▓
  //   ▟██▙
};

#endif
