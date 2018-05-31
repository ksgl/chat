## Service messages

# Commands from GUI to NET: 

/* commands to server */

{
    "command" : "user.register",
    "payload" : {
        "login" : "Ivan1998",
        "ip" : "",
        "password" : "sweethomealabama"
    }
}

{
    "command" : "user.login",
    "payload" : {
        "login" : "Ivan1998",
        "password" : "sweethomealabama"
    }
}

{
    "command" : "user.add_friend"
    "payload" : {
        "my_login" : "b",
        "friend_login" : "Ivan1998"
    }
}

/* commands to peers */

{
    "command" : "message.send"
    "payload" : {
    "message" : {
            "from" : "ksenia",
            "to" : "ivan",
            "to_ip" : "<ip of ivan>"
            "text" : "hello"
        }
    }
}


