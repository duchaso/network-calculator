import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.2
import Client 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Client {
        id: client
    }

    RowLayout {
        anchors.centerIn: parent

        Rectangle {
            height: 50
            width: 200
            color: "grey"

            TextInput {
                id: example

                anchors.fill: parent
            }
        }
        Text {
            id: result

            text: "=" + client.result
        }

        Button {
            text: "OK"
            onClicked: {
                if (example.text != "")
                {
                    client.setInput(example.text);
                }
            }
        }
    }
}
