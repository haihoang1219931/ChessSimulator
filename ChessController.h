#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#define CHESS_ROW 8
#define CHESS_COL 8
#define CHESS_ROW_1 0
#define CHESS_ROW_2 1
#define CHESS_ROW_3 2
#define CHESS_ROW_4 3
#define CHESS_ROW_5 4
#define CHESS_ROW_6 5
#define CHESS_ROW_7 6
#define CHESS_ROW_8 7
#define CHESS_COL_A 0
#define CHESS_COL_B 1
#define CHESS_COL_C 2
#define CHESS_COL_D 3
#define CHESS_COL_E 4
#define CHESS_COL_F 5
#define CHESS_COL_G 6
#define CHESS_COL_H 7
typedef enum {
    CHESS_SPACE,
    WHITE_ROOK,
    WHITE_KNIGHT,
    WHITE_BISHOP,
    WHITE_KING,
    WHITE_QUEEN,
    WHITE_PAWN,
    BLACK_ROOK,
    BLACK_KNIGHT,
    BLACK_BISHOP,
    BLACK_KING,
    BLACK_QUEEN,
    BLACK_PAWN,
} CHESS_PIECE;
#define CHESS_WHITE_ROOK
class ApplicationController;
class ChessController
{
public:
    ChessController(ApplicationController* app);
    void checkPiece();
    void waitOpponentMove();
    void calculateNextMove();
private:
    ApplicationController* m_app;
    unsigned char m_chessBoard[CHESS_ROW][CHESS_COL];
};

#endif // CHESSCONTROLLER_H
