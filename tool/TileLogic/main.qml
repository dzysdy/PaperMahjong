import QtQuick 2.6
import QtQuick.Window 2.2
import cppinterface 1.0

Window {
    visible: true
    width: 1024
    height: 768
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
            tileView.model = pathArray;
        }

        onLonelyTilesUpdated: {
            var pathArray = tileString2Array(lonelyTiles);
            lonelyTileView.model = pathArray;
        }

        onReadyStepsUpdated: {
            readyStepsText.text = "Ready Steps: " + steps;
        }

        onDiscardTilesUpdated: {
            discardTileView.model = Qt.createQmlObject('import QtQuick 2.6; ListModel {}', this);
            for (var i = 0; i < dataList.length; i++) {
                discardTileView.model.append(dataList[i]);
            }
            //var subModel = Qt.createQmlObject('import QtQuick 2.6; ListModel {}', discardTileView);

        }
    }

    TextEdit {
        id: textEdit
        //text: qsTr("46679m13389p457s4p")
        text: qsTr("2223334456888p3s")
        //text: qsTr("123789m123789p22s")
        width: 250
        verticalAlignment: Text.AlignVCenter
        anchors.right: okBtn.left
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.rightMargin: 15
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
        anchors.horizontalCenter: parent.horizontalCenter
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
        id: readSteps
        anchors.verticalCenter: okBtn.verticalCenter
        anchors.left: okBtn.right
        anchors.leftMargin: 15
        height: okBtn.height
        width: readyStepsText.width + 30
        border.color: "black"
        border.width: 1
        Text {
            id: readyStepsText
            anchors.centerIn: parent
        }
    }

    ListView {
        id: tileView
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width*2/3
        height: 50
        anchors.top: textEdit.bottom
        anchors.topMargin: 20
        orientation : ListView.Horizontal
        clip: true
        Rectangle {
            anchors.fill: parent
            border.width: 2
            border.color: "#009000"
            color: "transparent"
        }
        delegate: Component {
            Image {
                id: tileImg
                source: modelData
            }
        }
    }

    ListView {
        id: lonelyTileView
        width: tileView.width
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: tileView.bottom
        anchors.topMargin: 20
        orientation : ListView.Horizontal
        clip: true
        Rectangle {
            anchors.fill: parent
            border.width: 2
            border.color: "#0090FF"
            color: "transparent"
        }
        delegate: Component {
            Image {
                id: tileImg
                source: modelData
            }
        }
    }

    ListView {
        id: discardTileView
        width: tileView.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: lonelyTileView.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 20
        anchors.bottomMargin: 30
        spacing: 10
        clip: true
        Rectangle {
            anchors.fill: parent
            border.width: 2
            border.color: "black"
            color: "transparent"
        }

        delegate: Component {
            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: discarTileImg.height
                Image {
                    id: discarTileImg
                    anchors.left: parent.left
                    source: "./images/" + discard + ".gif";
                }
                ListView {
                    id: subListView
                    anchors.top: discarTileImg.top
                    anchors.left: discarTileImg.right
                    anchors.right: parent.right
                    anchors.leftMargin: 30
                    orientation : ListView.Horizontal
                    height: discarTileImg.height
                    spacing: 10
                    delegate: Component {
                        Image {
                            id: tileImg
                            source: "./images/" + draw + ".gif";
                        }
                    }
                }

                Component.onCompleted: {
                    subListView.model = discardTileView.model.get(index).draws;
                }
            }
        }
    }
}
