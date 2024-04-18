import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
    signal moveCurrentToPreviousClicked();

    color: "#f2a33c"
    radius: 12

    RowLayout {
        anchors.fill: parent

        Item { Layout.fillWidth: true }

        Rectangle {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.rightMargin: 16

            width: 100
            height: 20
            radius: 8
            color: "#454444"

            Text {
                anchors.centerIn: parent
                color: "#eeeeee"

                text: qsTr("Previous")
            }
        }

        ToolButton {
            id: moveToolButton

            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.rightMargin: 16
            Layout.maximumWidth: 20
            Layout.maximumHeight: 24

            MouseArea {
                id: buttonMousArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {
                    buttonMousArea.cursorShape = Qt.PointingHandCursor
                }
                onExited: {
                    buttonMousArea.cursorShape = Qt.ArrowCursor
                }
                onClicked: {
                    moveToolButton.clicked()
                }
            }

            background: Image {
                source: "../icons/back-arrow-white.png"
            }

            onClicked: {
                moveCurrentToPreviousClicked()
            }
        }

        Rectangle {
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.rightMargin: 16

            width: 100
            height: 20
            radius: 8
            color: "#454444"

            Text {
                anchors.centerIn: parent
                color: "#eeeeee"

                text: qsTr("Current")
            }
        }
    }
}
