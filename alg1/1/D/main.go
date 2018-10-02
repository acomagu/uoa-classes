package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	r := bufio.NewReader(os.Stdin)

	var n int
	fmt.Fscan(r, &n)

	dist := -9999999999
	min := 9999999999
	for i := 0; i < n; i++ {
		var e int
		fmt.Fscan(r, &e)

		if dist < e-min {
			dist = e - min
		}

		if min > e {
			min = e
		}
	}

	fmt.Println(dist)
}
