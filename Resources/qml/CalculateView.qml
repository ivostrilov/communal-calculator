import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: calculateView

    Connections {
        target: modelView
        ignoreUnknownSignals: true
        function onSummaryCalculated(calculation) {
            let log = calculation.log;
            let result = Number.parseFloat(calculation.result).toFixed(2)

            let text = log
            text = text.concat("\n\nSummary: ", result)

            calculateSummaryControl.logText = text
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
            property int counterCellsAlignment: Qt.AlignTop | Qt.AlignHCenter
            property int counterCellsLeftMargins: 16
            property int counterCellsRightMargins: 16
            property bool counterCellsFillWidth: true
            property int counterCellsFillHeight: 40
        }

        id: contentLayout
        anchors.fill: parent

        spacing: 10

        CounterCell {
            id: coldWaterCounterCell

            Layout.alignment: internal.counterCellsAlignment
            Layout.leftMargin: internal.counterCellsLeftMargins
            Layout.topMargin: 16;
            Layout.rightMargin: internal.counterCellsRightMargins
            Layout.fillWidth: internal.counterCellsFillWidth
            height: internal.counterCellsFillHeight

            titleText: qsTr("Cold water")

            onInputFinished: {
                hotWaterCounterCell.prevDigitsTextInput.forceActiveFocus()
            }
        }

        CounterCell {
            id: hotWaterCounterCell

            Layout.alignment: internal.counterCellsAlignment
            Layout.leftMargin: internal.counterCellsLeftMargins
            Layout.rightMargin: internal.counterCellsRightMargins
            Layout.fillWidth: internal.counterCellsFillWidth
            height: internal.counterCellsFillHeight

            titleText: qsTr("Hot water")

            onInputFinished: {
                electricityT1CounterCell.prevDigitsTextInput.forceActiveFocus()
            }
        }

        CounterCell {
            id: electricityT1CounterCell

            Layout.alignment: internal.counterCellsAlignment
            Layout.leftMargin: internal.counterCellsLeftMargins
            Layout.rightMargin: internal.counterCellsRightMargins
            Layout.fillWidth: internal.counterCellsFillWidth
            height: internal.counterCellsFillHeight

            titleText: qsTr("Electricity T1")

            onInputFinished: {
                electricityT2CounterCell.prevDigitsTextInput.forceActiveFocus()
            }
        }

        CounterCell {
            id: electricityT2CounterCell

            Layout.alignment: internal.counterCellsAlignment
            Layout.leftMargin: internal.counterCellsLeftMargins
            Layout.rightMargin: internal.counterCellsRightMargins
            Layout.fillWidth: internal.counterCellsFillWidth
            height: internal.counterCellsFillHeight

            titleText: qsTr("Electricity T2")

            onInputFinished: {
                electricityT3CounterCell.prevDigitsTextInput.forceActiveFocus()
            }
        }

        CounterCell {
            id: electricityT3CounterCell

            Layout.alignment: internal.counterCellsAlignment
            Layout.leftMargin: internal.counterCellsLeftMargins
            Layout.rightMargin: internal.counterCellsRightMargins
            Layout.fillWidth: internal.counterCellsFillWidth
            height: internal.counterCellsFillHeight

            titleText: qsTr("Electricity T3")

            onInputFinished: {
                electricityT3CounterCell.forceActiveFocus()
            }
        }

        CalculateSummaryControl {
            id: calculateSummaryControl

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            Layout.bottomMargin: 16
            Layout.fillWidth: true
            Layout.fillHeight: true

            backgroundColor: "transparent"

            onCalculateSummary: {
                let values = {
                    "coldWaterPrev": coldWaterCounterCell.prevDigitsTextInput.text,
                    "coldWaterCur": coldWaterCounterCell.curDigitsTextInput.text,
                    "hotWaterPrev": hotWaterCounterCell.prevDigitsTextInput.text,
                    "hotWaterCur": hotWaterCounterCell.curDigitsTextInput.text,
                    "T1Prev": electricityT1CounterCell.prevDigitsTextInput.text,
                    "T1Cur": electricityT1CounterCell.curDigitsTextInput.text,
                    "T2Prev": electricityT2CounterCell.prevDigitsTextInput.text,
                    "T2Cur": electricityT2CounterCell.curDigitsTextInput.text,
                    "T3Prev": electricityT3CounterCell.prevDigitsTextInput.text,
                    "T3Cur": electricityT3CounterCell.curDigitsTextInput.text
                }

                modelView.onCalculateSummary(values)
            }
        }
    }
}
