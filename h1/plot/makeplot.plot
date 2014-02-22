set terminal png


set output "res/plots/time.png"
set xlabel "log_2(#nodes)"
set ylabel "Time (us)"

plot    "res/inorder.BRANCH.bench.data"            using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'Inorder'          with errorlines, \
        "res/bfs.BRANCH.bench.data"                using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS'              with errorlines, \
        "res/dfs.BRANCH.bench.data"                using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS'              with errorlines, \
        "res/dfs_explicit.BRANCH.bench.data"       using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.BRANCH.bench.data"       using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):($3/$2):($4/$2):($5/$2) title 'vEB Explicit int' with errorlines




# set output "res/plots/branch_miss.png"
# set ylabel "branch mispredictions"
# 
# plot    "res/inorder.BRANCH.bench.data"            using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'Inorder'          with errorlines, \
#         "res/bfs.BRANCH.bench.data"                using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS'              with errorlines, \
#         "res/dfs.BRANCH.bench.data"                using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS'              with errorlines, \
#         "res/dfs_explicit.BRANCH.bench.data"       using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit'     with errorlines, \
#         "res/dfs_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit int' with errorlines, \
#         "res/bfs_explicit.BRANCH.bench.data"       using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit'     with errorlines, \
#         "res/bfs_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit int' with errorlines, \
#         "res/veb_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'vEB Explicit int' with errorlines
# 
# 
# set output "res/plots/branch_hitrate.png"
# set ylabel "branch hit %"
# 
# plot    "res/inorder.BRANCH.bench.data"            using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'Inorder'          with errorlines, \
#         "res/bfs.BRANCH.bench.data"                using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS'              with errorlines, \
#         "res/dfs.BRANCH.bench.data"                using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS'              with errorlines, \
#         "res/dfs_explicit.BRANCH.bench.data"       using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit'     with errorlines, \
#         "res/dfs_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit int' with errorlines, \
#         "res/bfs_explicit.BRANCH.bench.data"       using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit'     with errorlines, \
#         "res/bfs_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit int' with errorlines, \
#         "res/veb_explicit_int.BRANCH.bench.data"   using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'vEB Explicit int' with errorlines




set output "res/plots/BPU_miss.png"
set ylabel "branch mispredictions"

plot    "res/inorder.BPU.bench.data"               using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'Inorder'          with errorlines, \
        "res/bfs.BPU.bench.data"                   using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS'              with errorlines, \
        "res/dfs.BPU.bench.data"                   using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS'              with errorlines, \
        "res/dfs_explicit.BPU.bench.data"          using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.BPU.bench.data"      using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.BPU.bench.data"          using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.BPU.bench.data"      using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.BPU.bench.data"      using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'vEB Explicit int' with errorlines


set output "res/plots/BPU_hitrate.png"
set ylabel "Branch hit %"

plot    "res/inorder.BPU.bench.data"               using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'Inorder'          with errorlines, \
        "res/bfs.BPU.bench.data"                   using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS'              with errorlines, \
        "res/dfs.BPU.bench.data"                   using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS'              with errorlines, \
        "res/dfs_explicit.BPU.bench.data"          using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.BPU.bench.data"      using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.BPU.bench.data"          using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.BPU.bench.data"      using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.BPU.bench.data"      using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'vEB Explicit int' with errorlines




# set output "res/plots/cache_miss.png"
# set ylabel "cache faults"
# 
# plot    "res/inorder.HW_CACHE.bench.data"          using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'Inorder'          with errorlines, \
#         "res/bfs.HW_CACHE.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS'              with errorlines, \
#         "res/dfs.HW_CACHE.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS'              with errorlines, \
#         "res/dfs_explicit.HW_CACHE.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit'     with errorlines, \
#         "res/dfs_explicit_int.HW_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit int' with errorlines, \
#         "res/bfs_explicit.HW_CACHE.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit'     with errorlines, \
#         "res/bfs_explicit_int.HW_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit int' with errorlines, \
#         "res/veb_explicit_int.HW_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'vEB Explicit int' with errorlines
# 
# 
# set output "res/plots/cache_hitrate.png"
# set ylabel "Cache hit %"
# 
# plot    "res/inorder.HW_CACHE.bench.data"          using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'Inorder'          with errorlines, \
#         "res/bfs.HW_CACHE.bench.data"              using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS'              with errorlines, \
#         "res/dfs.HW_CACHE.bench.data"              using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS'              with errorlines, \
#         "res/dfs_explicit.HW_CACHE.bench.data"     using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit'     with errorlines, \
#         "res/dfs_explicit_int.HW_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit int' with errorlines, \
#         "res/bfs_explicit.HW_CACHE.bench.data"     using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit'     with errorlines, \
#         "res/bfs_explicit_int.HW_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit int' with errorlines, \
#         "res/veb_explicit_int.HW_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'vEB Explicit int' with errorlines




