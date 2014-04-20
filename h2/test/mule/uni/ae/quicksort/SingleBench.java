package mule.uni.ae.quicksort;

import static mule.uni.ae.quicksort.util.Populator.*;
import mule.uni.ae.quicksort.util.Args;

import bb.util.Benchmark;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.LinkedHashMap;
import java.util.Map;

public class SingleBench {
    private static final Map<String,Algorithm> algorithms = new LinkedHashMap<>();
    static {
        algorithms.put("jdk7",        new Algorithm() { public void sort(int[] a) { java.util.Arrays.sort(a); }});
        algorithms.put("classic",     new Algorithm() { public void sort(int[] a) { QuickSort.sort(a); }});
        algorithms.put("classic_ite", new Algorithm() { public void sort(int[] a) { QuickSortIte.sort(a); }});
        algorithms.put("wild",        new Algorithm() { public void sort(int[] a) { QuickSortDual.sort(a); }});
        algorithms.put("triple",      new Algorithm() { public void sort(int[] a) { QuickSortTriple.sort(a); }});
        algorithms.put("yaro",        new Algorithm() { public void sort(int[] a) { QuickSortYaroslavskiy.sort(a); }});
        algorithms.put("yaro_opt",    new Algorithm() { public void sort(int[] a) { QuickSortYaroslavskiyOpt.sort(a); }});
        algorithms.put("yaro_opt_13", new Algorithm() { public void sort(int[] a) { QuickSortYaroslavskiyOpt13.sort(a); }});
    }

    private static final Map<String,Input> inputs = new LinkedHashMap<>();
    static {
        inputs.put("ksorted2",   new Input() { public void fill(int[] a) { ksorted(a, 2); }});
        inputs.put("ksorted4",   new Input() { public void fill(int[] a) { ksorted(a, 4); }});
        inputs.put("ksorted8",   new Input() { public void fill(int[] a) { ksorted(a, 8); }});
        inputs.put("ksorted16",  new Input() { public void fill(int[] a) { ksorted(a, 16);}});
        inputs.put("ksorted32",  new Input() { public void fill(int[] a) { ksorted(a, 32);}});
        inputs.put("ksorted64",  new Input() { public void fill(int[] a) { ksorted(a, 64);}});

        inputs.put("stagger1",   new Input() { public void fill(int[] a) { stagger(a, 1); }});
        inputs.put("stagger2",   new Input() { public void fill(int[] a) { stagger(a, 2); }});
        inputs.put("stagger4",   new Input() { public void fill(int[] a) { stagger(a, 4); }});
        inputs.put("stagger8",   new Input() { public void fill(int[] a) { stagger(a, 8); }});

        inputs.put("random",     new Input() { public void fill(int[] a) { random(a);     }});
        inputs.put("organ_pipes",new Input() { public void fill(int[] a) { organPipes(a); }});
        inputs.put("ascend",     new Input() { public void fill(int[] a) { ascend(a);     }});
        inputs.put("descend",    new Input() { public void fill(int[] a) { descend(a);    }});
        inputs.put("same",       new Input() { public void fill(int[] a) { same(a);       }});

        inputs.put("period_1_2", new Input() { public void fill(int[] a) { period(a, 2);  }});
        inputs.put("period_1_3", new Input() { public void fill(int[] a) { period(a, 3);  }});
        inputs.put("period_1_4", new Input() { public void fill(int[] a) { period(a, 4);  }});
        inputs.put("period_1_5", new Input() { public void fill(int[] a) { period(a, 5);  }});
        inputs.put("period_1_6", new Input() { public void fill(int[] a) { period(a, 6);  }});
        inputs.put("period_1_7", new Input() { public void fill(int[] a) { period(a, 7);  }});
        inputs.put("period_1_8", new Input() { public void fill(int[] a) { period(a, 8);  }});

        inputs.put("stagger_3",  new Input() { public void fill(int[] a) { stagger(a, 3); }});
        inputs.put("stagger_5",  new Input() { public void fill(int[] a) { stagger(a, 5); }});
        inputs.put("stagger_6",  new Input() { public void fill(int[] a) { stagger(a, 6); }});
        inputs.put("stagger_7",  new Input() { public void fill(int[] a) { stagger(a, 7); }});

        inputs.put("random_1_2", new Input() { public void fill(int[] a) { random(a, 2);  }});
        inputs.put("random_1_3", new Input() { public void fill(int[] a) { random(a, 3);  }});
        inputs.put("random_1_4", new Input() { public void fill(int[] a) { random(a, 4);  }});
    }

