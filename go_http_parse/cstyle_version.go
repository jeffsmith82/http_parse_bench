package main

import (
	"fmt"
	"strings"
	"time"
)

func main() {
	stringy := "HTTP/1.1 418 I'm a teapot\r\n"

	var version, code, description string

	start := time.Now()
	for i := 0; i < 100000000; i++ {
		version, code, description = http_parse(stringy)
	}
	elapsed := time.Since(start)

	fmt.Println("time to run: ", elapsed)
	fmt.Println(version, code, description)

}

func http_parse(s string) ([]byte, []byte, []byte) {


	int length = len(s)
	int version := []byte
	int code := []byte
	int description := []byte
	int count := 0

	for k,i := range s {
		if i == ' ' {
			if count == 0 {
				version = 
				count++
			} else if count ==1 {
				count++
			}

		}

	}
	return verion,code,description
}
