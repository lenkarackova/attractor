import QtQuick
import QtQuick3D
import QtQuick3D.Helpers
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import AttractorExplorer 1.0

ApplicationWindow {
    id: window
    width: 900
    height: 700
    visible: true
    title: "AttractorExplorer"

    ViewModel {
        id: viewModel
    }

    View3D {
        id: view
        height: parent.height
        anchors.left: parent.left
        anchors.right: tabBar.left
        anchors.rightMargin: 4

        environment: SceneEnvironment {
            backgroundMode: SceneEnvironment.Color
            clearColor: viewModel.colorModel.backgroundColor
        }

        OrthographicCamera {
            id: camera
            property real zoom: 5.0
            position: Qt.vector3d(0, 0, 100)
            clipNear: 0
            verticalMagnification: zoom
            horizontalMagnification: zoom
        }

        Model {
            id: pointCloud
            geometry: viewModel.pointCloud
            pivot: viewModel.attractor.center
            scale: viewModel.attractor.scale
            materials: DefaultMaterial  {
                lighting: DefaultMaterial.NoLighting
                vertexColorsEnabled: true
                opacity: viewModel.opacity
            }
        }

        WasdController {
            id: attractorController
            keysEnabled: false
            controlledObject: pointCloud
        }

        WheelHandler {
            id: wheelHandler
            orientation: Qt.Vertical
            target: null
            acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
            onWheel: event => {
                        let zoom = camera.zoom + (event.angleDelta.y > 0 ? -0.4 : 0.4)
                        camera.zoom = Math.max(0.1, zoom)
            }
        }

        DragHandler {
            acceptedButtons: Qt.MiddleButton
            target: null

            xAxis.onActiveValueChanged: (delta) => { camera.position.x -= delta / camera.zoom }
            yAxis.onActiveValueChanged: (delta) => { camera.position.y += delta / camera.zoom }
        }
    }

    TabBar {
        id: tabBar
        width: 250
        anchors.right: parent.right

        TabButton {
            text: "Attractor"
        }

        TabButton {
            text: "View"
        }

        TabButton {
            text: "Tools"
        }
    }

    StackLayout {
        width: tabBar.width - 3
        anchors.left: tabBar.left
        anchors.top: tabBar.bottom
        currentIndex: tabBar.currentIndex
        anchors.leftMargin: 0
        anchors.topMargin: 10
        anchors.bottomMargin: 5

        Item {
            id: tabAttractor

            ColumnLayout {
                anchors.fill: parent
                spacing: 6

                Button {
                    text: "Random Attractor"
                    Layout.alignment: Qt.AlignCenter
                    onClicked: {
                        viewModel.randomAttractor()
                        pointCloud.rotation = Qt.quaternion(1, 0, 0, 0)
                    }
                }

                Label {
                    text: "Attractor type:"
                    Layout.leftMargin: 6
                }

                ComboBox {
                    id: attractorTypes
                    model: viewModel.attractor.attractorTypes
                    Layout.fillWidth: true
                    Layout.preferredHeight: 30
                    Layout.leftMargin: 6
                    Layout.rightMargin: 6
                    onActivated: {
                        viewModel.attractor.type = currentValue
                        pointCloud.rotation = Qt.quaternion(1, 0, 0, 0)
                    }
                }

                ListView {
                    id: listView
                    model: viewModel.attractor.parameterModel
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.minimumHeight: 600
                    Layout.leftMargin: 10

                    delegate: Row {
                        id: delegateRow
                        height: 30

                        Text {
                            width: 20
                            color: 'white'
                            font.pointSize: 11
                            text: model.name + ":"
                            anchors.verticalCenter: parent.verticalCenter
                            horizontalAlignment: Text.AlignRight
                        }

                        Slider {
                            width: 120
                            anchors.verticalCenter: parent.verticalCenter
                            id: paremeterSlider
                            from: model.min
                            to: model.max
                            value: model.value
                            stepSize: 0.01
                            onValueChanged: if (model.value !== value) model.value = value
                        }

                        Text {
                            id: text
                            width: 40
                            color: 'white'
                            font.pointSize: 9
                            anchors.verticalCenter: parent.verticalCenter
                            text: Math.round(model.value * 1000) / 1000
                        }

                        ToolButton {
                            width: 20
                            text: "-"
                            font.pointSize: 12
                            anchors.verticalCenter: parent.verticalCenter
                            onClicked: model.value -= 0.001
                        }

                        ToolButton {
                            width: 20
                            text: "+"
                            font.pointSize: 12
                            anchors.verticalCenter: parent.verticalCenter
                            onClicked: model.value += 0.001
                        }
                    }
                }
            }
        }

        Item {
            id: tabView

            Column {
                anchors.fill: parent
                spacing: -1

                AccordionItem {
                    title: "Viewport"
                    itemIcon: "❀"

                    Column {
                        padding: 6
                        spacing: 6
                        bottomPadding: 18

                        Label {
                            text: "Point count:"
                        }

                        Slider {
                            id: pointCount
                            from: 0
                            to: 1000000
                            height: 15
                            value: viewModel.pointCloud.count
                            onMoved: viewModel.pointCloud.count = pointCount.value
                            width: tabView.width - 20
                        }

                        Label {
                            text: "Opacity:"
                        }

                        Slider {
                            id: opacitySlider
                            from: 0.0
                            to: 1.0
                            height: 15
                            value: viewModel.opacity
                            onMoved: viewModel.opacity = opacitySlider.value
                            width: tabView.width - 20
                        }
                    }
                }

                AccordionItem {
                    title: "Colors"
                    itemIcon: "✿"

                    Column {
                        padding: 6
                        spacing: 6
                        bottomPadding: 18

                        width: parent.width

                        Label {
                            text: "Coloring mode:"
                        }

                        ComboBox {
                            id: colorMode
                            model: viewModel.colorModel.coloringModes
                            height: 30
                            width: tabView.width - 20
                            currentIndex: viewModel.colorModel.coloringMode
                            onActivated: viewModel.colorModel.coloringMode = currentIndex
                        }

                        Label {
                            text: "Attractor color:"
                        }

                        Rectangle {
                            id: solidColor
                            color: viewModel.colorModel.attractorColor
                            visible: colorMode.currentIndex === ColorModel.Single
                            width: colorMode.width
                            height: colorMode.height
                            border.color: 'gray'
                            border.width: 1
                            radius: 5

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    colorDialog.open()
                                }
                            }
                        }

                        ComboBox {
                            id: gradientSwitch
                            width: colorMode.width
                            height: colorMode.height
                            model: viewModel.colorModel.colorGradients
                            visible: colorMode.currentIndex !== ColorModel.Single

                            currentIndex: viewModel.colorModel.gradientIndex
                            onActivated: viewModel.colorModel.gradientIndex = currentIndex

                            delegate: ItemDelegate {
                                id: gradientDelegate
                                width: gradientSwitch.width
                                height: gradientSwitch.height

                                required property int index
                                required property var model

                                background: GradientRectangle {
                                    model: viewModel.colorModel.colorGradients[index]
                                    border.color: highlighted ? 'white' : 'gray'
                                    border.width: highlighted ? 2 : 1
                                    width: gradientSwitch.width
                                    //color: highlighted ? 'white' : "transparent"
                                }

                                highlighted: gradientSwitch.highlightedIndex === index
                            }

                            background: GradientRectangle {
                                id: gradientBg
                                model: viewModel.colorModel.gradientStops
                                //border.color: 'gray'
                                border.width: 1
                                radius: 5
                            }
                        }

                        Label {
                            text: "Background color:"
                        }

                        Rectangle {
                            id: backgroundColor
                            color: viewModel.colorModel.backgroundColor
                            width: colorMode.width
                            height: colorMode.height
                            border.color: 'gray'
                            border.width: 1
                            radius: 5

                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: {
                                    colorDialogBg.open()
                                }
                                onEntered: {
                                    backgroundColor.border.color = 'white'
                                }
                                onExited: {
                                    backgroundColor.border.color = 'gray'
                                }
                            }
                        }

                        ColorDialog {
                            id: colorDialogBg
                            options: ColorDialog.NoEyeDropperButton
                            selectedColor: viewModel.colorModel.backgroundColor
                            onAccepted: viewModel.colorModel.backgroundColor = selectedColor
                        }

                        ColorDialog {
                            id: colorDialog
                            options: ColorDialog.NoEyeDropperButton
                            selectedColor: viewModel.colorModel.attractorColor
                            onAccepted: viewModel.colorModel.attractorColor = selectedColor
                        }
                    }
                }
            }
        }

        Item {
            id: tabTools

            Column {
                anchors.fill: parent
                spacing: -1

                AccordionItem {
                    title: "Export"
                    itemIcon: "❃"

                    Column {
                        padding: 6
                        spacing: 6
                        bottomPadding: 18

                        Label {
                            text: "Point Count:"
                        }

                        SpinBox {
                            id: exportPointCount
                            height: 30
                            from: 1000
                            to: 1000000
                            value: 50000
                            stepSize: 1000
                        }

                        Button {
                            Layout.alignment: Qt.AlignCenter
                            text: "Export as .obj"
                            onClicked: fileDialog.open()
                        }

                        FileDialog {
                            id: fileDialog
                            defaultSuffix: "obj"
                            fileMode: FileDialog.SaveFile
                            nameFilters: ["OBJ files (*.obj)"]
                            onAccepted: viewModel.attractor.exportOBJ(selectedFile, exportPointCount.value)
                        }
                    }
                }


                AccordionItem {
                    title: "Render"
                    itemIcon: "❃"

                    Column {
                        padding: 6
                        spacing: 6

                        /*Row {
                            Button {
                                text: "Viewport render"
                            }

                            Button {
                                text: "Render image"
                            }
                        }

                        Label {
                            text: "Quality:"
                        }

                        ComboBox {
                            model: [ "Medium", "High", "Very High", "Custom" ]
                        }

                        Label {
                            text: "Background:"
                        }

                        ComboBox {
                            model: [ "Solid", "Transparent" ]
                        }

                        Label {
                            text: "Dimensions:"
                        }

                        ComboBox {
                            model: [ "Viewport", "800 x 600", "1024 x 768", "1920 x 1080" ]
                        }

                        Button {
                            text: "Render"
                        }*/
                    }
                }
            }
        }
    }
}


