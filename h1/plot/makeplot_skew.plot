set terminal png


set output "pred_search_binary_skew.png"
set xlabel "skew(percent)"
set ylabel "Time (us)"

plot    "dfs_explicit_int.skew.bench.data" using 1:($4/$3) title 'DFS Explicit int' with lines
