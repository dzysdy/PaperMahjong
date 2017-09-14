import QtQuick 2.6
import QtQuick.Window 2.2
import cppinterface 1.0

Window {
    visible: true
    width: 800
    height: 480
    title: qsTr("Hello World")

    function analysisTiles(tileString) {
        console.log(qsTr('Clicked on background. Text: "' + tileString + '"'))
        cpp.analysisTiles(tileString)
    }

    function tileString2Array(tileString) {
        var pathArray = new Array;
        var array = tileString.split('-');
        for (var i = 0; i < array.length; i++) {
            var path = "./images/" + array[i] + ".gif";
            pathArray.push(path);
        }
        return pathArray;
    }

    CppInterface {
        id: cpp
        onTileModelUpdated: {
            console.log(tileModelData);
            var pathArray = tileString2Array(tileModelData);
            tileView .model = pathArray;
        }

        onLonelyTilesUpdated: {
            var pathArray = tileString2Array(lonelyTiles);
            lonelyTileView.model = pathArray;
        }

        onReadyStepsUpdated: {
            readyStepsText.text = "Ready Steps: " + steps;
        }
    }

    TextEdit {
        id: textEdit
        //text: qsTr("46679m13389p457s4p")
        text: qsTr("2223334456888p3s")
        width: 250
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        Rectangle {
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }

    Rectangle {
        id: okBtn
        anchors.verticalCenter: textEdit.verticalCenter
        anchors.left: textEdit.right
        anchors.leftMargin: 15
        height: textEdit.height + 20
        width: 45
        border.color: "black"
        border.width: 1
        Text {
            text: qsTr("ok")
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (textEdit.text !== "")
                    analysisTiles(textEdit.text)
            }
        }
    }

    Rectangle {
        anchors.verticalCenter: okBtn.verticalCenter
        anchors.left: okBtn.right
        anchors.leftMargin: 15
        height: okBtn.height
        width: readyStepsText.width + 30
        border.color: "black"
        border.width: 1
        Text {
            id: readyStepsText
            //text: qsTr("Ready Steps: ")
            anchors.centerIn: parent
        }
    }

    ListView {
        id: tileView
        width: parent.width
        anchors.top: textEdit.bottom
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
        orientation : ListView.Horizontal
        delegate: Component {
            Image {
                id: tileImg
                source: modelData
            }
        }
    }

    ListView {
        id: lonelyTileView
        width: parent.width
        anchors.top: tileView.bottom
        anchors.topMargin: 90
        anchors.horizontalCenter: parent.horizontalCenter
        orientation : ListView.Horizontal
        delegate: Component {
            Image {
                id: tileImg
                source: modelData
            }
        }
    }
}
