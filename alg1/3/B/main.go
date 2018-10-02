package main

func main() {
	r := bufio.NewReader(os.Stdin)

	var n, q int
	fmt.Fscan(r, &n, &q)

	times := make(map[string]int)
	names := make([]string, n)
	for i := range names {
		fmt.Fscan(r, &names[i])
		fmt.Fscan(r, &times[names[i]])
	}


}

type f func() f

func step() {
}
