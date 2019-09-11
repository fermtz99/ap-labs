package main

import (
	"golang.org/x/tour/wc"
	"strings"
)

func WordCount(s string) map[string]int {
	newMap := make(map[string]int)
	
	for _, i := range strings.Fields(s) {
		newMap[i] += 1
	}
	return newMap
}

func main() {
	wc.Test(WordCount)
}
