var NOPIECE = 0;
var WHITE = 1;
var BLACK = 2;

var W_KING = 3;
var W_QUEEN = 4;
var W_ROOK = 5;
var W_BISHOP = 6;
var W_KNIGHT = 7;
var W_PAWN = 8;

var B_KING = 9;
var B_QUEEN = 10;
var B_ROOK = 11;
var B_BISHOP = 12;
var B_KNIGHT = 13;
var B_PAWN = 14;


function createChessBoardModel() {
    var chessBoardModel = [];
    for(var row =0; row <8; row ++) {
        for(var col =0; col <8; col ++){
            chessBoardModel[row*8+col] = {row:row,col:col,suggest:false}
        }
    }
    return chessBoardModel;
}
function createChessPiecesModel(){
    var chessPieceModel = [
        {piece:W_ROOK},   {piece:W_PAWN},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:B_PAWN},{piece:B_ROOK},
        {piece:W_KNIGHT}, {piece:W_PAWN},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:B_PAWN},{piece:B_KNIGHT},
        {piece:W_BISHOP}, {piece:W_PAWN},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:B_PAWN},{piece:B_BISHOP},
        {piece:W_QUEEN},  {piece:W_PAWN},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:B_PAWN},{piece:B_QUEEN},
        {piece:W_KING},   {piece:W_PAWN},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:B_PAWN},{piece:B_KING},
        {piece:W_BISHOP}, {piece:W_PAWN},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:B_PAWN},{piece:B_BISHOP},
        {piece:W_KNIGHT}, {piece:W_PAWN},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:B_PAWN},{piece:B_KNIGHT},
        {piece:W_ROOK},   {piece:W_PAWN},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:NOPIECE},{piece:B_PAWN},{piece:B_ROOK},
    ];
    chessPieceModel[2*8+2] = {piece:B_ROOK}
    chessPieceModel[3*8+2] = {piece:B_ROOK}
    chessPieceModel[4*8+3] = {piece:B_ROOK}
    chessPieceModel[5*8+3] = {piece:W_ROOK}
    return chessPieceModel;
}
function chessSide(chessPiece) {
    if(chessPiece >= W_KING && chessPiece <= W_PAWN) {
        return WHITE;
    } else if(chessPiece >= B_KING && chessPiece <= B_PAWN) {
        return BLACK;
    } else {
        return NOPIECE;
    }
}
function charCode(chessPiece) {
    if(chessPiece >= W_KING && chessPiece <= W_PAWN) {
        return String.fromCharCode(9811 + 0 * 6 + chessPiece-W_KING+1);
    } else if(chessPiece >= B_KING && chessPiece <= B_PAWN) {
        return String.fromCharCode(9811 + 1 * 6 + chessPiece-B_KING+1);
    } else {
        return "";
    }
}
function isOppositeSide(firstPiece,secondPiece) {
    var firtSide = chessSide(firstPiece);
    var secondSide = chessSide(secondPiece);
    if(firtSide === NOPIECE || secondSide === NOPIECE) {
        return false;
    } else return firtSide !== secondSide;
}
function validMove(chessPieceModel,_row,_col) {
    var possibleMoves=[];
    var chessPiece = chessPieceModel[_row*8+_col]
//    console.log("chessPiece "+)
    switch(chessPiece.piece) {
    case W_PAWN: {
        if(chessSide(chessPieceModel[_row*8+_col+1].piece)=== NOPIECE)
            possibleMoves.push({row:_row,col:_col+1,suggest:true});
        if(chessSide(chessPieceModel[_row*8+_col+2].piece)=== NOPIECE && _col === 1)
            possibleMoves.push({row:_row,col:_col+2,suggest:true});
        if(_row-1 >= 0 && chessSide(chessPieceModel[(_row-1)*8+_col+1].piece)=== BLACK)
            possibleMoves.push({row:_row-1,col:_col+1,suggest:true});
        if(_row+1 < 8 && chessSide(chessPieceModel[(_row+1)*8+_col+1].piece)=== BLACK)
            possibleMoves.push({row:_row+1,col:_col+1,suggest:true});
        break;
    }
    case B_PAWN: {
        break;
    }
    }
    return possibleMoves;
}