    public static void main(String[] args) {
        Args argz = new Args(args);

        // Help flag, do nothing
        for (String flag : new String[] {"?", "help", "-help", "--help"}) {
            if (argz.get(flag, false)) {
                showHelp();
                return;
            }
        }

        // Grab array size, input type, and algorithm
        final int n = argz.get("-n", 100000);
        final Input input = inputs.get(argz.get("-input", "random"));
        final Algorithm algo = algorithms.get(argz.get("-algo", "yaro"));
        final boolean verbose = !argz.get("-t", false);
        final boolean pre = argz.get("-pre", false);
        final boolean once = argz.get("-once", false);
        final boolean comp = argz.get("-comp", false);

        // Report
        if (verbose) {
            System.out.println("size: " + n + ", algo: " + argz.get("-algo", "yaro") + ", input: " + argz.get("-input", "random"));
        }

        // Initialize and fill the array
        final int[] a = new int[n];
        input.fill(a);

        if (pre) {
            // Preliminary stuff for perf stat
            long sum = sum(a);
            System.out.println("Hi " + sum);
            return;
        }


        if (once) {
            // Running once for perf stat?
//            int result = algo.sort(a);
            algo.sort(a);
            verify(a);
            if (verbose) System.out.println("Done");
//            if (comp) {
//                System.out.print(verbose ? "Comparisons: " + result + "\n" : result + " ");
//            }
        } else {
            // Boyer's or our own?
            double us = (argz.get("-b", false)) ? boyer(a, algo)
                                                : bench(a, algo);
            verify(a);

            // Print execution time
            System.out.print(us + ((verbose) ? " us\n" : " "));
        }
    }

    private static double boyer(final int[] a, final Algorithm algo) {
        // Silence the nonsense warnings
        silence();

        // Do the benchmark (runs on construction)
        Benchmark bench = new Benchmark(new Runnable() {
            @Override
            public void run() {
                int[] test = a.clone();
                algo.sort(test);
            }
        });
        algo.sort(a);

        // Restore out and err streams
        speak();

        // Return time, seconds * 10^6 = microseconds
        return bench.getMean() * 1000000;
    }

    private static double bench(final int[] a, final Algorithm algo) {
        // Do a warmup session
        int[] test;
        for (int w = 0; w < 15000; w++) {
            test = a.clone();
            algo.sort(test);
            verify(test);
        }

        // Then it's time to bench
        int iterations = 10000;
        long total = 0;
        for (int i = 0; i < iterations; i++) {
            test = a.clone();

            long start = System.nanoTime();
            algo.sort(test);
            long end = System.nanoTime();

            total += (end - start);
            verify(test);
        }
        algo.sort(a);

        // Return time, nanoseconds * 10^-3 = microseconds
        return ((double) total / iterations) * 0.001;
    }

    private static void verify(final int[] a) {
        for (int i = 1; i < a.length; i++) {
            if (a[i-1] > a[i]) {
                System.out.println("ERROR! a[" + (i-1) + "]=" + a[i-1] + " before a[" + i + "]=" + a[i]);
            }
        }
    }

    private static long sum(final int[] a) {
        long sum = 0;
        for (int i = 1; i < a.length; i++) {
            if (a[i-1] > a[i]) {
                sum += a[i-1];
            }
        }
        return sum;
    }

    private static void showHelp() {
        String[] first = {
            "Arguments:",
            "  -n <integer>      array size",
            "  -input <string>   input type",
            "  -algo <string>    algorithm",
            "  -b                use Boyer's benchmark framework",
            "  -t                output execution time only (for batch runs)",
            "  -pre              run everything but the benchmark (for perf stat)",
            "  -once             run the benchmark once only (for perf stat)",
            ""
        };

        for (String line : first) {
            System.out.println(line);
        }

        System.out.println("Input types:");
        for (String type : inputs.keySet()) {
            System.out.println("  " + type);
        }
        System.out.println();

        System.out.println("Algorithms");
        for (String algo : algorithms.keySet()) {
            System.out.println("  " + algo);
        }
    }

    private static void silence() {
        System.setOut(NULL_STREAM);
        System.setErr(NULL_STREAM);
    }

    private static void speak() {
        System.setOut(STDOUT);
        System.setErr(STDERR);
    }

    private static final PrintStream STDOUT = System.out;
    private static final PrintStream STDERR = System.err;

    private static final PrintStream NULL_STREAM = new PrintStream(new OutputStream() {
        public void write(int b) throws IOException {}
        public void write(byte[] b) throws IOException {}
        public void write(byte[] b, int off, int len) throws IOException {}
    });

    private static interface Algorithm {
        public void sort(int[] a);
    }

    private static interface Input {
        public void fill(int[] a);
    }
}
