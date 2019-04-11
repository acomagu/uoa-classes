package main

import "fmt"

func main() {
	A := []int{5, 3, 12, 7, 23, 1, 23, 43, 54, 31}
	N := 10

	// At Here in the assembly, calcurate the address of the last element of A.

	i := 0
	for {
		i++

		if i == N {
			break
		}

		j := N
		for {
			if j == i {
				break
			}

			j--

			if A[j] < A[j-1] {
				A[j], A[j-1] = A[j-1], A[j]
			}
		}
	}
	fmt.Println(A)
}
