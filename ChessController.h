#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include "ProjectTypes.h"

class ApplicationController;
class ChessController
{
public:
    ChessController(ApplicationController* app);
    void checkPiece();
    void waitOpponentMove();
    void calculateNextMove();
    void setChessPiece(bool isBlack);
    void setOpponentMove(ChessMove chessMove);
    ChessMove nextMove();
private:
    ApplicationController* m_app;
    char m_chessBoard[CHESS_ROW][CHESS_COL];
    bool m_chessPieceDetected;
    bool m_isBlack;
    bool m_isOpponentMoved;
    bool m_isNextMoveCalculated;
    ChessMove m_nextMove;
};

#endif // CHESSCONTROLLER_H
