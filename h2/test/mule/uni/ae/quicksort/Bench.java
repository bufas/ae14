package mule.uni.ae.quicksort;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Random;

public class Bench {
    private static int N;
    private static int N_MIN;
    private static int N_MAX;

    private static boolean TO_FILE;
    private static boolean VERBOSE;

    private static int[] a;

    /**
     * Algorithms for the benchmark
     */
    private static Algorithm[] algorithms = {
//        new Algorithm() { public void sortArray(int[] a) { InsertionSort.sort(a); }},
//        new Algorithm() { public void sortArray(int[] a) { QuickSort.sort(a); }},
//        new Algorithm() { public void sortArray(int[] a) { QuickSortDual.sort(a); }},
        new Algorithm() { public void sortArray(int[] a) { java.util.Arrays.sort(a); }},
        new Algorithm() { public void sortArray(int[] a) { QuickSortYaroslavskiy.sort(a); }},
        new Algorithm() { public void sortArray(int[] a) { QuickSortYaroslavskiyOpt.sort(a); }},
        new Algorithm() { public void sortArray(int[] a) { QuickSortYaroslavskiyOpt13.sort(a); }},
    };

    /**
     * Different types of array input
     */
    private static Iteration[] iterations = {
        new Iteration() { public void pop() { stagger(1);   } public String name() { return "stagger_1"; }},
        new Iteration() { public void pop() { stagger(2);   } public String name() { return "stagger_2"; }},
        new Iteration() { public void pop() { stagger(4);   } public String name() { return "stagger_4"; }},
        new Iteration() { public void pop() { stagger(8);   } public String name() { return "stagger_8"; }},

        new Iteration() { public void pop() { random();     } public String name() { return "random"; }},
        new Iteration() { public void pop() { organPipes(); } public String name() { return "organ_pipes"; }},
        new Iteration() { public void pop() { ascend();     } public String name() { return "ascend"; }},
        new Iteration() { public void pop() { descend();    } public String name() { return "descend"; }},
        new Iteration() { public void pop() { same();       } public String name() { return "same"; }},

        new Iteration() { public void pop() { period(2);    } public String name() { return "period_1-2"; }},
        new Iteration() { public void pop() { period(3);    } public String name() { return "period_1-3"; }},
        new Iteration() { public void pop() { period(4);    } public String name() { return "period_1-4"; }},
        new Iteration() { public void pop() { period(5);    } public String name() { return "period_1-5"; }},
        new Iteration() { public void pop() { period(6);    } public String name() { return "period_1-6"; }},
        new Iteration() { public void pop() { period(7);    } public String name() { return "period_1-7"; }},
        new Iteration() { public void pop() { period(8);    } public String name() { return "period_1-8"; }},

        new Iteration() { public void pop() { stagger(3);   } public String name() { return "stagger_3"; }},
        new Iteration() { public void pop() { stagger(5);   } public String name() { return "stagger_5"; }},
        new Iteration() { public void pop() { stagger(6);   } public String name() { return "stagger_6"; }},
        new Iteration() { public void pop() { stagger(7);   } public String name() { return "stagger_7"; }},

        new Iteration() { public void pop() { random(2);    } public String name() { return "random_1-2"; }},
        new Iteration() { public void pop() { random(3);    } public String name() { return "random_1-3"; }},
        new Iteration() { public void pop() { random(4);    } public String name() { return "random_1-4"; }},
    };

