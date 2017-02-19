import QtQuick 2.5
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 320
    height: 240
    title: qsTr("License Validator")

    signal validationRequested(url path)
    signal licenseFileSelected(url path)

    MouseArea {
        anchors.fill: parent

        ColumnLayout {
            id: columnLayout
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.fill: parent

            RowLayout {
                id: rowLayout
                anchors.fill: parent

                Text {
                    id: licenseHintText
                    width: 80
                    height: 20
                    anchors {
                        left: parent.left
                        right: chooseButton.left
                        top: parent.top

                        leftMargin: 25
                        rightMargin: 50
                        topMargin: 70
                    }
                    text: qsTr("License File")
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 12
                }

                Button {
                    id: chooseButton
                    anchors {
                        top: parent.top
                        right: parent.right

                        topMargin: 60
                        rightMargin: 50
                    }
                    text: qsTr("Choose")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    onClicked: licenseDialog.visible = true
                }
            }

            Button {
                id: validateButton
                text: qsTr("Validate")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                enabled: false
                onClicked: validationRequested(licenseDialog.fileUrl)
            }
        }
    }

    FileDialog {
        id: licenseDialog
        title: "Select license file"
        folder: shortcuts.home
        onAccepted: {
            validateButton.enabled = true
            licenseFileSelected(licenseDialog.fileUrl)
        }
        onRejected: Qt.quit()
    }
}
