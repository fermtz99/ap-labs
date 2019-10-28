// Fernando Martinez
// A01630401

// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"fmt"
	"log"
	"net"
	"os"
	"strings"
	"time"
)


//!+broadcaster
type client chan<- string // an outgoing message channel

type clientInfo struct {
        username string
	ip string
        admin bool
	clientNum int
        clientChan client
}


var clientList []clientInfo

var usersConnected int = 0

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
)

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		i := 0
		for clies := range clients {
			clientList[i].clientChan = clies
			i++
		}
		select {
		case msg := <-messages:
			mString := strings.Split(msg, " ")
			user := mString[0]
			//fmt.Println(user)
			// Show all users
			if mString[2] == "/users" {
				msg = "irc-server > "
				for clie := 0; clie < usersConnected; clie++ {
					msg = msg + clientList[clie].username + ", "
				}
				for client := range clientList {
					if clientList[client].username == user {
						clientList[client].clientChan <- msg
					}
				}
			} else if mString[2] == "/msg" {
				otherUser := mString[3]
				msg = "Message from " + user + " > " + strings.Join(mString[4:], " ")
				for client := range clientList {
                                        if clientList[client].username == otherUser {
                                                clientList[client].clientChan <- msg
                                        }
                                }
			} else if mString[2] == "/time" {
				msg = "irc-server > " + time.Now().Format("01-02-2006 15:04:05")
				for client := range clientList {
                                        if clientList[client].username == user {
                                                clientList[client].clientChan <- msg
                                        }
                                }
			} else if mString[2] == "/user" {
				var found bool = false
				otherUser := mString[3]
				for client := range clientList {
                                        if clientList[client].username == otherUser {
                                                msg = "irc-server > Username: " + clientList[client].username + ", IP: " + clientList[client].ip
						found = true
                                        }
                                }
				if !found {
					msg = "User not found"
				}
				for client := range clientList {
                                        if clientList[client].username == user {
                                                clientList[client].clientChan <- msg
                                        }
                                }
			} else if mString[2] == "/kick" {
				otherUser := mString[3]
				for client := range clientList {
                                        if clientList[client].username == user {
						if clientList[client].admin {
							msg = "You kicked user [" + otherUser + "]"
							clientList[client].clientChan <- msg
							for otherClient := range clientList {
								if clientList[otherClient].username == otherUser {
									clientList[otherClient].clientChan <- "You were kicked"
									delete(clients, clientList[otherClient].clientChan)
									close(clientList[otherClient].clientChan)
								}
							}
							msg = "[" + otherUser + "] was kicked from the channel"
							for cli := range clients {
                                                		cli <- msg
							}
						}
                                        }
                                }
			} else {
                                for cli := range clients {
                                        cli <- msg
                                }
                        }


		case cli := <-entering:
			clients[cli] = true

		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	go clientWriter(conn, ch)

	input := bufio.NewScanner(conn)
	input.Scan()
	username := input.Text()

	// Info about the new user
	isAdmin := usersConnected == 0;
	newClient := clientInfo{username: username, ip: conn.RemoteAddr().String() ,admin: isAdmin, clientNum: usersConnected}
	clientList = append(clientList, newClient)
	usersConnected++

	//who := conn.RemoteAddr().String()
	ch <- "Your user [" + username + "] is successfully logged"
	if isAdmin {
		ch <- "Congrats, you were the first user."
		ch <- "You're the new IRC Server ADMIN"
	}
	messages <- "irc-server > New connected user [" + username + "]"
	//messages <- username + " has arrived"
	entering <- ch

	//input := bufio.NewScanner(conn)
	for input.Scan() {
		messages <- username + " > " + input.Text()
	}
	// NOTE: ignoring potential errors from input.Err()

	leaving <- ch
	messages <- "irc-server > [" + username + "]" + " has left"
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

//!+main
func main() {
	host := os.Args[2]
	port := os.Args[4]
	localhost := host + ":" + port
	fmt.Println("irc-server > Simple IRC Server started at " + localhost)
	listener, err := net.Listen("tcp", localhost)
	if err != nil {
		log.Fatal(err)
	}

	go broadcaster()
	fmt.Println("irc-server > Ready for receiving new clients")
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

//!-main
