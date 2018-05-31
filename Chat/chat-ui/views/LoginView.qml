import QtQuick 2.9
import components 1.0
import assets 1.0
import CHAT 1.0

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Item {
    property LoginViewModel loginViewModel : masterController.ui_viewController.ui_loginViewModel
    property int loginState : loginViewModel.ui_state
    id: columnWithRectangle
    Rectangle {

        anchors.fill: parent
        color: Style.colourBackground

        ColumnLayout
        {
            anchors {
                centerIn: parent
            }

            Text {
                id:welcomeText
                bottomPadding: 50
                text: "Welcome to Messenger!"
                color: Style.colourDashboardFont
                font.pixelSize: Style.pixelSizeDashboard
            }

            InputString {
                id : log_loginInput
                description : "Login"
                inputText : loginViewModel.ui_login
            }

            InputString {
                id : log_passwordInput
                description : "Password"
                inputText : loginViewModel.ui_password
            }

            Rectangle {
                height: Style.heightCommandBar

                FormButton {
                    description: "Login"
                    onFormButtonClicked: {
                        loginViewModel.ui_login = log_loginInput.inputText
                        loginViewModel.ui_password = log_passwordInput.inputText
                        loginViewModel.onLoginButtonClicked()
                    }
                }
            }

            Rectangle {
                height: Style.heightCommandBar

                FormButton {
                    description: "To Registration"
                    onFormButtonClicked: {
                        masterController.ui_commandController.onRegisterViewExecuted()
                    }
                }
            }

            Button {
                id: proccessButton
                Layout.fillWidth: true
            }
        }
    }

    Connections {
        target: loginViewModel
        onChangeState: {
            loginState = loginViewModel.ui_state
        }
    }

    states: [
            State {
                name: "NotAuthenticated"
                when: loginState == 0
                PropertyChanges {
                    target: proccessButton
                    text: "Login"
                    onClicked: {

                    }
                }
            },
            State {
                name: "Authenticating"
                when: loginState == 1
                PropertyChanges {
                    target: proccessButton
                    text: "Authenticating..."
                    enabled: false
                }
            },
            State {
                name: "AuthenticationFailure"
                when: loginState == 2
                PropertyChanges {
                    target: proccessButton
                    text: "Authentication failed, restart"
                    onClicked: {

                    }
                }
            },
            State {
                name: "Authenticated"
                when: loginState == 3
                PropertyChanges {
                    target: proccessButton
                    text: "Logout"
                    onClicked: {

                    }
                }
            }
        ]

    /*
    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_loginViewContextCommands
    }
    */
}

