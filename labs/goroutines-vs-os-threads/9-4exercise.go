package main

import (
	"fmt"
	"os"
	"time"
)

func main() {
	startTime := time.Now()
	// Number of goroutines to create
	i := 100000
	in, out := createPipe(i)
	in <- i
	<-out
	tNow := time.Now()
	elapsed := tNow.Sub(startTime)

	file, err := os.OpenFile("9-4result.txt", os.O_RDWR|os.O_CREATE|os.O_TRUNC, 0666)
        if err != nil {
                fmt.Println("File not opened")
        }
        s := fmt.Sprintf("%d created in %s time", i, elapsed)
        file.WriteString(s)
        file.Close()
}

func createPipe(n int) (chan<- int, <-chan int) {
	if n < 1 {
		return nil, nil
	}
	input := make(chan int)
	output := input
	for i := 0; i < n; i++ {
		prev := output
		next := make(chan int)

		go func() {
			for value := range prev {
				next <- value
			}
			close(next)
		}()
		output = next
	}
	return input, output
}
