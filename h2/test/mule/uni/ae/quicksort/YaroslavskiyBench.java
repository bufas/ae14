package mule.uni.ae.quicksort;

import java.util.Random;

public class YaroslavskiyBench {
    public static void main(String[] args) {
//        warmUp();
        gold = new int[MAX_N];

        stagger(1);    doIteration("  stagger 1");
        stagger(2);    doIteration("  stagger 2");
        stagger(4);    doIteration("  stagger 4");
        stagger(8);    doIteration("  stagger 8");

        random();      doIteration("     random");
        organPipes();  doIteration("organ pipes");
        ascendant();   doIteration("  ascendant");
        descendant();  doIteration(" descendant");
        equal();       doIteration("      equal");

        period(2);     doIteration("period 1..2");
        period(3);     doIteration("period 1..3");
        period(4);     doIteration("period 1..4");
        period(5);     doIteration("period 1..5");
        period(6);     doIteration("period 1..6");
        period(7);     doIteration("period 1..7");
        period(8);     doIteration("period 1..8");

        stagger(3);    doIteration("  stagger 3");
        stagger(5);    doIteration("  stagger 5");
        stagger(6);    doIteration("  stagger 6");
        stagger(7);    doIteration("  stagger 7");

        random(2);     doIteration("random 1..2");
        random(3);     doIteration("random 1..3");
        random(4);     doIteration("random 1..4");
    }

    private static void warmUp() {
        out("start warm up");
        MAX_N = 12000;
        int[] test;

        gold = new int[MAX_N];
        random();
        System.out.print(".");

        for (int i = 0; i < 12000; i++) {
//            test = gold.clone(); InsertionSort.sort(test);
//            test = gold.clone(); java.util.Arrays.sort(test);
//            test = gold.clone(); QuickSort.sort(test);
//            test = gold.clone(); QuickSortMedian3.sort(test);
//            test = gold.clone(); QuickSortVogella.sort(test);
//            test = gold.clone(); QuickSortDual.sort(test);
            test = gold.clone(); QuickSortYaroslavskiy.sort(test);
            test = gold.clone(); QuickSortYaroslavskiyOpt.sort(test);
            test = gold.clone(); QuickSortYaroslavskiyOpt13.sort(test);

            if ((i+1) % 1000 == 0) System.out.print(".");
        }
        out();
        out("  end warm up");
        MAX_N = N;
    }

    private static void doIteration(String name) {
        out();
        out(name + " =======");

//        doSort("          InsertionSort", new Sortable() { public void sortArray(int[] a) { InsertionSort.sort(a); }});
//        doSort("                   JDK7", new Sortable() { public void sortArray(int[] a) { java.util.Arrays.sort(a); }});
//        doSort("               CLRS ref", new Sortable() { public void sortArray(int[] a) { QuickSort.sort(a); }});
//        doSort("            Median of 3", new Sortable() { public void sortArray(int[] a) { QuickSortMedian3.sort(a); }});
//        doSort("                Vogella", new Sortable() { public void sortArray(int[] a) { QuickSortVogella.sort(a); }});
//        doSort("       Dual-pivot (2,4)", new Sortable() { public void sortArray(int[] a) { QuickSortDual.sort(a); }});
        doSort("     Yaroslavskiy (2,4)", new Sortable() { public void sortArray(int[] a) { QuickSortYaroslavskiy.sort(a); }});
        doSort("Yaroslavskiy Opt. (2,4)", new Sortable() { public void sortArray(int[] a) { QuickSortYaroslavskiyOpt.sort(a); }});
        doSort("Yaroslavskiy Opt. (1,3)", new Sortable() { public void sortArray(int[] a) { QuickSortYaroslavskiyOpt13.sort(a); }});
    }

    private static void doSort(String name, Sortable sortable) {
//    outArr(gold);
        long startTime;
        long endTime;
        long minTime = Long.MAX_VALUE;
        long avgTime = 0L;
        int[] test = null;

        for (int i = 0; i < COUNT; i++) {
            test = gold.clone();

            startTime = System.nanoTime();
            sortable.sortArray(test);
            endTime = System.nanoTime();
            long time = endTime - startTime;

            minTime = Math.min(minTime, time);
            avgTime += time;
        }
//        outArr(test);
        check(test); /// !!!
//        checkExt(test); /// !!!

        out(name + ": " + minTime * COUNT / 1000000L + "  " + avgTime / 1000000L);
    }

