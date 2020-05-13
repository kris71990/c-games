#include <array>
#include <map>
#include <string>

// #include "Pawn.hpp"
// #include "Rook.hpp"
// #include "Knight.hpp"
// #include "Bishop.hpp"
// #include "Queen.hpp"
// #include "King.hpp"

class Board {
public:
  enum class Piece { king, queen, pawn, rook, bishop, knight };
  std::array<std::array<std::string, 8>, 8> board;

  struct Position {
    int x,y;
    Position(const Position &p, int dx = 0, int dy = 0) { *this = p; x += dx; y += dy;}
    Position(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(const Position &p) const { return (x < p.x) || (x == p.x && y < p.y); }
    bool operator==(const Position &p) const { return x == p.x && y == p.y; }
  };

  std::map<Position, Piece> white_pieces;
  std::map<Position, Piece> black_pieces;
  std::map<Piece, std::string> board_chars =
    {
      { Piece::pawn, "P" },
      { Piece::rook, "R" },
      { Piece::knight, "Kn" },
      { Piece::bishop, "B" },
      { Piece::queen, "Q" },
      { Piece::king, "K" },
    };
  
  void init();
  void draw_board();
};

void Board::init()
{
  for (int i = 0; i < 8; ++i) {
    black_pieces[Position(1, i)] = Piece::pawn;
    white_pieces[Position(6, i)] = Piece::pawn;
    
    if (i == 0 || i == 7) {
      black_pieces[Position(0, i)] = Piece::rook;
      white_pieces[Position(7, i)] = Piece::rook;
    }

    if (i == 1 || i == 6) {
      black_pieces[Position(0, i)] = Piece::knight;
      white_pieces[Position(7, i)] = Piece::knight;
    }

    if (i == 2 || i == 5) {
      black_pieces[Position(0, i)] = Piece::bishop;
      white_pieces[Position(7, i)] = Piece::bishop;
    }

    if (i == 3) {
      black_pieces[Position(0, i)] = Piece::queen;
      white_pieces[Position(7, i)] = Piece::queen;
    }

    if (i == 4) {
      black_pieces[Position(0, i)] = Piece::king;
      white_pieces[Position(7, i)] = Piece::king;
    }
  }

  for (int i = 0; i < 8; ++i) { board[i].fill(" "); }

  std::map<Position, Piece>::iterator it;
  for (it = white_pieces.begin(); it != white_pieces.end(); ++it) {
    board[it -> first.x][it -> first.y] = board_chars[it -> second]; //"\x1b[1;97m"
  }

  for (it = black_pieces.begin(); it != black_pieces.end(); ++it) {
    board[it -> first.x][it -> first.y] = board_chars[it -> second]; //"\x1b[1;30m" + 
  }
}

void Board::draw_board() 
{
  std::cout << "\n  a  |  b  |  c  |  d  |  e  |  f  |  g  |  h  | \n";

  for (int x = 0; x < 8; ++x) {
    std::cout << "\n------------------------------------------------\n";
    for (int y = 0; y < 8; ++y) {
      std::cout << "  " << board[x][y] << "  |";
      // if (board[x][y] == "\x1b[1;97mKn" || board[x][y] == "\x1b[1;30mKn") {
      //   if ((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) {
      //     std::cout << "\x1b[100m  " << board[x][y] << " \x1b[0m|";
      //   } else {
      //     std::cout << "\x1b[47m  " << board[x][y] << " \x1b[0m|";
      //   }
      // } else {
      //   if ((x % 2 == 1 && y % 2 == 0) || (x % 2 == 0 && y % 2 == 1)) {
      //     std::cout << "\x1b[100m  " << board[x][y] << "  \x1b[0m|";
      //   } else {
      //     std::cout << "\x1b[47m  " << board[x][y] << "  \x1b[0m|";
      //   }
      // }
    }
    std::cout << "  " << std::abs(x - 8);
  }
  std::cout << "\n------------------------------------------------\n\n";
}