package main

import "fmt"

func main() {
	a := []int{5, 3, 17, 10, 84, 19, 6, 22, 9}
	fmt.Println(a)
	buildMaxHeap(a)
	fmt.Println(a)
}

func buildMaxHeap(a []int) {
	for i := len(a) - 1; i >= 0; i-- {
		maxHeapify(a, i)
	}
}

func maxHeapify(a []int, i int) {
	l := (i+1)*2 - 1
	r := l + 1
	largesti := maxi(a, l, r, i)
	fmt.Println(l, r, i, largesti)
	if largesti != i {
		swap(a, i, largesti)
		maxHeapify(a, largesti)
	}
}

func swap(a []int, x, y int) {
	tmp := a[x]
	a[x] = a[y]
	a[y] = tmp
}

func maxi(a []int, is ...int) int {
	var m int
	mi := -1
	for _, i := range is {
		if i >= 0 && i < len(a) && m < a[i] {
			m = a[i]
			mi = i
		}
	}

	return mi
}
