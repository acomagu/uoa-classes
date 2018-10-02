package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)

	s := make([]int, n)
	for i := range s {
		fmt.Scan(&s[i])
	}

	cnt := bubble_sort(s)
	for i, e := range s {
		fmt.Print(e)
		if i < n-1 {
			fmt.Print(" ")
		} else {
			fmt.Println()
		}
	}
	fmt.Println(cnt)
}

func bubble_sort(s []int) int {
	if cnt := step(s); cnt > 0 {
		return cnt + bubble_sort(s)
	}
	return 0
}

func step(s []int) int {
	if len(s) < 2 {
		return 0
	}

	var cnt int
	s[0], s[1], cnt = swap(s[0], s[1])
	return cnt + step(s[1:])
}

func swap(a, b int) (int, int, int) {
	if a > b {
		return b, a, 1
	}
	return a, b, 0
}
