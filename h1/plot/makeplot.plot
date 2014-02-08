set terminal png

set xlabel "log_2(#nodes)"
set ylabel "Time (us)"


set output "pred_search_binary.png"
plot    "inorder.bench.data" using 1:($4/$3) title 'Inorder' with lines, \
        "bfs.bench.data"     using 1:($4/$3) title 'BFS'     with lines, \
        "dfs.bench.data"     using 1:($4/$3) title 'DFS'     with lines
