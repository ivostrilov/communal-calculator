import QtQuick 2.15
import QtQuick.Layouts

Rectangle {
    property alias titleText: titleText.text
    property alias valueTextInput: valueDigitsTextInput.textInput

    signal focusLost()
    signal enterPressed()

    id: mainRectangle

    color: "transparent"

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
            id: valueDigitsTextInput

            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.rightMargin: 16

            backgroundColor: "#656666"

            onFocusLost: {
                mainRectangle.focusLost()
            }

            Keys.onReturnPressed: {
                inputFinished()
            }
        }
    }
}
