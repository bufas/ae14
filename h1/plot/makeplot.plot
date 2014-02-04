set terminal png

set xlabel "# of nodes"
set ylabel "Time (us)"

set output "pred_search_binary.png"
plot    "inorder.bench.data" using 1:($3/1000) title 'Inorder' with lines, \
        "bfs.bench.data"     using 1:($3/1000) title 'BFS'     with lines
