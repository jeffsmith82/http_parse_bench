package main

import (
	"errors"
	"fmt"
	"strings"
	"time"
)

func main() {
	stringy := "HTTP/1.1 418 I'm a teapot\r\n"

	var version, code, description []byte

	start := time.Now()
	for i := 0; i < 100000000; i++ {
		version, code, description, _ = http_parse([]byte(stringy))
	}
	elapsed := time.Since(start)

	fmt.Println("time to run: ", elapsed)
	fmt.Println("Version: ", string(version))
	fmt.Println("code: ", string(code))
	fmt.Println("description:", string(description))

}

func http_parse(s []byte) ([]byte, []byte, []byte, error) {

	version := []byte{}
	code := []byte{}
	description := []byte{}

	version_pos := strings.IndexByte(string(s), ' ')
	if version_pos == -1 {
		return version, code, description, errors.New("invalid")
	}
	code_pos := strings.IndexByte(string(s[version_pos+1:]), ' ')
	if code_pos == -1 {
		return version, code, description, errors.New("invalid")
	}
	version = s[:version_pos]
	code = s[version_pos+1 : version_pos+1+code_pos]
	description = s[version_pos+1+code_pos+1:]

	return version, code, description, nil
}
