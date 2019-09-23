package main

import (
	"fmt"
	"os"
	"path/filepath"
)
// scanDir stands for the directory scanning implementation

func scanDir(dir string) error {
	directNum := 0
	linksNum := 0
	devicesNum := 0
	socketsNum := 0
	othersNum := 0

	file := func(path string, fileInfo os.FileInfo, e error) error {
		fType := string(os.FileMode.String(fileInfo.Mode())[0])
		if fType == "d" {
			directNum++
		} else if fType == "L" {
			linksNum++
		} else if fType == "D" {
			devicesNum++
		} else if fType == "S" {
			socketsNum++
		} else {
			othersNum++
		}
		return e
	}
	err := filepath.Walk(dir, file)
	if err != nil {
		fmt.Println(err)
		fmt.Println("Steps to run this program:")
		fmt.Println("1. Build: go build dir-scan.go")
		fmt.Println("2. Run: sudo ./dir-scan <directory>")
		os.Exit(1)
	}

	fmt.Println("Directory Scanner Tool")
	fmt.Println("+-------------------------+------+")
	fmt.Println("| Path                    |",dir,"|")
	fmt.Println("+-------------------------+------+")
	fmt.Println("| Directories             | ",directNum," |")
	fmt.Println("| Symbolic Links          | ",linksNum,"  |")
	fmt.Println("| Devices                 | ",devicesNum,"  |")
	fmt.Println("| Sockets                 | ",socketsNum,"  |")
	fmt.Println("| Other files             | ",othersNum,"  |")
	fmt.Println("+-------------------------+------+")
	return err
}

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
}
