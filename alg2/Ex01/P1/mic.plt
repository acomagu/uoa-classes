set xlabel "N"
set ylabel "elasped time(ms)"

set term png

set output "selection.png"
plot "plotsource" using 1:2 title "Selection Sort"

set output "merge.png"
plot "plotsource" using 1:3 title "Merge Sort"
