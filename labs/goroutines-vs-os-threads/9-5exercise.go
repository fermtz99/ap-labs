package main

import (
	"fmt"
	"time"
	"os"
	//"strconv"
	//"os/signal"
)

func main() {
	programChan := make(chan int)
	start := time.Now()
	i := 0
	go func() {
		programChan <- 1
		for {
			i++
			programChan <- <- programChan
		}
	}()
	go func() {
		for {
			programChan <- <- programChan
		}
	}()

	time.Sleep(2 * time.Second)
	file, err := os.OpenFile("9-5result.txt", os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0666)
	if err != nil {
		fmt.Println("File not opened")
	}
	s := fmt.Sprintf("%f", (float64(i)/float64(time.Since(start)) * 1e9))
	file.WriteString(s + "trips per second")
	file.Close()
	fmt.Println(float64(i)/float64(time.Since(start)) * 1e9, "trips per second")
}
