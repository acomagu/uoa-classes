package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
)

const names = "abcdefghijklm"

func main() {
	scn := newScanner(os.Stdin)

	n := scn.ScanInt()

	var nodes []*node
	for i := 0; i < n; i++ {
		var dtcs []int
		for j := 0; j < n; j++ {
			dtc := scn.ScanInt()

			if i == j {
				continue
			}

			dtcs = append(dtcs, dtc)
		}

		nodes = append(nodes, &node{
			dtcs: dtcs,
			name: names[i],
		})
	}
	for i, nd := range nodes {
		refs := make([]*node, i, n-1)
		copy(refs, nodes[:i])
		refs = append(refs, nodes[i+1:]...)

		nd.refs = refs


		fmt.Printf("refs for %c: ", nd.name)
		for _, ref := range refs {
			fmt.Printf("%c, ", ref.name)
		}
		fmt.Println()
	}

	fmt.Print("      ")
	for _, end := range nodes {
		fmt.Printf("     %c", end.name)
	}
	fmt.Println()
	for _, start := range nodes {
		fmt.Printf("     %c", start.name)

		for _, end := range nodes {
			fmt.Printf(" %5d", end.DistanceFrom(start))
		}

		fmt.Println()
	}
}

type node struct {
	dtcs []int   // distances from own to others.
	refs []*node // references to directly connected nodes.
	name byte  // for debug
}

func (n *node) DistanceFrom(m *node) int {
	if n == m {
		return 0
	}

	md := -1
	for i, connected := range n.refs {
		md = n.min(md, connected.DistanceFrom(m)+n.dtcs[i])
	}

	return md
}

func (*node) min(ns ...int) int {
	ans := -1
	for _, n := range ns {
		if n == -1 {
			continue
		}

		if ans == -1 || n < ans {
			ans = n
		}
	}

	if ans == -1 {
		panic("no valid numbers")
	}

	return ans
}

type scanner struct {
	s *bufio.Scanner
}

func newScanner(r io.Reader) *scanner {
	s := bufio.NewScanner(r)
	s.Split(bufio.ScanWords)
	return &scanner{
		s: s,
	}
}

func (s *scanner) ScanInt() int {
	if ok := s.s.Scan(); !ok {
		panic("could not scan")
	}

	n, err := strconv.Atoi(s.s.Text())
	if err != nil {
		panic(err)
	}

	return n
}
