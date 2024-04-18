import QtQuick 2.15
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: calculateView

    function getCounterCellsValues() {
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

        return values
    }

    function floatToStr(value) {
        return Number.parseFloat(value).toFixed(3)
    }

    function readValuesHistory() {
        let history = modelView.onReadValuesHistory()

        let coldWaterPrev = floatToStr(history.coldWaterPrev)
        let coldWaterCur = floatToStr(history.coldWaterCur)
        coldWaterCounterCell.prevDigitsTextInput.text = coldWaterPrev
        coldWaterCounterCell.curDigitsTextInput.text = coldWaterCur

        let hotWaterPrev = floatToStr(history.hotWaterPrev)
        let hotWaterCur = floatToStr(history.hotWaterCur)
        hotWaterCounterCell.prevDigitsTextInput.text = hotWaterPrev
        hotWaterCounterCell.curDigitsTextInput.text = hotWaterCur

        let t1Prev = floatToStr(history.T1Prev)
        let t1Cur = floatToStr(history.T1Cur)
        electricityT1CounterCell.prevDigitsTextInput.text = t1Prev
        electricityT1CounterCell.curDigitsTextInput.text = t1Cur

        let t2Prev = floatToStr(history.T2Prev)
        let t2Cur = floatToStr(history.T2Cur)
        electricityT2CounterCell.prevDigitsTextInput.text = t2Prev
        electricityT2CounterCell.curDigitsTextInput.text = t2Cur

        let t3Prev = floatToStr(history.T3Prev)
        let t3Cur = floatToStr(history.T3Cur)
        electricityT3CounterCell.prevDigitsTextInput.text = t3Prev
        electricityT3CounterCell.curDigitsTextInput.text = t3Cur
    }

    Component.onCompleted: {
        readValuesHistory()
    }

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

        CounterValuesControlCell {
            id: counterValuesControlCell

            Layout.alignment: internal.counterCellsAlignment
            Layout.leftMargin: internal.counterCellsLeftMargins
            Layout.topMargin: 16;
            Layout.rightMargin: internal.counterCellsRightMargins
            Layout.fillWidth: internal.counterCellsFillWidth
            height: internal.counterCellsFillHeight

            onMoveCurrentToPreviousClicked: {
                coldWaterCounterCell.prevDigitsTextInput.text = coldWaterCounterCell.curDigitsTextInput.text
                coldWaterCounterCell.curDigitsTextInput.text = ""

                hotWaterCounterCell.prevDigitsTextInput.text = hotWaterCounterCell.curDigitsTextInput.text
                hotWaterCounterCell.curDigitsTextInput.text = ""

                electricityT1CounterCell.prevDigitsTextInput.text = electricityT1CounterCell.curDigitsTextInput.text
                electricityT1CounterCell.curDigitsTextInput.text = ""

                electricityT2CounterCell.prevDigitsTextInput.text = electricityT2CounterCell.curDigitsTextInput.text
                electricityT2CounterCell.curDigitsTextInput.text = ""

                electricityT3CounterCell.prevDigitsTextInput.text = electricityT3CounterCell.curDigitsTextInput.text
                electricityT3CounterCell.curDigitsTextInput.text = ""
            }
        }

        CounterCell {
            id: coldWaterCounterCell

            Layout.alignment: internal.counterCellsAlignment
            Layout.leftMargin: internal.counterCellsLeftMargins
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
                let values = getCounterCellsValues()
                modelView.onCalculateSummary(values)
                modelView.onSaveValuesHistory(values)
            }
        }
    }
}
