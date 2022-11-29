import QtQuick 2.15

Rectangle {
    property bool hovered: false
    property bool pressed: pressed
    property alias cursorShape: buttonMousArea.cursorShape
    property alias text: buttonText.text

    signal clicked()

    id: customButton
    width: 100
    height: 40
    radius: 8
    color: customButton.pressed ? "grey" : "lightgrey"

    Text {
        id: buttonText

        text: customButton.text
        color: "black"
        anchors.centerIn: parent
    }

    MouseArea {
        id: buttonMousArea

        anchors.fill: parent

        hoverEnabled: true

        onEntered: {
            customButton.hovered = true
        }

        onExited: {
            customButton.hovered = false
        }

        onClicked: {
            customButton.clicked()
        }

        onPressedChanged: {
            customButton.pressed = pressed
        }
    }
}
