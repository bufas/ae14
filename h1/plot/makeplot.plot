set terminal png

set output "res/pred_search_binary.png"
set xlabel "log_2(#nodes)"
set ylabel "Time (us)"

plot    "res/inorder.bench.data"          using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'Inorder'          with errorlines, \
        "res/bfs.bench.data"              using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS'              with errorlines, \
        "res/dfs.bench.data"              using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS'              with errorlines, \
        "res/dfs_explicit.bench.data"     using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.bench.data" using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.bench.data"     using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.bench.data" using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.bench.data" using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'vEB Explicit int' with errorlines


set output "res/branch_misses.png"
set xlabel "log_2(#nodes)"
set ylabel "misses"

plot    "res/inorder.bench.data"          using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'Inorder'          with errorlines, \
        "res/bfs.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS'              with errorlines, \
        "res/dfs.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS'              with errorlines, \
        "res/dfs_explicit.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'vEB Explicit int' with errorlines


set output "res/cache_misses.png"
set xlabel "log_2(#nodes)"
set ylabel "misses"

plot    "res/inorder.bench.data"          using (log($1)/log(2)):($9/$2):($10/$2):($11/$2) title 'Inorder'          with errorlines, \
        "res/bfs.bench.data"              using (log($1)/log(2)):($9/$2):($10/$2):($11/$2) title 'BFS'              with errorlines, \
        "res/dfs.bench.data"              using (log($1)/log(2)):($9/$2):($10/$2):($11/$2) title 'DFS'              with errorlines, \
        "res/dfs_explicit.bench.data"     using (log($1)/log(2)):($9/$2):($10/$2):($11/$2) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.bench.data" using (log($1)/log(2)):($9/$2):($10/$2):($11/$2) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.bench.data"     using (log($1)/log(2)):($9/$2):($10/$2):($11/$2) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.bench.data" using (log($1)/log(2)):($9/$2):($10/$2):($11/$2) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.bench.data" using (log($1)/log(2)):($9/$2):($10/$2):($11/$2) title 'vEB Explicit int' with errorlines

