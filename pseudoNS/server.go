package main

import (
	"net"
	"log"
	"fmt"
	"time"
	//"strings"
)
import "database/sql"
import _ "github.com/go-sql-driver/mysql"
import (
	"encoding/json"

)

const port = 1337



//CREATE TABLE `chat`.`chat` ( `id` INT(6) NOT NULL AUTO_INCREMENT ,
// `login` VARCHAR(30) NULL DEFAULT NULL ,
// `password` VARCHAR(30) NULL DEFAULT NULL ,
// `IP` VARCHAR(30) NOT NULL DEFAULT '0.0.0.0:0' ,
// PRIMARY KEY (`id`)) ENGINE = InnoDB;


//INSERT INTO `chat` (`id`, `login`, `password`, `IP`) VALUES (NULL, 'login', 'password', '127.0.0.1:1337');
//INSERT INTO `chat` (`id`, `login`, `password`, `IP`) VALUES (NULL, 'root', 'toor', '127.0.0.1:1447');

//var db, err = sql.Open("mysql", "root:546595@/chat")

type Answer struct {
	ID     string `json:"id"`
	Answer string `json:"answer"`
}

type Answer_IP struct {
	IP 	   string `json:"IP"`
	ID     string `json:"id"`
	Answer string `json:"answer"`
}

type Messege struct {
	Command string `json:"command"`
	Payload struct {
		ID 			  string `json:"id"`
		Login         string `json:"login"`
		Password      string `json:"password"`
		MyLogin       string `json:"my_login"`
		FriendLogin   string `json:"friend_login"`
		ToRemoveLogin string `json:"to_remove_login"`
		IP   		  string `json:"IP"`
	} `json:"payload"`
}


type Server struct {
	connection *net.UDPConn
	messages   chan string
	client     *net.UDPAddr //or use map with an uuid
}

var buffer = make([]byte, 1024)

func checkErr(err error) {
	if err != nil {
		panic(err)
	}
}

func errorCheck(err error, where string, kill bool) {
	if err != nil {
		log.Printf("‡‡‡ Error ‡‡‡ %s | %s", err.Error(), where)
		if kill {
			log.Fatalln("Script Terminated")
		}
	}
}




