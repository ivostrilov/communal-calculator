import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Page {
    id: settingsView

    Connections {
        id: connections

        target: modelView
        ignoreUnknownSignals: true
        function onAppCfgChanged(cfg) {
            let coldWaterTariff = cfg.coldWaterTariff
            let hotWaterTariff = cfg.hotWaterTariff
            let waterSinkTariff = cfg.waterSinkTariff
            let electricityT1Tariff = cfg.T1Tariff
            let electricityT2Tariff = cfg.T2Tariff
            let electricityT3Tariff = cfg.T3Tariff

            tariffSettingsPanel.changeSettingCellValue(0, coldWaterTariff)
            tariffSettingsPanel.changeSettingCellValue(1, hotWaterTariff)
            tariffSettingsPanel.changeSettingCellValue(2, waterSinkTariff)
            tariffSettingsPanel.changeSettingCellValue(3, electricityT1Tariff)
            tariffSettingsPanel.changeSettingCellValue(4, electricityT2Tariff)
            tariffSettingsPanel.changeSettingCellValue(5, electricityT3Tariff)
        }
    }

    focusPolicy: Qt.ClickFocus

    background: Rectangle {
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#585959" }
            GradientStop { position: 1.0; color: "#656666" }
        }
    }

    ColumnLayout {
        QtObject {
            id: internal
            property int panelsAlignment: Qt.AlignTop | Qt.AlignHCenter
            property int leftRightMargin: 16
        }

        id: panelsLayout

        anchors.fill: parent
        spacing: 1

        TariffSettingsPanel {
            id: tariffSettingsPanel

            onSettingCellsCompleted: {
                let cfg = modelView.onGetAppConfiguration()
                connections.onAppCfgChanged(cfg)
            }

            Layout.alignment: internal.panelsAlignment

            Layout.leftMargin: internal.leftRightMargin
            Layout.topMargin: 16
            Layout.rightMargin: internal.leftRightMargin

            height: 410
            Layout.fillWidth: true

            onTariffsMayChanged: (tariffs) => {
                                     modelView.onAppCfgChanged(tariffs)
                                 }
        }

        Item {
            Layout.alignment: internal.panelsAlignment

            Layout.leftMargin: internal.leftRightMargin
            Layout.rightMargin: internal.leftRightMargin

            Layout.fillHeight: true
            Layout.fillWidth: true

            // Rectangle {
            //     anchors.fill: parent
            //     color: "green"
            // }
        }
    }
}
