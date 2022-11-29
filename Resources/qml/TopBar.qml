import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Rectangle {
    id: topBar

    signal backActivated()
    signal settinsActivated()

    property alias backButtonVisible: backButton.visible
    property alias settingsButtonVisible: settingsButton.visible

    width: parent.width
    height: 40

    color: "gray"

    ToolButton {
        id: backButton

        width: 28
        height: 28

        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        anchors.leftMargin: 8

        background: Image {
            source: "../icons/back-arrow.png"
        }

        onClicked: topBar.backActivated()
    }

    ToolButton {
        id: settingsButton

        width: 28
        height: 28

        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        anchors.rightMargin: 8

        background: Image {
            source: "../icons/settings.svg"
        }

        onClicked: topBar.settinsActivated()
    }
}
