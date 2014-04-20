set terminal png

set xlabel "log n"
set ylabel "Comparisons / n"

#set xrange [100000:]
set yrange [5:]

set logscale y

# u = using
# t = title
# w = with
# l = lines
set key left top autotitle columnheader
plot datafile u (log($1)/log(2)):($2/$1) w linespoints ls 23, \
           '' u (log($1)/log(2)):($3/$1) w linespoints ls 21, \
           '' u (log($1)/log(2)):($4/$1) w linespoints ls 7 pt 4, \
           '' u (log($1)/log(2)):($5/$1) w linespoints ls 1 pt 2, \
           '' u (log($1)/log(2)):($6/$1) w linespoints ls 2 pt 2, \
           '' u (log($1)/log(2)):($7/$1) w linespoints ls 3 pt 2, \
           '' u (log($1)/log(2)):($8/$1) w linespoints ls 32 lw 2
#plot datafile u 1:2 w l, \
#           '' u 1:3 w l, \
#           '' u 1:4 w l, \
#           '' u 1:5 w l, \
#           '' u 1:6 w l, \
#           '' u 1:7 w l, \
#           '' u 1:8 w l
