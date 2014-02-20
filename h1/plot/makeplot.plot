set terminal png

set output "pred_search_binary.png"
set xlabel "log_2(#nodes)"
set ylabel "Time (us)"

plot    "inorder.bench.data"          using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'Inorder'          with errorlines, \
        "bfs.bench.data"              using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS'              with errorlines, \
        "dfs.bench.data"              using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS'              with errorlines, \
        "dfs_explicit.bench.data"     using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS Explicit'     with errorlines, \
        "dfs_explicit_int.bench.data" using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS Explicit int' with errorlines, \
        "bfs_explicit.bench.data"     using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS Explicit'     with errorlines, \
        "bfs_explicit_int.bench.data" using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS Explicit int' with errorlines, \
        "veb_explicit_int.bench.data" using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'vEB Explicit int' with errorlines
