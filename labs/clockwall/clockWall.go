// Fernando Martinez
// A01630401

package main

import (
	"fmt"
	"io"
	"os"
	"strings"
	"sync"
	"net"
)

func main() {
	if len(os.Args) >= 2 {
		var waitGroup sync.WaitGroup
		for i := 1; i < len(os.Args); i++ {
			substrings := strings.Split(os.Args[i], "=")
			server := substrings[1]
			conn, err := net.Dial("tcp", server)
			if err != nil {
				fmt.Println(err)
			}
			waitGroup.Add(1)
			go mustCopy(conn, &waitGroup)
		}
		waitGroup.Wait()
	} else {
		fmt.Println("Usage: ./clockWall 'city'='server':'port'")
	}
}

func mustCopy(conn net.Conn, waitGroup *sync.WaitGroup) {
	defer waitGroup.Done()
	for {
		_, err := io.Copy(os.Stdout, conn)
		if err == nil {
			break
		}
	}
	fmt.Println("Connection lost")
}
