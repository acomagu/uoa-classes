package main

import (
	"fmt"
	"math"
)

func main() {
	var n int
	fmt.Scan(&n)
	a := make([]int, n)

	for i := range a {
		fmt.Scan(&a[i])
	}

	var c int
	for _, e := range a {
		if isPrime(e) {
			c++
		}
	}

	fmt.Println(c)
}

func isPrime(n int) bool {
	for i := 2; i <= int(math.Sqrt(float64(n))); i++ {
		if n % i == 0 {
			return false
		}
	}

	return true
}
