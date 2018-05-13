pragma Singleton
import QtQuick 2.9

Item {

    function hscale(size) {
        return Math.round(size * (widthWindow / widthWindowReference))
    }
    function vscale(size) {
        return Math.round(size * (heightWindow / heightWindowReference))
    }
    function tscale(size) {
        return Math.round((hscale(size) + vscale(size)) / 2)
    }

    property alias fontAwesome: fontAwesomeLoader.name

    readonly property real widthWindow: 1080
    readonly property real heightWindow: 720
    readonly property real widthWindowReference: 1080
    readonly property real heightWindowReference: 720

    readonly property color colourBackground: "#f7f6f6"

    readonly property real sizeScreenMargin: tscale(20)
    readonly property real sizeControlSpacing: tscale(10)

    readonly property real widthLoginBar: 200
    readonly property real heightLoginBar: 30
    readonly property real sizeLoginBottomMargin: 100

    //--------------------------------navBar---------------------------
    readonly property color colourNavigationBarBackground: "#544b82"
    readonly property color colourNavigationBarFont: "#ffffff"
    readonly property int pixelSizeNavigationBarIcon: tscale(42)
    readonly property int pixelSizeNavigationBarText: tscale(22)
    readonly property real widthNavigationBarCollapsed: widthNavigationButtonIcon
    readonly property real heightNavigationBarExpanded: widthNavigationButton

    readonly property real widthNavigationButtonIcon: hscale(80) //width of navBar
    readonly property real heightNavigationButtonIcon: widthNavigationButtonIcon
    readonly property real widthNavigationButtonDescription: hscale(160)
    readonly property real heightNavigationButtonDescription: heightNavigationButtonIcon
    readonly property real widthNavigationButton: widthNavigationButtonIcon + widthNavigationButtonDescription
    readonly property real heightNavigationButton: Math.max(heightNavigationButtonIcon, heightNavigationButtonDescription)


    //------------------------topBar----------------------
    readonly property color colourCommandBarBackground: "#d8d8eb"
    readonly property color colourCommandBarFont: "#131313"
    readonly property color colourCommandBarFontDisabled: "#d8d8eb"
    readonly property real heightCommandBar: heightCommandButton
    readonly property int pixelSizeCommandBarIcon: tscale(32)
    readonly property int pixelSizeCommandBarText: tscale(12)
    //---------------------------------------------------

    readonly property real widthCommandButton: hscale(160)
    readonly property real heightCommandButton: tscale(80)

    readonly property color colourDataControlsBackground: "#ffffff" //?
    readonly property color colourDataControlsFont: "#131313"
    readonly property int pixelSizeDataControls: tscale(18)
    readonly property real widthDataControls: hscale(400)
    readonly property real heightDataControls: vscale(40)
    readonly property int sizeDataControlsRadius: tscale(5)

    readonly property color colourPanelBackground: "#ffffff"        //?
    readonly property color colourPanelBackgroundHover: "#ececec"
    readonly property color colourPanelHeaderBackground: "#131313"
    readonly property color colourPanelHeaderFont: "#ffffff"
    readonly property color colourPanelFont: "#131313"
    readonly property int pixelSizePanelHeader: tscale(18)
    readonly property real heightPanelHeader: vscale(40)
    readonly property real sizeShadowOffset: tscale(5)
    readonly property color colourShadow: "#dedede"

    readonly property color colourItemBackground: "#fefefe" //?
    readonly property color colourItemBackgroundHover: "#efefef"
    readonly property color colorItemBorder: "#efefef"
    readonly property color colorItemDateFont: "#636363"
    readonly property color colorItemTitleFont: "#131313"
    readonly property real sizeItemMargin: tscale(5)

    readonly property color colourDashboardBackground: "#ffffff" //?
    readonly property color colourDashboardFont: "#000000"
    readonly property int pixelSizeDashboard: tscale(30)
    readonly property int pixelSizeDashboardSmall: tscale(16)
    readonly property real sizeDashboardLogo: tscale(500)

    readonly property color colourDataSelectorBackground: "#131313"
    readonly property color colourDataControlsBackgroundSelected: "#f36f24"
    readonly property color colourDataSelectorFont: "#ffffff"

    //-------------------------Button------------------------
    readonly property real widthFormButton: 150
    readonly property real heightFormButton: 105
    readonly property color colorFormButtonBackground: "#d8d8eb"
    readonly property color colorFormButtonFont: "#000000"
    readonly property color colorFormButtonBorder: "#000000"
    readonly property int pixelSizeFormButtonIcon: 32
    readonly property int pixelSizeFormButtonText: 16
    readonly property int sizeFormButtonRadius: 10

    //---------------------Login view---------------------------
     readonly property real loginFieldPositionY: 250



    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.ttf"
    }
}

