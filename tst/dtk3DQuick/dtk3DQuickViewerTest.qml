/* dtk3DQuickViewerTest.qml ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 23:20:48 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr 11 15:51:53 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 392
 */

/* Change Log:
 * 
 */

import    QtQuick 2.0
import dtk3DQuick 1.0

Item {

  width: 1024;
  height: 512;

// ///////////////////////////////////////////////////////////////////
// Quick3DShortcuts
// ///////////////////////////////////////////////////////////////////

  Quick3DShortcuts {

    view: view;
    
    width: 300;
    
    anchors.top: parent.top;
    anchors.right: parent.right;
    anchors.bottom: parent.bottom;
  }

// ///////////////////////////////////////////////////////////////////
// Quick3DViewShadow
// ///////////////////////////////////////////////////////////////////

  Quick3DViewShadow {
    view: view;
  }

// ///////////////////////////////////////////////////////////////////
// Quick3DView
// ///////////////////////////////////////////////////////////////////

  Quick3DView {
      
    id: view;
    
    x: 0;
    y: 0;

    width: parent.width;
    height: parent.height;
    
    Quick3DScene {
      
      id: scene;
      
      items: [
        Quick3DPoint { id: item1; x: +0.0; color: "red"; },
        Quick3DPoint { id: item2; x: +2.0; color: "green"; },
        Quick3DPoint { id: item3; x: -2.0; color: "blue"; }
      ]
    }

    states: [
      State {
        name: "default"
        PropertyChanges { target: view; x: 0; }
      },
      State {
        name: "ShiftedLeft";
        PropertyChanges { target: view; x: -300; }
      },
      State {
        name: "ShiftedRight";
        PropertyChanges { target: view; x: +300; }
      }
    ] 

    transitions: [
      Transition {
        NumberAnimation { property: "x"; duration: 200; }
      }
    ]
  }

// ///////////////////////////////////////////////////////////////////
// Key handling
// ///////////////////////////////////////////////////////////////////

  Keys.onDigit0Pressed: view.state = "default";
  Keys.onDigit1Pressed: view.state = "ShiftedRight";
  Keys.onDigit2Pressed: view.state = "ShiftedLeft";
}