    private static void random() {
        Random random = new Random();

        for (int i=0; i < MAX_N; i++) {
            gold[i] = random.nextInt();
        }
    }

    private static void ascendant() {
        for (int i=0; i < MAX_N; i++) {
            gold[i] = i;
        }
    }

    private static void descendant() {
        for (int i=0; i < MAX_N; i++) {
            gold[i] = MAX_N - i;
        }
    }

    private static void equal() {
        for (int i=0; i < MAX_N; i++) {
            gold[i] = 0;
        }
    }

    private static void stagger(int m) {
        for (int i=0; i < MAX_N; i++) {
            gold[i] = (i * m + i) % MAX_N;
        }
    }

    private static void period(int m) {
        for (int i=0; i < MAX_N; i++) {
            gold[i] = i % m;
        }
    }

    private static void random(int m) {
        Random random = new Random();

        for (int i=0; i < MAX_N; i++) {
            gold[i] = random.nextInt(m);
        }
    }

    private static void sawSequence() {
        int incCount = 1;
        int decCount = MAX_N;
        int i = 0;
        int period = 1;

        while (true) {
            for (int k=1; k < period; k++) {
                if (i >= MAX_N) {
                    return;
                }
                gold[i++] = incCount++;
            }
            period++;

            for (int k=1; k < period; k++) {
                if (i >= MAX_N) {
                    return;
                }
                gold[i++] = decCount--;
            }
            period++;
        }
    }

    private static void mixed() {
        int k = 0;

        for (int i = 0; i < MAX_N; i += 2) {
            gold[i] = k++;
        }
        for (int i = MAX_N - 1; i >= 0; i -= 2) {
            gold[i] = k--;
        }
    }

    private static void almostEqual() {
        equal();
        Random random = new Random();

        for (int k=1; k <= MAX_N/4; k++) {
            gold[random.nextInt(MAX_N)] = random.nextInt();
        }
    }

    private static void organPipes() {
        int middle = MAX_N / 2;

        for (int i=0; i < middle; i++) {
            gold[i] = i;
        }
        for (int i=middle; i < MAX_N ; i++) {
            gold[i] = MAX_N - i - 1;
        }
    }

    private static void check(int[] a) {
        for (int i=0; i < a.length - 1; i++) {
            if (a[i] > a[i+1]) {
                throw new IllegalArgumentException("!!! Array is not sorted at: " + i);
            }
        }
    }

    private static void checkExt(int[] a) {
        for (int i=0; i < a.length - 1; i++) {
            if (a[i] != i) {
                throw new IllegalArgumentException("!!!+1 Array is not sorted at: " + i + " " + a[i]);
            }
        }
    }

    private static void out() {
        System.out.println();
    }

    private static void out(Object object) {
        System.out.println(object);
    }

    private static void outArr(int[] a) {
        int length = 31;
        out();

        if (a.length < length) {
            length = a.length;
        }
        for (int i=0; i < length; i++) {
            System.out.print(" " + a[i]);
        }
        out();
        out();
    }

    interface Sortable {
        void sortArray(int[] a);
    }

//    private static final int N = 10000000;
//    private static final int COUNT =    9;

//    private static final int N =           10;
//    private static final int COUNT = 10000000;

//    private static final int N =         100;
//    private static final int COUNT = 1000000;

//    private static final int N = 1000000;
//    private static final int COUNT = 100;

//    private static final int N = 2000000;
//    private static final int COUNT =  50;


//    private static final int N =           10;
//    private static final int COUNT = 10000000;

//    private static final int N =          100;
//    private static final int COUNT =  1000000;

//    private static final int N =         1000;
//    private static final int COUNT =   100000;

//    private static final int N =        10000;
//    private static final int COUNT =    10000;

    private static final int N =       100000;
    private static final int COUNT =     1000;

//    private static final int N =      1000000;
//    private static final int COUNT =      100;

    private static int MAX_N = N;
    private static int[] gold;
}