func (s *Server) handleMessage() {
	var buf [512]byte

	n, addr, err := s.connection.ReadFromUDP(buf[0:])
	errorCheck(err, "handleMessage", false)

	got := string(buf[0:n])
	log.Printf("a client [%s] sent [%s]\n", addr, got)

	// respond with something ?
	s.client = addr

	db, err := sql.Open("mysql", "root:@tcp(0.0.0.0:3306)/chat")
	if err != nil {
		log.Fatal(err)
	}


	defer db.Close()

	var msge  = []byte(got)

	//log.Printf("msge = " + string(msge))

	var IP  = addr.String()
	var msg_struct = Messege{}
	var msg_answer_FAIL = Answer{}





	err1 := json.Unmarshal(msge, &msg_struct)
	if err1 != nil {
		log.Fatal("error")
	}

	//log.Printf("msge = " + msg_struct.Payload.Password)


	//log.Printf(msg_command)

	msg_answer_FAIL.Answer = "FAIL"
	msg_answer_FAIL.ID = msg_struct.Payload.ID

	answer_to_client_json, err := json.Marshal(msg_answer_FAIL)
	if err != nil {
		fmt.Println(err)
		return
	}
	//log.Print(string(answer_to_client_json))

	switch msg_struct.Command {

	case "user.register":

		//check is avalible
		//SELECT `id` FROM `chat` WHERE `id` IS NOT NULL AND `login` LIKE 'root'

		var check_null sql.NullString
		err  :=
			db.QueryRow("select login from chat where id is not null and login = ?",
				msg_struct.Payload.Login).Scan(&check_null)



		if check_null.Valid {
			s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)
			log.Print(string(answer_to_client_json))
			break
		}
		//INSERT INTO `chat` (`id`, `login`, `password`, `IP`) VALUES (NULL, 'login', 'passwd', '127.0.0.1:1447');
		log.Printf("Client %s have ip = %s and password = %s", msg_struct.Payload.Login, IP, msg_struct.Payload.Password)

		insert ,err := db.Exec("INSERT INTO chat (login, password, IP) VALUES (?, ?, ?)",
			string(msg_struct.Payload.Login), string(msg_struct.Payload.Password), IP)
		if err != nil {
			log.Fatal(err)
			s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)//"FAIL INSERT"
			log.Print(string(answer_to_client_json))
			return
		}
		rowsAffected, err := insert.RowsAffected()
		if err != nil {
			log.Fatal(err)
			s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)//"FAIL INSERT"
			log.Print(string(answer_to_client_json))
			return
		}

		log.Printf("Client %s created successfully (%d row affected)\n", addr, rowsAffected)

		msg_answer_FAIL.Answer = "OK"

		answer_to_client_json, err := json.Marshal(msg_answer_FAIL)
		if err != nil {
			fmt.Println(err)
			return
		}

		s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"OK"}"`)
		log.Print(string(answer_to_client_json))

	case "user.login":
		var check_null sql.NullString
		_ = db.QueryRow("select login from chat where id is not null and login = ?",
			msg_struct.Payload.Login).Scan(&check_null)
		var check_user Messege


		if check_null.Valid {

			_ = db.QueryRow("select password from chat where id is not null and login = ?",
				msg_struct.Payload.Login).Scan(&check_user.Payload.Password)


			if msg_struct.Payload.Password == check_user.Payload.Password {

				//UPDATE `chat` SET `IP` = '0.0.0.0:1' WHERE `chat`.`login` = root
				insert ,err := db.Exec("update chat set IP=? where login=?",
					string(IP), string(msg_struct.Payload.Login))
				if err != nil {
					log.Fatal(err)
					s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)//"FAIL UPDATE IP"
					log.Print(string(answer_to_client_json))
					return
				}
				rowsAffected, err := insert.RowsAffected()
				if err != nil {
					log.Fatal(err)
					s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)//"FAIL UPDATE IP"
					log.Print(string(answer_to_client_json))
					return
				}

				log.Printf("Client %s created successfully (%d row affected)\n", addr, rowsAffected)
				msg_answer_FAIL.Answer = "OK"

				answer_to_client_json, err := json.Marshal(msg_answer_FAIL)
				if err != nil {
					fmt.Println(err)
					return
				}

				s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"OK"}"`)//"OK | " + check_user.Payload.IP
				log.Print(string(answer_to_client_json))


			} else {
				s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)//"FAIL WRONG PASSWORD"
				log.Print(string(answer_to_client_json))
				break
			}

		} else {
			s.messages <- string(answer_to_client_json)//string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)//"FAIL USER MUST BE REGISTRATION"
			log.Print(string(answer_to_client_json))
			break
		}




	case "user.add_friend":
		var check_null sql.NullString
		_ = db.QueryRow("select login from chat where id is not null and login = ?",
			msg_struct.Payload.MyLogin).Scan(&check_null)
		var check_user Answer_IP


		if check_null.Valid {

			_ = db.QueryRow("select IP from chat where id is not null and login = ?",
				msg_struct.Payload.FriendLogin).Scan(check_user.IP)


			check_user.Answer = "OK"
			check_user.ID = msg_struct.Payload.ID

			msg_answer_FAIL.Answer = "OK"

			//Использовать без IP тобишь {"id":"572e997d-7bfd-4a31-93f1-8256775c0fd1","answer":"OK"}
			//answer_to_client_json, err := json.Marshal(msg_answer_FAIL)

			//Использовать с IP тобишь {"id":"572e997d-7bfd-4a31-93f1-8256775c0fd1","answer":"OK","IP":"127.0.0.1:213"}
			answer_to_client_json, err := json.Marshal(check_user)
			if err != nil {
				fmt.Println(err)
				return
			}

			s.messages <- string(answer_to_client_json) //string(`"{"id":"`+ msg_struct.ID +`","answer":"OK","IP":"127.0.0.1:213"}"`)//"OK | " + check_user.Payload.IP
			log.Print(string(answer_to_client_json))

		} else {
			s.messages <- string(answer_to_client_json) //string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)//"FAIL USER MUST BE REGISTRATION"
			log.Print(string(answer_to_client_json))
			break
		}






	default:
		//s.messages <- "FAIL" + time.Now().Format("15:04:05")
		s.messages <- string(answer_to_client_json) //string(`"{"id":"`+ msg_struct.ID +`","answer":"FAIL"}"`)//"FAIL 666"
		log.Print(string(answer_to_client_json))
		break
	}
	//s.messages <- "server says hello at " + time.Now().Format("15:04:05")
}

func (s *Server) sendMessage() {
	for {
		msg := <-s.messages
		err := s.connection.SetWriteDeadline(time.Now().Add(1 * time.Second))
		if err != nil {
			log.Printf("Seems like this client %s is gone.\n", s.client)

		}
		_, err = s.connection.WriteTo([]byte(msg), s.client)
		errorCheck(err, "sendMessage", false)
	}
}

func main() {

	var s Server
	s.messages = make(chan string, 20)

	serverAddr, err := net.ResolveUDPAddr("udp", fmt.Sprintf(":%d", port))
	errorCheck(err, "main", true)

	s.connection, err = net.ListenUDP("udp", serverAddr)
	errorCheck(err, "main", true)

	defer s.connection.Close()

	log.Printf("Starting UDP Server, listening at %s", s.connection.LocalAddr())


	go s.sendMessage()

	for {
		s.handleMessage()
	}

}
