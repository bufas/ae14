set terminal png


set output "pred_search_binary_skew.png"
set xlabel "skew(percent)"
set ylabel "Time (us)"

plot    "dfs_explicit_int.skew.bench.data" using 1:($4/$3) title 'DFS Explicit int' with lines


set output "pred_search_binary.png"
set xlabel "log_2(#nodes)"
set ylabel "Time (us)"

plot    "inorder.bench.data"          using (log($1)/log(2)):($3/$2) title 'Inorder'          with lines, \
        "bfs.bench.data"              using (log($1)/log(2)):($3/$2) title 'BFS'              with lines, \
        "dfs.bench.data"              using (log($1)/log(2)):($3/$2) title 'DFS'              with lines, \
        "dfs_explicit.bench.data"     using (log($1)/log(2)):($3/$2) title 'DFS Explicit'     with lines, \
        "dfs_explicit_int.bench.data" using (log($1)/log(2)):($3/$2) title 'DFS Explicit int' with lines, \
        "bfs_explicit.bench.data"     using (log($1)/log(2)):($3/$2) title 'BFS Explicit'     with lines, \
        "bfs_explicit_int.bench.data" using (log($1)/log(2)):($3/$2) title 'BFS Explicit int' with lines, \
        "veb_explicit_int.bench.data" using (log($1)/log(2)):($3/$2) title 'vEB Explicit int' with lines
