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
	println(version, code, description)

}

func http_parse(s string) (string, string, string) {

	result := strings.SplitN(s, " ", 3)
	if len(result) == 3 {
		return result[0], result[1], result[2]
	}
	return "", "", ""
}