set output "res/plots/ll_cache_miss.png"
set ylabel "Last-level cache faults"

plot    "res/inorder.LL_CACHE.bench.data"          using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'Inorder'          with errorlines, \
        "res/bfs.LL_CACHE.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS'              with errorlines, \
        "res/dfs.LL_CACHE.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS'              with errorlines, \
        "res/dfs_explicit.LL_CACHE.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.LL_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.LL_CACHE.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.LL_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.LL_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'vEB Explicit int' with errorlines


set output "res/plots/ll_cache_hitrate.png"
set ylabel "Last-level cache hit %"

plot    "res/inorder.LL_CACHE.bench.data"          using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'Inorder'          with errorlines, \
        "res/bfs.LL_CACHE.bench.data"              using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS'              with errorlines, \
        "res/dfs.LL_CACHE.bench.data"              using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS'              with errorlines, \
        "res/dfs_explicit.LL_CACHE.bench.data"     using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.LL_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.LL_CACHE.bench.data"     using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.LL_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.LL_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'vEB Explicit int' with errorlines




set output "res/plots/l1_cache_miss.png"
set ylabel "Level-1 cache faults"

plot    "res/inorder.L1_CACHE.bench.data"          using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'Inorder'          with errorlines, \
        "res/bfs.L1_CACHE.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS'              with errorlines, \
        "res/dfs.L1_CACHE.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS'              with errorlines, \
        "res/dfs_explicit.L1_CACHE.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.L1_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.L1_CACHE.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.L1_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.L1_CACHE.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'vEB Explicit int' with errorlines


set output "res/plots/l1_cache_hitrate.png"
set ylabel "Level-1 cache hit %"

plot    "res/inorder.L1_CACHE.bench.data"          using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'Inorder'          with errorlines, \
        "res/bfs.L1_CACHE.bench.data"              using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS'              with errorlines, \
        "res/dfs.L1_CACHE.bench.data"              using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS'              with errorlines, \
        "res/dfs_explicit.L1_CACHE.bench.data"     using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.L1_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.L1_CACHE.bench.data"     using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.L1_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.L1_CACHE.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'vEB Explicit int' with errorlines




set output "res/plots/TLB_miss.png"
set ylabel "TLB miss"

plot    "res/inorder.DATA_TLB.bench.data"          using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'Inorder'          with errorlines, \
        "res/bfs.DATA_TLB.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS'              with errorlines, \
        "res/dfs.DATA_TLB.bench.data"              using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS'              with errorlines, \
        "res/dfs_explicit.DATA_TLB.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.DATA_TLB.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.DATA_TLB.bench.data"     using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.DATA_TLB.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.DATA_TLB.bench.data" using (log($1)/log(2)):($6/$2):($7/$2):($8/$2) title 'vEB Explicit int' with errorlines


set output "res/plots/TLB_hitrate.png"
set ylabel "TLB hit %"

plot    "res/inorder.DATA_TLB.bench.data"          using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'Inorder'          with errorlines, \
        "res/bfs.DATA_TLB.bench.data"              using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS'              with errorlines, \
        "res/dfs.DATA_TLB.bench.data"              using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS'              with errorlines, \
        "res/dfs_explicit.DATA_TLB.bench.data"     using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit'     with errorlines, \
        "res/dfs_explicit_int.DATA_TLB.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'DFS Explicit int' with errorlines, \
        "res/bfs_explicit.DATA_TLB.bench.data"     using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit'     with errorlines, \
        "res/bfs_explicit_int.DATA_TLB.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'BFS Explicit int' with errorlines, \
        "res/veb_explicit_int.DATA_TLB.bench.data" using (log($1)/log(2)):(100-$12):(100-$13):(100-$14) title 'vEB Explicit int' with errorlines
