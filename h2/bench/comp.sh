#!/bin/bash
#printf 'x jdk7 classic classic_ite wild yaro yaro_opt yaro_opt_13\n'
printf 'x classic classic_ite wild yaro yaro_opt yaro_opt_13 triple\n'

#for n in 10 30 100 300 1000 3000 10000 30000 100000 300000 1000000 3000000 10000000; do
for n in 100 300 1000 3000 10000 30000 100000 300000 1000000 3000000 10000000; do
    printf "$n "
    for algo in 'classic' 'classic_ite' 'wild' 'yaro' 'yaro_opt' 'yaro_opt_13' 'triple'; do
    #for algo in 'jdk7' 'wild' 'yaro' 'yaro_opt' 'yaro_opt_13' 'triple'; do
    #for algo in 'triple'; do
        java -jar ../bench.jar -t -n $n -algo $algo -input ksorted32 -once -comp
    done
    printf "\n"
done


# for i in 10 30 100 300 1000 3000 10000 30000 100000 300000 1000000
# do
#   java -jar ../bench.jar -n $i -algo jdk7
#   java -jar ../bench.jar -n $i -algo classic
#   java -jar ../bench.jar -n $i -algo classic_ite
#   java -jar ../bench.jar -n $i -algo wild
#   java -jar ../bench.jar -n $i -algo yaro
#   java -jar ../bench.jar -n $i -algo yaro_opt
#   java -jar ../bench.jar -n $i -algo yaro_opt_13
# done
