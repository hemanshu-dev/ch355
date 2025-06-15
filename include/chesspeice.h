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

  ChessPeice *getPeice(PeiceType peiceType,bool isWhite,std::pair<uint8_t,uint8_t> coordinates);
  static ChessPeiceFactory *getInstance();
};

class ChessPeice {
private:
  const uint8_t _defaultLocationX{0};
  const uint8_t _defaultLocationY{0};
  std::pair<uint8_t, uint8_t> _currentCoordinates;
  virtual void initAsset()=0;
protected:
  const char *asset[3]{"","",""};
public:
  const bool isWhite{true};
  explicit ChessPeice(bool isWhitePeice,std::pair<uint8_t,uint8_t>currentCoordinates);
  virtual ~ChessPeice();
  std::pair<uint8_t, uint8_t> getCoordinates() const;
  void setCoordinates(const std::pair<uint8_t,uint8_t> &coordinates);
  const char **getAsset() ;
};

class Knight : public ChessPeice {
  // KNIGHT
  //  ▂▟▟
  //  ▔▐▓
  //  ▃▓▓▙
private:
  void initAsset() override;

public:
  explicit Knight(bool isWhite, std::pair<uint8_t, uint8_t> coordinates);
};

class Pawn : public ChessPeice {
  // PAWN
  //    ▟██▙
  //     ▟▙
  //    ▟██▙
private:
  void initAsset() override;

public:  
  explicit Pawn(bool isWhite, std::pair<uint8_t, uint8_t> coordinates);
};

class Bishop : public ChessPeice {
  // BISHOP
  //     ▜▓▛
  //     ▀█▀
  //     ▟█▙
private:
  void initAsset() override;

public:  
  explicit Bishop(bool isWhite, std::pair<uint8_t, uint8_t> coordinates);
};

class Rook : public ChessPeice {
  // ROOK
  //    ▙▟▙▟
  //     ▓▓
  //    ▟██▙
private:
  void initAsset() override;

public:  
  explicit Rook(bool isWhite, std::pair<uint8_t, uint8_t> coordinates);
};

class Queen : public ChessPeice {
  // QUEEN
  //    ▜▟▙▛
  //     ▙▟          ▙
  //    ▟▓▓▙
private:
  void initAsset() override;

public:  
  explicit Queen(bool isWhite, std::pair<uint8_t, uint8_t> coordinates);
};

class King : public ChessPeice {
  // KING
  //   ▜➕▛
  //    ▓▓
  //   ▟██▙
private:
  void initAsset() override;

public:  
  explicit King(bool isWhite, std::pair<uint8_t, uint8_t> coordinates);
};

#endif
