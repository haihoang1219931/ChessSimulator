import QtQuick 2.0

Item {
    id: root
    Grid {
        id: grid
        columns: 8
        rows: 8
        Repeater {
            id: repeater
            delegate: Rectangle {
                width: root.width / grid.columns
                height: root.height / grid.rows
                color: modelData === 0? "#90652C" : "#DEB887"
            }
        }
    }
    Grid {
        id: gridChessPiece
        columns: 8
        rows: 8
        Repeater {
            id: repeaterChessPiece
            delegate: Text {
                text: modelData.piece !== 0 ? String.fromCharCode(9811 + (1 - modelData.color) * 6 + modelData.piece):""
                width: root.width / grid.columns
                height: root.height / grid.rows
                font.pointSize : root.width / grid.columns * 0.6
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
    Component.onCompleted: {
        var chessBoardModel = [];
        for(var row =0; row <8; row ++) {
            for(var col =0; col <8; col ++){
                chessBoardModel[row*8+col] = (row + col) % 2
            }
        }
        repeater.model = chessBoardModel;
        var NOPIECE = 0;
        var KING = 1;
        var QUEEN = 2;
        var ROOK = 3;
        var BISHOP = 4;
        var KNIGHT = 5;
        var PAWN = 6;
        var chessPieceModel = [
            {color:1,piece:ROOK},{color:1,piece:KNIGHT},{color:1,piece:BISHOP},{color:1,piece:QUEEN},{color:1,piece:KING},{color:1,piece:BISHOP},{color:1,piece:KNIGHT},{color:1,piece:ROOK},
            {color:1,piece:PAWN},{color:1,piece:PAWN},{color:1,piece:PAWN},{color:1,piece:PAWN},{color:1,piece:PAWN},{color:1,piece:PAWN},{color:1,piece:PAWN},{color:1,piece:PAWN},
            {color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},
            {color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},
            {color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},
            {color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},{color:0,piece:NOPIECE},
            {color:0,piece:PAWN},{color:0,piece:PAWN},{color:0,piece:PAWN},{color:0,piece:PAWN},{color:0,piece:PAWN},{color:0,piece:PAWN},{color:0,piece:PAWN},{color:0,piece:PAWN},
            {color:0,piece:ROOK},{color:0,piece:KNIGHT},{color:0,piece:BISHOP},{color:0,piece:QUEEN},{color:0,piece:KING},{color:0,piece:BISHOP},{color:0,piece:KNIGHT},{color:0,piece:ROOK},
        ];
        repeaterChessPiece.model = chessPieceModel;
    }
}
