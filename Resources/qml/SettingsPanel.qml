import QtQuick 2.15
import QtQuick.Layouts

Item {
    property alias titleText: titleText.text
    property alias settingCellsList: cellsItemLayout.settingCellsList

    signal paramsMayChanged()

    function addSettingCell(name) {
        cellsItemLayout.addSettingCell(name)
    }

    id: mainItem

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Text {
            id: titleText
            color: "#fef1e2"
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            color: "#454444"
            radius: 12

            ColumnLayout {
                anchors.fill: parent

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.topMargin: 10
                    Layout.bottomMargin: 10

                    ColumnLayout {
                        property list<SettingCell> settingCellsList
                        property list<Rectangle> separatorRectanglesList

                        function addSettingCell (name) {
                            if (settingCellsList.length > 0) {
                                var separator = separatorComponent.createObject(cellsItemLayout)
                                separatorRectanglesList.push(separator)
                            }

                            var cell = settingCellComponent.createObject(cellsItemLayout)
                            cell.titleText = name
                            settingCellsList.push(cell)
                        }

                        id: cellsItemLayout

                        anchors.fill: parent
                        spacing: 10

                        Component {
                            id: settingCellComponent

                            SettingCell {
                                height: 40
                                Layout.fillWidth: true

                                onFocusLost: {
                                    mainItem.paramsMayChanged()
                                }
                            }
                        }

                        Component {
                            id: separatorComponent

                            Rectangle {
                                height: 1
                                Layout.fillWidth: true
                                Layout.leftMargin: 16
                                Layout.rightMargin: 16
                                color: "#6f6f70"
                            }
                        }
                    }
                }
            }
        }
    }
}