    /**
     * The program runs a battery of tests, which consists of the cross
     * product between the sorting algorithms and the test iteration types
     * as well as the various array sizes, i.e. each algorithm is tested
     * with each iteration type and each array size.
     * <p>
     * A warmup phase will ensure that all algorithms have been processed
     * by the JIT compiler before the actual benchmark to avoid inconsistent
     * results.
     * <p>
     * The program offers limited configuration at launch-time, where the
     * minimum and maximum array sizes can be specified as factors of 10,
     * as well as whether or not the results should be exported to files,
     * and whether or not to use verbose output.
     *
     * @param args an array of program arguments
     * <ul>
     *     <li><b>-min #</b><br/> minimum array size (def: 10)</li>
     *     <li><b>-max #</b><br/> maximum array size (def: 10e6)</li>
     *     <li><b>-f</b><br/> enable file output (def: not set)</li>
     *     <li><b>-v</b><br/> enable verbose (def: not set)</li>
     * </ul>
     */
    public static void main(String[] args) {
        N_MIN   = get(args, "-min", 10);
        N_MAX   = get(args, "-max", 10000000);
        TO_FILE = get(args, "-f", true);
        VERBOSE = get(args, "-v", true);

        warmUp();
        doIterations();
    }



    //-------------------------------------------------------------------------
    //
    //      Benchmark methods
    //      - warmUp
    //      - doIteration
    //      - doSort
    //
    //-------------------------------------------------------------------------

    /**
     * In the warmup phase, all algorithms sort an array 12,000 times. The
     * array is size 12,000 and is randomly populated at the beginning of
     * the phase, and cloned before each sort. The purpose of the warmup
     * is to force the JIT compiler to get its work done before the actual
     * benchmark to avoid inconsistent results.
     */
    private static void warmUp() {
        info("Warming up");
        int tmp = N;
        N = 12000;

        a = new int[N];
        random();

        int[] test;
        for (int i = 0; i < N; i++) {
            for (Algorithm algorithm : algorithms) {
                test = a.clone();
                algorithm.sortArray(test);
            }
            if (i % 1200 == 0) info(".");
        }
        N = tmp;
        info(" Done! %n");
    }

    /**
     * Each iteration is run with each array size between the minimum and
     * maximum sizes, the sizes increasing by a factor of 10 every time.
     * Each algorithm is then used to sort the given array.
     */
    private static void doIterations() {
        for (Iteration iteration : iterations) {
            info("=== %s %n", iteration.name());

            // Store stdout
            PrintStream out = System.out;
            setOutput(iteration.name());

            for (int n = N_MIN; n <= N_MAX; n *= 10) {
                N = n;
                pad("%d \t", N);
                a = new int[N];
                iteration.pop();
                for (Algorithm algorithm : algorithms) {
                    doSort(algorithm, N);
                }
                out("%n");

//                N = n * 2;
//                pad("%d \t", N);
//                a = new int[N];
//                iteration.pop();
//                for (Algorithm algorithm : algorithms) {
//                    doSort(algorithm, N);
//                }
//                out("%n");

                N = n * 3;
                pad("%d \t", N);
                a = new int[N];
                iteration.pop();
                for (Algorithm algorithm : algorithms) {
                    doSort(algorithm, N);
                }
                out("%n");

//                N = n * 6;
//                pad("%d \t", N);
//                a = new int[N];
//                iteration.pop();
//                for (Algorithm algorithm : algorithms) {
//                    doSort(algorithm, N);
//                }
//                out("%n");
            }
//            for (N = N_MIN; N <= N_MAX; N *= 10) {
//                pad("%d \t", N);
//                a = new int[N];
//                iteration.pop();
//                for (Algorithm algorithm : algorithms) {
//                    doSort(algorithm, N);
//                }
//                out("%n");
//            }

            // Restore stdout
            System.setOut(out);
        }
    }

    /**
     * Given an algorithm and an array size, the algorithm sorts the given
     * array (MAX / N) number of times, where MAX is the maximum array size
     * and N is the given array size. This ensures that small array sizes
     * are tested various times and averaged properly, but also that large
     * sizes will not take forever to complete.
     *
     * @param sortable an algorithm
     * @param N an array size
     */
    private static void doSort(Algorithm sortable, int N) {
        long start, end;
        long total = 0l;
        int[] test = null;

        for (int i = 0; i < (N_MAX / N) * 10; i++) {
            test = a.clone();

            start = System.nanoTime();
            sortable.sortArray(test);
            end   = System.nanoTime();

            total += (end - start);
        }
//        verify(test);

        out("%d\t", total / 1000000l);
    }



