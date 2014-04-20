package mule.uni.ae.quicksort;

import java.util.Deque;
import java.util.LinkedList;

/**
 * An iterative implementation of standard QuickSort with a single pivot,
 * based on the {@link QuickSort} implementation.
 * <p>
 * The purpose of this iterative implementation is to provide a version of
 * standard QuickSort that doesn't result in stack overflow due to massive
 * call stacks.
 */
public class QuickSortIte {
    /**
     * Sort the given array.
     *
     * @param a an array
     */
    public static void sort(int[] a) {
//    public static int sort(int[] a) {
//        comparisons = 0;
        sort(a, 0, a.length - 1);
//        return comparisons;
    }
//    private static int comparisons;

    /**
     * Sort the given array in the range {@code [p;r]} (both inclusive).
     *
     * @param a an array
     * @param p index of the first element in the range
     * @param r index of the last element in the range
     */
    public static void sort(int[] a, int p, int r) {
        // Stacks to keep track of p's and q's
        Deque<Integer> ps = new LinkedList<>();
        Deque<Integer> rs = new LinkedList<>();

        // Start off with the end points
        ps.push(p);
        rs.push(r);

        while (!ps.isEmpty()) {
//            comparisons++;
            p = ps.poll();
            r = rs.poll();

            // Stop condition
//            comparisons++;
            if (p >= r) {
                continue;
            }

            // Partition the array
            int q = partition(a, p, r);

            // Left
            ps.push(p);
            rs.push(q - 1);

            // Right
            ps.push(q + 1);
            rs.push(r);
        }
    }

    private static int partition(int[] a, int p, int r) {
        int x = a[r];
        int i = p - 1;
        for (int j = p; j < r; j++) {
//            comparisons++;
            if (a[j] <= x) {
                i++;
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
//            comparisons++;
        }
        i++;
        int tmp = a[i];
        a[i] = a[r];
        a[r] = tmp;
        return i;
    }
}
