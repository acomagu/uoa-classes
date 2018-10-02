package main

import "fmt"

func main() {
	var n int
	fmt.Scan(&n)
	v := make([]int, n)
	for i := range v {
		fmt.Scan(&v[i])
	}

	p, c := selectionSort(v)
	for i, e := range p {
		fmt.Print(e)
		if i < len(p)-1 {
			fmt.Print(" ")
		} else {
			fmt.Println()
		}
	}
	fmt.Println(c)
}

func selectionSort(v []int) ([]int, int) {
	if len(v) == 0 {
		return []int{}, 0
	}

	a, p, c := step(v, v[0])
	pp, cc := selectionSort(p[1:])
	return append([]int{a}, pp...), c + cc
}

func step(v []int, s int) (int, []int, int) {
	if len(v) == 0 {
		return s, v, 0
	}

	a, p, _ := step(v[1:], s)
	if v[0] > a {
		return a, append([]int{v[0]}, p...), 1
	}
	return v[0], append([]int{s}, v[1:]...), 0
}
