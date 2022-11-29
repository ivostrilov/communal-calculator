import QtQuick 2.15

Item {
    signal settingCellsCompleted()
    signal tariffsMayChanged(var tariffs)

    function changeSettingCellValue(index, value) {
        let value_str = Number.parseFloat(value).toFixed(2)
        settingPanel.settingCellsList[index].valueTextInput.text = value_str
    }

    SettingsPanel {
        id: settingPanel

        anchors.fill: parent

        titleText: "Tariff"

        Component.onCompleted: {
            addSettingCell("Cold water")
            addSettingCell("Hot water")
            addSettingCell("Sink water")
            addSettingCell("Electricity T1")
            addSettingCell("Electricity T2")
            addSettingCell("Electricity T3")
            settingCellsCompleted()
        }

        onParamsMayChanged: {
            let coldWaterTariff = settingCellsList[0].valueTextInput.text
            let hotWaterTariff = settingCellsList[1].valueTextInput.text
            let sinkWaterTariff = settingCellsList[2].valueTextInput.text
            let t1WaterTariff = settingCellsList[3].valueTextInput.text
            let t2WaterTariff = settingCellsList[4].valueTextInput.text
            let t3WaterTariff = settingCellsList[5].valueTextInput.text

            let values = {
                "coldWaterTariff": coldWaterTariff,
                "hotWaterTariff": hotWaterTariff,
                "sinkWaterTariff": sinkWaterTariff,
                "T1Tariff": t1WaterTariff,
                "T2Tariff": t2WaterTariff,
                "T3Tariff": t3WaterTariff,
            }

            tariffsMayChanged(values)
        }
    }
}
