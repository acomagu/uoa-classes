set xlabel "N"
set ylabel "elapsed time(ms)"

set term png

set output "up_down.png"
plot "plotsource" using 1:2 title "up-heap", \
     "plotsource" using 1:3 title "down-heap"

set output "heapsort.png"
plot "plotsource" using 1:4 title "heap sort"
