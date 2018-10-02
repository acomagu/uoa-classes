package main

import "fmt"

func main() {
	a := []int{15, 13, 9, 5, 12, 8, 7, 4, 0, 6, 2, 1}
	fmt.Println(a)
	maxHeapInsert(&a, 10)
	fmt.Println(a)
}

func maxHeapInsert(a *[]int, v int) {
	*a = append(*a, v)
	for i := len(*a) - 1; i > 0 && (*a)[p(i)] < (*a)[i]; i = p(i) {
		swap(*a, i, p(i))
	}
}

func heapExtractMax(a *[]int) int {
	m := (*a)[0]
	(*a)[0] = (*a)[len(*a)-1]
	*a = (*a)[:len(*a)-1]
	maxHeapify(*a, 0)
	return m
}

func buildMaxHeap(a []int) {
	for i := len(a) - 1; i >= 0; i-- {
		maxHeapify(a, i)
	}
}

func maxHeapify(a []int, i int) {
	l, r := c(i)
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

func p(i int) int {
	return (i+1)/2 - 1
}

func c(i int) (int, int) {
	return (i+1)*2 - 1, (i + 1) * 2
}
