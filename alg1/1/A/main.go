package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	a := make([]int, n)

	pas := make([]interface{}, n)
	for i := range a {
		pas[i] = &a[i]
	}
	fmt.Scan(pas...)

	for i, e := range a {
		fmt.Print(e)
		if i != n-1 {
			fmt.Print(" ")
		} else {
			fmt.Println()
		}
	}

	for i := 1; i < n; i++ {
		v := a[i]
		j := i - 1
		for j >= 0 && a[j] > v {
			a[j+1] = a[j]
			j--
		}
		a[j+1] = v

		for i, e := range a {
			fmt.Print(e)
			if i != n-1 {
				fmt.Print(" ")
			} else {
				fmt.Println()
			}
		}
	}
}