    //-------------------------------------------------------------------------
    //
    //      Array population methods
    //      - random (capped and uncapped)
    //      - ascend
    //      - descend
    //      - same
    //      - stagger
    //      - period
    //
    //-------------------------------------------------------------------------

    /**
     * Random elements. This method is primarily useful for the warmup phase.
     */
    private static void random() {
        Random random = new Random();
        for (int i = 0; i < N; i++) {
            a[i] = random.nextInt();
        }
    }

    /**
     * Random elements in [0..m).
     *
     * @param m the maximum element value
     */
    private static void random(int m) {
        Random random = new Random();
        for (int i = 0; i < N; i++) {
            a[i] = random.nextInt(m);
        }
    }

    /**
     * Values equal to indices - sorted.
     */
    private static void ascend() {
        for (int i = 0; i < N; i++) {
            a[i] = i;
        }
    }

    /**
     * Values equal to (MAX - index) - reverse sorted.
     */
    private static void descend() {
        for (int i = 0; i < N; i++) {
            a[i] = N_MAX - i;
        }
    }

    /**
     * All values are identical.
     */
    private static void same() {
        for (int i = 0; i < N; i++) {
            a[i] = 0;
        }
    }

    /**
     * Sawblade - somewhat similar to ascend, but with several periods of
     * magnitude defined by m
     *
     * @param m period length
     */
    private static void period(int m) {
        for (int i = 0; i < N; i++) {
            a[i] = i % m;
        }
    }

    /**
     * Sawblade - similar to period, but with a steepness depending on m,
     * and the array size as the magnitude
     *
     * @param m steepness factor; greater is steeper
     */
    private static void stagger(int m) {
        for (int i = 0; i < N; i++) {
            a[i] = (i*m + i) % N;
        }
    }

    /**
     * Combination of ascend and descend, in the shape of organ pipes.
     */
    private static void organPipes() {
        int middle = N / 2;
        for (int i = 0; i < middle; i++) {
            a[i] = i;
        }
        for (int i = middle; i < N ; i++) {
            a[i] = N - i - 1;
        }
    }



    //-------------------------------------------------------------------------
    //
    //      Utilities
    //      - Algorithm interface
    //      - Iteration interface
    //      - Verification of sorted arrays
    //      - command-line argument parsers
    //      - logging and output
    //
    //-------------------------------------------------------------------------

    interface Algorithm {
        void sortArray(int[] a);
    }

    interface Iteration {
        void pop();
        String name();
    }

    private static void verify(int[] a) {
        for (int i = 0; i < a.length - 1; i++) {
            if (a[i] > a[i+1]) {
                throw new IllegalArgumentException("Array is not sorted!   expected " + a[i] + " <= " + a[i+1]);
            }
        }
    }

    private static int get(String[] args, String flag, int def) {
        for (int i = 0; i < args.length - 1; i++) {
            if (args[i].equals(flag)) {
                return Integer.parseInt(args[i+1]);
            }
        }
        return def;
    }

    private static boolean get(String[] args, String flag, boolean def) {
        for (String arg : args) {
            if (arg.equals(flag)) {
                return true;
            }
        }
        return def;
    }

    private static void info(String s, Object... args) {
        if (VERBOSE) out(s, args);
    }

    private static void out(String s, Object... args) {
        System.out.format(s, args);
    }

    private static void pad(String s, int N) {
        String indent = "";
        for (int tmp = N; tmp < N_MAX; tmp *= 10) {
            indent += " ";
        }
        out(indent + s, N);
    }

    private static void setOutput(String name) {
        if (TO_FILE) {
            try {
                File plot = new File("plot");
                File data = new File(plot, "data");
                File file = new File(data, name + ".data");

                if (!plot.exists()) plot.mkdir();
                if (!data.exists()) data.mkdir();

                if (file.exists()) file.delete();

                System.setOut(new PrintStream(new FileOutputStream(file)));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
