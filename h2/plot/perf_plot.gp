set terminal png

set xlabel "log n"

#set xrange [100000:]
#set yrange [.1:]

#set logscale x
#set logscale y

#set xtics ('2' 1e2, '3' 1e3, '4' 1e4, '5' 1e5, '6' 1e6, '7' 1e7)
#unset ytics

set key left top autotitle columnheader

# u = using
# t = title
# w = with
# l = lines

set ytics
set ylabel "Branch miss %"
set output "perf_png/branch-miss-percentage.png"
plot "perf_data/branch-miss-percentage.data" \
   u (log($1)/log(2)):3  w linespoints ls 20 lw 2, \
'' u (log($1)/log(2)):4  w linespoints ls 23, \
'' u (log($1)/log(2)):5  w linespoints ls 21, \
'' u (log($1)/log(2)):6  w linespoints ls 7 pt 4, \
'' u (log($1)/log(2)):7  w linespoints ls 1 pt 2, \
'' u (log($1)/log(2)):8  w linespoints ls 2 pt 2, \
'' u (log($1)/log(2)):9  w linespoints ls 3 pt 2, \
'' u (log($1)/log(2)):10 w linespoints ls 32 lw 2,

set ytics 1
set ylabel "Cache miss %"
set output "perf_png/cache-miss-percentage.png"
plot "perf_data/cache-miss-percentage.data" \
   u (log($1)/log(2)):3  w linespoints ls 20 lw 2, \
'' u (log($1)/log(2)):4  w linespoints ls 23, \
'' u (log($1)/log(2)):5  w linespoints ls 21, \
'' u (log($1)/log(2)):6  w linespoints ls 7 pt 4, \
'' u (log($1)/log(2)):7  w linespoints ls 1 pt 2, \
'' u (log($1)/log(2)):8  w linespoints ls 2 pt 2, \
'' u (log($1)/log(2)):9  w linespoints ls 3 pt 2, \
'' u (log($1)/log(2)):10 w linespoints ls 32 lw 2,

# Log scale for non-percentage
set logscale y
unset ytics

set ylabel "Branches"
set output "perf_png/branches.png"
plot "perf_data/branches.data" \
   u (log($1)/log(2)):3  w linespoints ls 20 lw 2, \
'' u (log($1)/log(2)):4  w linespoints ls 23, \
'' u (log($1)/log(2)):5  w linespoints ls 21, \
'' u (log($1)/log(2)):6  w linespoints ls 7 pt 4, \
'' u (log($1)/log(2)):7  w linespoints ls 1 pt 2, \
'' u (log($1)/log(2)):8  w linespoints ls 2 pt 2, \
'' u (log($1)/log(2)):9  w linespoints ls 3 pt 2, \
'' u (log($1)/log(2)):10 w linespoints ls 32 lw 2,

set ylabel "Branch misses"
set output "perf_png/branch-misses.png"
plot "perf_data/branch-misses.data" \
   u (log($1)/log(2)):3  w linespoints ls 20 lw 2, \
'' u (log($1)/log(2)):4  w linespoints ls 23, \
'' u (log($1)/log(2)):5  w linespoints ls 21, \
'' u (log($1)/log(2)):6  w linespoints ls 7 pt 4, \
'' u (log($1)/log(2)):7  w linespoints ls 1 pt 2, \
'' u (log($1)/log(2)):8  w linespoints ls 2 pt 2, \
'' u (log($1)/log(2)):9  w linespoints ls 3 pt 2, \
'' u (log($1)/log(2)):10 w linespoints ls 32 lw 2,

set ylabel "Cache references"
set output "perf_png/cache-references.png"
plot "perf_data/cache-references.data" \
   u (log($1)/log(2)):3  w linespoints ls 20 lw 2, \
'' u (log($1)/log(2)):4  w linespoints ls 23, \
'' u (log($1)/log(2)):5  w linespoints ls 21, \
'' u (log($1)/log(2)):6  w linespoints ls 7 pt 4, \
'' u (log($1)/log(2)):7  w linespoints ls 1 pt 2, \
'' u (log($1)/log(2)):8  w linespoints ls 2 pt 2, \
'' u (log($1)/log(2)):9  w linespoints ls 3 pt 2, \
'' u (log($1)/log(2)):10 w linespoints ls 32 lw 2,

set ylabel "Cache misses"
set output "perf_png/cache-misses.png"
plot "perf_data/cache-misses.data" \
   u (log($1)/log(2)):3  w linespoints ls 20 lw 2, \
'' u (log($1)/log(2)):4  w linespoints ls 23, \
'' u (log($1)/log(2)):5  w linespoints ls 21, \
'' u (log($1)/log(2)):6  w linespoints ls 7 pt 4, \
'' u (log($1)/log(2)):7  w linespoints ls 1 pt 2, \
'' u (log($1)/log(2)):8  w linespoints ls 2 pt 2, \
'' u (log($1)/log(2)):9  w linespoints ls 3 pt 2, \
'' u (log($1)/log(2)):10 w linespoints ls 32 lw 2,
