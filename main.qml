import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Window {
    visible: true
    minimumHeight: 700
    minimumWidth: 600
    maximumHeight: 700
    maximumWidth: 600
    title: "Tic Tac Toe"

    Connections {
        target: gameEngine
        onGameFinished: {
            (winner === "draw") ? messageDialog.show("Round finished", " Draw round!", StandardIcon.Information) : messageDialog.show("Round finished", " " + winner + " won a round!", StandardIcon.Information)
        }
    }

    MessageDialog {
        id: messageDialog
        onAccepted: {
            gameEngine.loadGridModel()
            messageDialog.close();
        }
        function show(title,caption,icon) {
            messageDialog.title = title;
            messageDialog.text = caption;
            messageDialog.icon = icon;
            messageDialog.open();
        }
    }

    Rectangle {
        id: mainRect
        anchors.fill: parent
        color: "white"

        Column {
            spacing: 2

            Rectangle {
                id: titleRect
                width: mainRect.width
                height: 100
                color: "white"

                Text {
                    id: player1;
                    text: "Player "
                    anchors { left: parent.left; leftMargin: 70; top: parent.top; topMargin: 25 }
                    font.pixelSize: 25
                }

                Image {
                    id: player1Icon
                    source: "qrc:/pictures/pictures/circle.png"
                    height: player1.height
                    anchors { left: player1.right; leftMargin: 10; top: parent.top; topMargin: 25 }
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                }

                Text {
                    id: player1Result;
                    text: gameEngine.circleWins
                    anchors { top: parent.top; topMargin: 60; horizontalCenter: player1.horizontalCenter }
                    font.pixelSize: 25
                    font.bold: true
                    onTextChanged: result1Animation.running = true

                    SequentialAnimation {
                        id: result1Animation
                        PropertyAnimation {duration: 100; target: player1Result; property: "scale"; from: 1; to: 2}
                        PropertyAnimation {duration: 700; target: player1Result; property: "scale"; from: 2; to: 1}
                    }
                }

                Text {
                    id: player2;
                    text: "Player "
                    anchors { right: parent.right; rightMargin: 70; top: parent.top; topMargin: 25 }
                    font.pixelSize: 25
                }

                Image {
                    id: player2Icon
                    source: "qrc:/pictures/pictures/cross.png"
                    height: player2.height
                    anchors { left: player2.right; leftMargin: 10; top: parent.top; topMargin: 25 }
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                }

                Text {
                    id: player2Result;
                    text: gameEngine.crossWins
                    anchors { top: parent.top; topMargin: 60; horizontalCenter: player2.horizontalCenter }
                    font.pixelSize: 25
                    font.bold: true
                    onTextChanged: result2Animation.running = true

                    SequentialAnimation {
                        id: result2Animation
                        PropertyAnimation {duration: 100; target: player2Result; property: "scale"; from: 1; to: 2}
                        PropertyAnimation {duration: 700; target: player2Result; property: "scale"; from: 2; to: 1}
                    }
                }

                Text {
                    id: currentMove;
                    text: "Move: "
                    anchors { top: parent.top; topMargin: 60; horizontalCenter: parent.horizontalCenter }
                    font.pixelSize: 25
                }

                Image {
                    id: currentMoveIcon
                    source: "qrc:/pictures/pictures/" + gameEngine.getPicture(gameEngine.currentMove)
                    height: currentMove.height
                    anchors { left: currentMove.right; leftMargin: 10; top: parent.top; topMargin: 60 }
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    onSourceChanged: currentMoveAnimation.running = true
                    scale: 1

                    SequentialAnimation {
                        id: currentMoveAnimation
                        PropertyAnimation {duration: 100; target: currentMoveIcon; property: "scale"; from: 1; to: 2}
                        PropertyAnimation {duration: 700; target: currentMoveIcon; property: "scale"; from: 2; to: 1}
                    }
                }

            }

            GridView {
                id: gameGrid
                width: mainRect.width
                height: 700
                cellWidth: 200; cellHeight: 200
                focus: true
                model: gameEngine.gridModel

                delegate: Item {
                    id: delegateItem
                    width: 200; height: 200

                    Rectangle {
                        id: rect
                        anchors.fill: parent
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "steelblue"
                        border.color: "black"
                    }

                    Image {
                        id: icon
                        source: ((gameEngine.getPicture(gameEngine.getCellState(index))) === "") ? "" : "qrc:/pictures/pictures/" + gameEngine.getPicture(gameEngine.getCellState(index))
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        onClicked: {
                            gameEngine.setCellState(gameEngine.currentMove, index)
                        }

                        Binding {
                            target: rect
                            property: "opacity"
                            value: "0.5"
                            when: mouseArea.pressed
                        }
                    }

                }
            }
        }
   }
}
