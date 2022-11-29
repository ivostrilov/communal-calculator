import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    property alias backgroundColor: mainRectangle.color
    property alias logText: logTextInput.text

    signal calculateSummary()

    id: mainRectangle

    radius: 12

    RowLayout {
        anchors.fill: parent

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft

            radius: 16
            color: "#454444"

            TextEdit {
                id: logTextInput

                anchors.fill: parent

                verticalAlignment: TextEdit.AlignVCenter
                horizontalAlignment: TextEdit.AlignLeft
                leftPadding: 32

                color: "#fef1e2"
                readOnly: true
                selectByMouse: true

                Text {
                    id: hintText

                    anchors.centerIn: parent

                    color: "#aaa"
                    text: qsTr("Press 'calculate'\nto calculate your communal")

                    visible: !logTextInput.text
                }
            }
        }

        CustomButton {
            id: calculateSummaryButton

            width: 75
            radius: 16
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft

            cursorShape: hovered ? Qt.PointingHandCursor : Qt.ArrowCursor
            color: hovered ? "#f4b159" : "#f2a33c"
            text: qsTr("calculate")

            onClicked: {
                calculateSummary()
            }
        }
    }
}
