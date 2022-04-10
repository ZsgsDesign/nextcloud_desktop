import QtQuick 2.15
import QtQuick.Window 2.15
import Style 1.0
import com.nextcloud.desktopclient 1.0
import QtQuick.Layouts 1.2
import QtMultimedia 5.15

Window {
    id: root
    flags: Qt.FramelessWindowHint

    readonly property int windowMargins: 50
    readonly property int windowWidth: 400
    readonly property int windowHeight: 200

    function declineCall() {
        root.close();
        ringSound.stop();
    }

    width: windowWidth
    height: windowHeight

    x: Screen.desktopAvailableWidth - windowWidth - windowMargins
    y: Screen.desktopAvailableHeight - windowHeight - windowMargins

    color: "transparent"

    Rectangle {
        anchors.fill: parent
        radius: Systray.useNormalWindow ? 0.0 : Style.trayWindowRadius
        color: Style.backgroundColor

        Audio {
            id: ringSound
            source: "qrc:///client/theme/call-notification.ogg"
            loops: 9 // about 45 seconds of audio playing
            autoPlay: true
            onStopped: root.declineCall()
        }

        ColumnLayout {
            anchors.centerIn: parent
            spacing: 10

            Text {
                id: message
                text: model.subject
                color: Style.ncTextColor
                font.pixelSize: Style.topLinePixelSize
            }

            Row {
                spacing: 10
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                CustomButton {
                    id: answerCall
                    readonly property string imageSrc: "image://svgimage-custom-color/wizard-talk.svg" + "/"

                    bgColor: Style.ncBlue

                    Layout.preferredWidth: Style.callNotificationPrimaryButtonMinWidth
                    Layout.preferredHeight: Style.callNotificationPrimaryButtonMinHeight

                    text: qsTr("Answer call")
                    toolTipText: qsTr("Answer call")

                    imageSource: imageSrc + Style.ncBlue
                    imageSourceHover: imageSrc + Style.ncTextColor

                    onClicked: {
                        activityModel.slotTriggerAction(model.index, model.index);
                        root.declineCall();
                    }
                }

                CustomButton {
                    id: declineCall

                    readonly property string imageSrc: "image://svgimage-custom-color/delete.svg" + "/"

                    bgColor: Style.errorBoxBackgroundColor

                    Layout.preferredWidth: Style.callNotificationPrimaryButtonMinWidth
                    Layout.preferredHeight: Style.callNotificationPrimaryButtonMinHeight

                    text: qsTr("Decline")
                    toolTipText: qsTr("Decline")

                    imageSource: imageSrc + Style.errorBoxBackgroundColor
                    imageSourceHover: imageSrc + Style.ncTextColor

                    onClicked: root.declineCall()
                }
            }
        }

    }
}
