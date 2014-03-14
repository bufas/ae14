set terminal png

set xlabel "Skew %"
set ylabel "Time (us)"

set output "res1/plots/skew_1k.png"
plot    "res1/skew/dfs_explicit_int.1k.skew.bench.data"   using 1:($4/$3):($5/$3):($6/$3) title "1k nodes"   with errorlines
set output "res1/plots/skew_10k.png"
plot    "res1/skew/dfs_explicit_int.10k.skew.bench.data"  using 1:($4/$3):($5/$3):($6/$3) title "10k nodes"  with errorlines
set output "res1/plots/skew_100k.png"
plot    "res1/skew/dfs_explicit_int.100k.skew.bench.data" using 1:($4/$3):($5/$3):($6/$3) title "100k nodes" with errorlines
set output "res1/plots/skew_1m.png"
plot    "res1/skew/dfs_explicit_int.1m.skew.bench.data"   using 1:($4/$3):($5/$3):($6/$3) title "1m nodes"   with errorlines
set output "res1/plots/skew_10m.png"
plot    "res1/skew/dfs_explicit_int.10m.skew.bench.data"  using 1:($4/$3):($5/$3):($6/$3) title "10m nodes"  with errorlines


set ylabel "Time"
set format y ''

set output "res1/plots/skew.png"
plot    "res1/skew/dfs_explicit_int.1k.skew.bench.data"   using 1:($4/3919):($5/3919):($6/3919) title "1k nodes"   with errorlines, \
        "res1/skew/dfs_explicit_int.10k.skew.bench.data"  using 1:($4/6687):($5/6687):($6/6687) title "10k nodes"  with errorlines, \
        "res1/skew/dfs_explicit_int.100k.skew.bench.data" using 1:($4/9327):($5/9327):($6/9327) title "100k nodes" with errorlines, \
        "res1/skew/dfs_explicit_int.1m.skew.bench.data"   using 1:($4/28394):($5/28394):($6/28394) title "1m nodes"   with errorlines, \
        "res1/skew/dfs_explicit_int.10m.skew.bench.data"  using 1:($4/47620):($5/47620):($6/47620) title "10m nodes"  with errorlines


