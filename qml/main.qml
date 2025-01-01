/***************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import diy 1.0
ApplicationWindow {
    id: wroot
    visible: true
    width: 1280
    height: 780
    title: qsTr("Chess Simulator")

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 960
        height: 780
        color: "#84af40"
        z: 0

        Item {
            id: canvas
            anchors.fill: parent
            VideoRender {
                id: videoRender
                anchors.fill: parent
            }
        }

        Label {
            id: lblMachineState
            x: 8
            y: 8
            width: 682
            height: 57
            color: "#ffffff"
            text: qsTr("MACHINE_STATE")
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
        }

        Column {
            id: column
            x: 546
            y: 71
            width: 394
            height: 400

            CheckBox {
                id: cbxAutomation
                text: qsTr("Automation")
                onCheckedChanged: {
                    mainProcess.pause(checked)
                }
            }

            Row {
                width: 240
                height: 40

                Label {
                    id: lblAngle1
                    width: 80
                    height: 40
                    text: qsTr("Angle1")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Slider {
                    id: sldAngle1
                    width: 150
                    stepSize: 1
                    to: 360
                    value: 0
                    onValueChanged: {
                        robot01.angle2 = -value
                    }
                }

                TextField {
                    id: txtText1
                    width: 100
                    text: qsTr(sldAngle1.value.toString())
                }

            }

            Row {
                width: 240
                height: 40

                Label {
                    id: lblAngle2
                    width: 80
                    height: 40
                    text: qsTr("Angle2")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Slider {
                    id: sldAngle2
                    width: 150
                    stepSize: 1
                    to: 360
                    value: 0
                    onValueChanged: {
                        robot01.angle3 = -value
                    }
                }

                TextField {
                    id: txtText2
                    width: 100
                    text: qsTr(sldAngle2.value.toString())
                }

            }

            Row {
                width: 240
                height: 40

                Label {
                    id: lblAngle3
                    width: 80
                    height: 40
                    text: qsTr("Angle3")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Slider {
                    id: sldAngle3
                    width: 150
                    stepSize: 1
                    to: 360
                    value: 0
                    onValueChanged: {
                        robot01.angle4 = -value
                    }
                }

                TextField {
                    id: txtText3
                    width: 100
                    text: qsTr(sldAngle3.value.toString())
                }

            }

            Row {
                width: 240
                height: 40

                Label {
                    id: lblAngle4
                    width: 80
                    height: 40
                    text: qsTr("Angle4")
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }

                Slider {
                    id: sldAngle4
                    width: 150
                    stepSize: 1
                    to: 100
                    value: 0
                    onValueChanged: {
                        robot01.grabberAngle = value/to
                    }
                }

                TextField {
                    id: txtText4
                    width: 100
                    text: qsTr(sldAngle4.value.toString())
                }

            }

        }
    }
    Column {
        anchors.left: parent.left
        anchors.leftMargin: 80
        spacing: 80
        Item {
            width: 350
            height: 320
            Grid {
                id: grid
                y: parent.height
                width: 320
                height: 40
                columns: 8
                rows: 1
                Repeater {
                    id: repeater
                    model: [0,1,0,1,0,1,0,1]
                    delegate: Rectangle {
                        width: grid.width / grid.columns
                        height: grid.height / grid.rows
                        color: modelData === 0? "#90652C" : "#DEB887"
                    }
                }
            }
            Robot {
                id: robot01
                x: parent.width
                y: parent.height
                width: 320
                angle1: -90
                angle2: 10
                angle3: -160
                angle4: -30
                arm1Width: 100
                arm2Width: 250
                arm3Width: 200
                arm4Width: 50
            }
        }
        Item {
            width: 350
            height: 320
            ChessBoard {
                width: 320
                height: 320
            }
            Robot {
                id: robot02
                x: parent.width
                y: parent.height/2-20
                width: 320
                angle1: 180
                angle2: 0
                angle3: 0
                arm1Width: 40
                arm2Width: 100
                arm3Width: 100
            }
        }
    }

    MainProcess {
        id: mainProcess
        onReadyToUpdate: {
            mainProcess.updateScreen();
        }
        onRobotChanged: {
            robot01.angle2 = -angle1;
            robot01.angle3 = -angle2;
            robot01.angle4 = -angle3;
            robot01.grabberAngle = angle4/100

        }
    }

    Component.onCompleted: {
        mainProcess.setRender(videoRender);
        mainProcess.startService();
    }
}
