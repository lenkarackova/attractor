import QtQuick
import QtQuick.Controls

Column {
    id: column
    default property alias item: ld.sourceComponent
    property string title: ""
    property string itemIcon: ""
    anchors.left: parent.left; anchors.right: parent.right
    spacing: 6

    Rectangle {
        id: titleRect
        height: 30
        width: column.width
        color: "#333333"
        border.width: 1
        border.color: "#444444"

        ToolButton {
            id: icon
            text: itemIcon
            width: titleRect.height; height: titleRect.height
            anchors.verticalCenter: titleRect.verticalCenter
            anchors.left: titleRect.left
            hoverEnabled: false
            font.pointSize: 16
        }

        Text {
            color: "white"
            text: title
            font.pointSize: 10
            anchors.verticalCenter: titleRect.verticalCenter
            anchors.left: icon.right
        }

        ToolButton {
            id: arrow
            text: "❯"
            width: titleRect.height; height: titleRect.height
            anchors.verticalCenter: titleRect.verticalCenter
            anchors.right: titleRect.right
            hoverEnabled: false
            font.pointSize: 10
            rotation: 90

            Behavior on rotation {
                NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
            }
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                content.show = !content.show
                arrow.rotation *= -1
            }            
            onEntered: parent.color = "#3F3F40"
            onExited: parent.color = "#333333"
        }
    }

    Item {
        id: content
        property bool show: true

        clip: true
        width: column.width
        height: show ? ld.height : 0

        Loader {
            id: ld
            y: content.height - height
        }

        Behavior on height {
            NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
        }
    }
}
