.INTERMEDIATE: xaa xab xac upheat downheat heapsort
plotsource: memo.md
	split memo.md -l8
	cat xac | awk '/[0-9].*/{print $$1" "$$6}' > heapsort
	cat xab | awk '/[0-9].*/{print $$1" "$$6}' > downheat
	cat xaa | awk '/[0-9].*/{print $$1" "$$6}' > upheat
	join upheat downheat | join - heapsort > plotsource
