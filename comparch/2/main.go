package main

import "fmt"

func main() {
	md := 23
	mr := 112

	ans := 0
	mask := 1
	for {
		if mr&mask > 0 {
			ans += md
		}
		mask <<= 1
		md <<= 1
		if mask == 0 {
			break
		}
	}
	fmt.Println(ans)
}
