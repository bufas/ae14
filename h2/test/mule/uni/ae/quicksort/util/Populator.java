package mule.uni.ae.quicksort.util;

import java.util.Random;

public class Populator {
    private static final long SEED = 1985713895739l;
    private Populator() {}

    /**
     * Random elements. This method is primarily useful for the warmup phase.
     */
    public static void random(final int[] a) {
        Random random = new Random();
        for (int i = 0; i < a.length; i++) {
            a[i] = random.nextInt();
        }
    }

    /**
     * Random elements in [0..m).
     */
    public static void random(final int[] a, final int m) {
        Random random = new Random(SEED);
        for (int i = 0; i < a.length; i++) {
            a[i] = random.nextInt(m);
        }
    }

    /**
     * Values equal to indices - sorted.
     */
    public static void ascend(final int[] a) {
        for (int i = 0; i < a.length; i++) {
            a[i] = i;
        }
    }

    /**
     * Values equal to (MAX - index) - reverse sorted.
     */
    public static void descend(final int[] a) {
        for (int i = 0; i < a.length; i++) {
            a[i] = a.length - i;
        }
    }

    /**
     * All values are identical.
     */
    public static void same(final int[] a) {
        for (int i = 0; i < a.length; i++) {
            a[i] = 0;
        }
    }

    /**
     * Sawblade - somewhat similar to ascend, but with several periods of
     * magnitude defined by m
     */
    public static void period(final int[] a, final int m) {
        for (int i = 0; i < a.length; i++) {
            a[i] = i % m;
        }
    }

    /**
     * Sawblade - similar to period, but with a steepness depending on m,
     * and the array size as the magnitude
     */
    public static void stagger(final int[] a, final int m) {
        for (int i = 0; i < a.length; i++) {
            a[i] = (i*m + i) % a.length;
        }
    }

    /**
     * Combination of ascend and descend, in the shape of organ pipes.
     */
    public static void organPipes(final int[] a) {
        int middle = a.length / 2;
        for (int i = 0; i < middle; i++) {
            a[i] = i;
        }
        for (int i = middle; i < a.length ; i++) {
            a[i] = a.length - i - 1;
        }
    }

    /**
     * Create a nearly sorted ascend array, then randomly swap two elements
     * in a range of [left;left+k) where left is the current left-most index
     * (increased by k every iteration) and k is the range in which to swap.
     * A large k thus yields fewer swaps in greater sections.
     */
    public static void ksorted(final int[] a, int k) {
        // Start with sorted data
        ascend(a);
        Random random = new Random(SEED);

        // Shuffle two random elements in each range
        for (int left = 0; left < a.length; left += k) {
            // Cap k if necessary
            if (left + k > a.length) {
                k = (a.length - left);

                // If there's only one element left, skip it
                if (k == 1) {
                    break;
                }
            }

            int i = left + random.nextInt(k);
            int j = left + random.nextInt(k - 1);

            // Make sure the indices are different
            // We can j++ because j is guaranteed to be 1 lower than end
            if (i == j) {
                j++;
            }

            // Swap them
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
}
