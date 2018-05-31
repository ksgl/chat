import QtQuick 2.9
import components 1.0
import assets 1.0
import CHAT 1.0

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Item {
    property RegistrationViewModel registrationViewModel : masterController.ui_viewController.ui_registrationViewModel
    property int registrationState : registrationViewModel.ui_state
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
                text: "It's great to see a new member!"
                color: Style.colourDashboardFont
                font.pixelSize: Style.pixelSizeDashboard
            }

            InputString {
                id : loginInput
                description : "Login"
                inputText : registrationViewModel.ui_login
            }

            InputString {
                id : passwordInput
                description : "Password"
                inputText : registrationViewModel.ui_password
            }

            Rectangle {
                height: Style.heightCommandBar

                FormButton {
                    description: "Register"
                    onFormButtonClicked: {
                        registrationViewModel.ui_login = loginInput.inputText
                        registrationViewModel.ui_password = passwordInput.inputText
                        registrationViewModel.onRegisterButtonClicked()
                    }
                }
            }

            Rectangle {
                height: Style.heightCommandBar

                FormButton {
                    description: "To Login"
                    onFormButtonClicked: {
                        masterController.ui_commandController.onLoginViewExecuted()
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
        target: registrationViewModel
        onChangeState: {
            registrationState = registrationViewModel.ui_state
        }
    }

    states: [
            State {
                name: "NotAuthenticated"
                when: registrationState == 0
                PropertyChanges {
                    target: proccessButton
                    text: "Login"
                    onClicked: {

                    }
                }
            },
            State {
                name: "Authenticating"
                when: registrationState == 1
                PropertyChanges {
                    target: proccessButton
                    text: "Authenticating..."
                    enabled: false
                }
            },
            State {
                name: "AuthenticationFailure"
                when: registrationState == 2
                PropertyChanges {
                    target: proccessButton
                    text: "Authentication failed, restart"
                    onClicked: {

                    }
                }
            },
            State {
                name: "AuthenticationFailure_UserExists"
                when: registrationState == 3
                PropertyChanges {
                    target: proccessButton
                    text: "Authentication failed, user exists, restart"
                    onClicked: {

                    }
                }
            },
            State {
                name: "Authenticated"
                when: registrationState == 4
                PropertyChanges {
                    target: proccessButton
                    text: "Logout"
                    onClicked: {

                    }
                }
            }
        ]

}
