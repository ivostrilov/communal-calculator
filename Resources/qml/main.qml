import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: applicationWindow

    title: qsTr("Communal Calculator")
    minimumWidth: 600
    minimumHeight: 680
    visible: true

    header: TopBar {
        id: topBar

        onBackActivated: {
            stackView.pop()
        }

        onSettinsActivated: {
            stackView.push(settingsView)
        }

        backButtonVisible: stackView.depth > 1
        settingsButtonVisible: stackView.currentItem != settingsView
    }

    StackView {
        id: stackView
        initialItem: calculateView
        anchors.fill: parent

        Component {
            id: calculateView
            CalculateView {}
        }

        Item {
            id: settingsView
            SettingsView {
                anchors.fill: parent
            }
        }
    }
}
