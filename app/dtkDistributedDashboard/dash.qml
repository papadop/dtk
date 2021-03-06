
import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.0

import dtkDistributed 1.0

import "status.js" as Status

import jbQuick.Charts 1.0


ApplicationWindow {
    title: "DTK Distributed Dashboard"
    visible: true

    minimumHeight: 400
    minimumWidth: 600

    ListModel {
        id: servers
        ListElement { text: "localhost" }
        ListElement { text: "nef-devel.inria.fr" }
        ListElement { text: "fsophia.sophia.grid5000.fr" }
    }

    ListModel {
        id: types
        ListElement { text: "local" }
        ListElement { text: "torque" }
        ListElement { text: "oar" }
    }

    RowLayout {
        id: contentRow
        anchors.fill:parent
        anchors.margins: 8
        spacing: 16
        ColumnLayout {
            id: firstColumn
            Layout.minimumWidth: 400
            Layout.fillWidth: false
            RowLayout {
                id: serverrow

                Label {
                    id: serverLabel
                    text: "resources:"
                }

                ComboBox {
                    id: combo
                    editable: true
                    model: servers
                    currentIndex: 0
                    Layout.fillWidth: true
                    onCurrentIndexChanged: {
                        if (combotypes) {
                            /* console.log("index changed " + currentText +" " + combotypes.find(Status.guess_type(currentText))) */
                            combotypes.currentIndex = combotypes.find(Status.guess_type(currentText))
                        }
                    }
                }
                Label {
                    id: typeLabel
                    text: "type:"
                }
                ComboBox {
                    id: combotypes
                    editable: true
                    model: types
                    Layout.minimumWidth: 80
                    currentIndex: 0
                }
            }
            RowLayout {
                id: pathrow
                Label {
                    id: pathLabel
                    text: "path:"
                }
                TextEdit {
                    id: serverPath
                    Layout.fillWidth: true
                    text: "/home/nniclaus/git/dtk-github/build/bin/dtkDistributedServer"
                }
            }
            RowLayout {
                id: apppathrow
                Label {
                    id: apppathLabel
                    text: "application path:"
                }
                TextEdit {
                    id: slavePath
                    Layout.fillWidth: true
                    text: "dtkDistributedSlave"
                }
            }
            RowLayout {
                id: actionrow

                CheckBox {
                        id: tunnel
                        text: "SSH Tunnel"
                        checked: false
                    }
                Button {
                    id: connectBotton
                    text: "Connect"
                    tooltip: "Deploy resource manager daemon on remote host"
                    onClicked: {
                        controller.deploy( Status.url(false),combotypes.currentText, tunnel.checked, serverPath.text);
                        controller.connect( Status.url(false), tunnel.checked, true);
                        Status.show()
                    }
                }
                Button {
                    id: statusBotton
                    text: "Refresh"
                    tooltip:"Refresh status"
                    onClicked: {
                        Status.show()
                    }
                }
                Button {
                    id: quitBotton
                    text: "Stop"
                    tooltip:"Deconnect and stop server"
                    onClicked: {
                        controller.stop( Status.url(false) );
                    }
                }
            }
            RowLayout {
                id: submitrow

                Label {
                    id: nodesLabel
                    text: "nodes:"
                }
                SpinBox {
                    id: nodes
                    minimumValue: 1
                    value: 1
                }

                Label {
                    id: coresLabel
                    /* Layout.fillWidth: true */
                    text: "cores:"
                }

                SpinBox {
                    id: cores
                    minimumValue: 1
                    value: 1
                }

                Label {
                    id: walltimeLabel
                    text: "walltime:"
                }
                SpinBox {
                    id: wallHours
                    minimumValue: 0
                    value: 0
                }
                SpinBox {
                    id: wallMin
                    minimumValue: 0
                    value: 10
                    maximumValue: 59
                }
                SpinBox {
                    id: wallSec
                    minimumValue: 0
                    value: 0
                    maximumValue: 59
                }
            }
            RowLayout {
                id: submitrow2

                Label {
                    id:  policyLabel
                    text: "Distributed policy:"
                }
                ComboBox {
                    id: comboPolicies
                    editable: false
                    /* model: policies */
                    model: policy.types()
                    currentIndex: 0
                    Layout.fillWidth: true
                }
                Button {
                    id: submitButton
                    text: "Submit"
                    Layout.fillWidth: true
                    tooltip: "Submit a job on a resource manager"
                    onClicked: {
                        console.debug("submit");
                        Status.submit(nodes.value, cores.value, Status.setWalltime(wallHours.value,wallMin.value,wallSec.value))
                    }
                }
            }
            RowLayout {
                id: jobs
                Item {
                    id: root
                    anchors.fill: parent
                    /* anchors.margins: Qt.platform.os === "osx" ? 12 : 6 */
                    ListModel {
                        id: jobModel
                    }

                    TableView{
                        model: jobModel
                        anchors.fill: parent

                        TableViewColumn {
                            role: "id"
                            title: "jobid"
                            width: 72
                            resizable: false
                            movable: false
                        }
                        TableViewColumn {
                            role: "nodes"
                            title: "Nodes"
                            width: 52
                        }
                        TableViewColumn {
                            role: "cores"
                            title: "Cores"
                            width: 52
                            visible: true
                        }
                        TableViewColumn {
                            role: "queue"
                            title: "Queue"
                            width: 100
                            visible: true
                        }
                        TableViewColumn {
                            role: "user"
                            title: "User"
                            width: 100
                        }
                    }
                }
            }
            RowLayout {
                id: myjobs
                Item {
                    id: jobsitem
                    anchors.fill: parent
                    /* anchors.margins: Qt.platform.os === "osx" ? 12 : 6 */
                    ListModel {
                        id: myjobModel
                    }

                    TableView{
                        model: myjobModel
                        anchors.fill: parent

                        TableViewColumn {
                            role: "id"
                            title: "jobid"
                            width: 72
                            resizable: false
                            movable: false
                        }
                        TableViewColumn {
                            role: "nodes"
                            title: "Nodes"
                            width: 52
                        }
                        TableViewColumn {
                            role: "cores"
                            title: "Cores"
                            width: 52
                            visible: true
                        }
                        TableViewColumn {
                            role: "state"
                            title: "State"
                            width: 72
                            visible: true
                        }
                    }
                }
            }

        }
        RowLayout {
            id: chartrow
            Chart {
                id: cores_pie;
                width: 200;
                height: 200;
                chartAnimated: true;
                chartAnimationEasing: Easing.InOutElastic;
                chartAnimationDuration: 2000;
                chartType: Charts.ChartType.PIE;
                chartData:  [];
            }
            Chart {
                id: nodes_pie;
                width: 200;
                height: 200;
                chartAnimated: true;
                chartAnimationEasing: Easing.InOutElastic;
                chartAnimationDuration: 2000;
                chartType: Charts.ChartType.DOUGHNUT;
                chartData:  [];
            }
        }
    }

    DistributedController {
        id: controller
        property var jobs: { }
        onJobQueued: {
            console.debug("a job is queued");
            myjobModel.append({"id": jobid,"nodes" : NaN, "cores" : NaN, "state": "Queued"})
        }
        onJobStarted: {
            console.debug("a job is started");
            myjobModel.setProperty(Status.getJobIndex(jobid), "state", "Running")
        }
        onJobEnded: {
            console.debug("a job has ended");
            myjobModel.remove(Status.getJobIndex(jobid))
        }
    }
    DistributedPolicy {
        id: policy
    }
}
