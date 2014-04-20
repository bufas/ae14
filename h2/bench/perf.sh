for n in 100 300 1000 3000 10000 30000 100000 300000 1000000 3000000 10000000; do
    echo $n
    (perf stat -e cache-references,cache-misses,branches,branch-misses -x, -r 20 java -jar ../bench.jar -n $n -algo $algo -input random -pre > /dev/null)
    echo ""
    for algo in 'jdk7' 'classic' 'classic_ite' 'wild' 'yaro' 'yaro_opt' 'yaro_opt_13' 'triple'; do
        echo $algo
        (perf stat -e cache-references,cache-misses,branches,branch-misses -x, -r 20 java -jar ../bench.jar -n $n -algo $algo -input random -once > /dev/null)
        echo ""
    done
    echo ""
done
