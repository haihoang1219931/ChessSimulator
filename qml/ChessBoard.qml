import QtQuick 2.0
import "qrc:/ChessSupport.js" as ChessSupport
Item {
    id: root
    property var chessClicked
    Grid {
        id: grid
        columns: 8
        rows: 8
        Repeater {
            id: repeater
            delegate: Rectangle {
                width: root.width / grid.columns
                height: root.height / grid.rows
                color: (modelData.row+modelData.col)%2 === 0? "#90652C" : "#DEB887"
                Rectangle {
                    anchors.fill: parent
                    color: "transparent"
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            parent.color = "yellow"
                        }
                        onExited: {
                            parent.color = "transparent"
                        }
                        onClicked: {
                            parent.color = "blue"
                            chessClicked = repeaterChessPiece.model[index];
                            var possibleMoves = ChessSupport.validMove(repeaterChessPiece.model,modelData.row,modelData.col);
                            var chessModel = ChessSupport.createChessBoardModel();
                            possibleMoves.forEach((item)=> {
                                chessModel[item.row*8+item.col] = item;
                            });
                            repeater.model = chessModel;
                        }
                    }
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "transparent"
                    border.color: modelData.suggest?"gray":"transparent"
                    border.width: 10
                    width: typeof chessClicked !== 'undefined' &&
                            ChessSupport.isOppositeSide(repeaterChessPiece.model[index].piece,chessClicked.piece)?parent.width:20
                    height: typeof chessClicked !== 'undefined' &&
                            ChessSupport.isOppositeSide(repeaterChessPiece.model[index].piece,chessClicked.piece)?parent.height:20
                    radius: width/2
                }
            }
        }
    }
    Grid {
        id: gridChessPiece
        columns: 8
        rows: 8
        Repeater {
            id: repeaterChessPiece
            delegate: Item {
                width: root.width / grid.columns
                height: root.height / grid.rows


                Text {
                    text: ChessSupport.charCode(modelData.piece)
                    anchors.fill: parent
                    font.pointSize : root.width / grid.columns * 0.6
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
    Component.onCompleted: {
        repeater.model = ChessSupport.createChessBoardModel();
        repeaterChessPiece.model = ChessSupport.createChessPiecesModel();
    }
}
