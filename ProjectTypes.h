#ifndef PROJECTTYPES_H
#define PROJECTTYPES_H

typedef enum{
    MACHINE_INITIALIZE_ROBOT = 0,
    MACHINE_CHECK_PIECE,
    MACHINE_WAIT_OPPONENT_MOVE,
    MACHINE_CALCULATE_NEXT_MOVE,
    MACHINE_ATTACK_OPPONENT_PIECE,
    MACHINE_MOVE_PIECE,
    MACHINE_MOVE_PIECE_EXECUTE,
    MACHINE_RETURN_HOME,
} MACHINE_STATE;

#define MOTOR_DIR_NORMAL 1
#define MOTOR_DIR_INVERSE -1
#define MOTOR_MAX_SEQUENCE 20
#define MOVE_CODE_NO_MOVE 0
#define MOVE_CODE_HAS_MOVE 1
typedef enum {
    MOTOR_BASE,
    MOTOR_ARM1,
    MOTOR_ARM2,
    MOTOR_ARM3,
    MOTOR_CAP,
    MOTOR_MAX,
} MOTOR;

typedef enum {
    ROBOT_INIT_STATE,
    ROBOT_RETURN_HOME,
    ROBOT_MOVE_PIECE
} ROBOT_STATE;

typedef struct {
    bool moveInit;
    float armAngle[MOTOR_MAX];
} MoveLocation;

#define CHESS_ROW 8
#define CHESS_COL 8

typedef struct {
    int startRow;
    int startCol;
    int stopRow;
    int stopCol;
    bool castles;
    bool enpassant;
    char promotePiece;
} ChessMove;
#endif // PROJECTTYPES_H
