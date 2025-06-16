import QtQuick

Rectangle {
    id: rectangle
    required property list<color> model

    gradient: Gradient {
        id: gradient
        orientation: Gradient.Horizontal
    }

    Component {
        id: gradientStop
        GradientStop {}
    }

    onModelChanged: {
        var stopsList = [];
        var length = model.length;

        for (let i = 0; i < length; i++) {
            var s = gradientStop.createObject(rectangle, {"position": i / length , "color": model[i]});
            stopsList.push(s);
        }

        gradient.stops = stopsList;
        border.color = "gray";
    }
}
