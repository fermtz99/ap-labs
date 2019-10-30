// Fernando Martinez
// A01630401

// Clock2 is a concurrent TCP server that periodically writes the time.
package main

import (
	"io"
	"log"
	"net"
	"time"
	"os"
	"fmt"
)

func handleConn(c net.Conn) {
	defer c.Close()
	tZone := os.Getenv("TZ")
	location, err := time.LoadLocation(tZone)
	if err != nil {
		fmt.Println(err)
	}
	for {
		_, err := io.WriteString(c, tZone + " : " + time.Now().In(location).Format("15:04:05\n"))
		if err != nil {
			return // e.g., client disconnected
		}
		time.Sleep(1 * time.Second)
	}
}

func main() {
	if len(os.Args) >= 2 {
		port := os.Args[2]
		host := "localhost:" + port

		listener, err := net.Listen("tcp", host)
		if err != nil {
			log.Fatal(err)
		}
		for {
			conn, err := listener.Accept()
			if err != nil {
				log.Print(err) // e.g., connection aborted
				continue
			}
			go handleConn(conn) // handle connections concurrently
		}
	} else {
		fmt.Println("Usage: TZ='timezone' ./clock2  -port 'port'")
	}
}
