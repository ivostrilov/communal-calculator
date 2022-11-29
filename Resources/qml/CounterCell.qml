import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {  
    property alias titleText: titleText.text
    property alias prevDigitsTextInput: previousDigitsTextInput.textInput
    property alias curDigitsTextInput: currentDigitsTextInput.textInput

    signal inputFinished()

    id: mainRectangle

    color: "#f2a33c"
    radius: 12

    RowLayout {
        anchors.fill: parent

        Text {
            id: titleText

            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.leftMargin: 16

            color: "#fef1e2"
        }

        Item { Layout.fillWidth: true }

        DigitsTextInput {
            id: previousDigitsTextInput

            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.rightMargin: 16

            hintText: "previous"
            backgroundColor: "#454444"

            Keys.onReturnPressed: {
                currentDigitsTextInput.textInput.forceActiveFocus()
            }
        }

        DigitsTextInput {
            id: currentDigitsTextInput

            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.rightMargin: 16

            hintText: "current"
            backgroundColor: "#454444"

            Keys.onReturnPressed: {
                inputFinished()
            }
        }
    }
}
