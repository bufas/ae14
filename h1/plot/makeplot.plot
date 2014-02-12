set terminal png

set xlabel "log_2(#nodes)"
set ylabel "Time (us)"


set output "pred_search_binary.png"
plot    "inorder.bench.data" using (log($1)/log(2)):($3/$2) title 'Inorder' with lines, \
        "bfs.bench.data"     using (log($1)/log(2)):($3/$2) title 'BFS'     with lines, \
        "dfs.bench.data"     using (log($1)/log(2)):($3/$2) title 'DFS'     with lines

set output "pred_search_binary2.png"
plot    "inorder.bench.data" using 1:($3/$2) title 'Inorder' with lines, \
        "bfs.bench.data"     using 1:($3/$2) title 'BFS'     with lines, \
        "dfs.bench.data"     using 1:($3/$2) title 'DFS'     with lines
