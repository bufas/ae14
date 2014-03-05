package mule.uni.ae.quicksort;

/**
 * A simple implementation of standard QuickSort with a single pivot, due to
 * Cormen et al. in <i>Introduction to Algorithms, 3rd Edition</i>.
 * <p>
 * This algorithm uses a single pivot, which is always selected as the final
 * element in a given range.
 */
public class QuickSort {
    /**
     * Sort the given array.
     *
     * @param a an array
     */
    public static void sort(int[] a) {
        sort(a, 0, a.length - 1);
    }

    /**
     * Sort the given array in the range {@code [p;r]} (both inclusive).
     *
     * @param a an array
     * @param p index of the first element in the range
     * @param r index of the last element in the range
     */
    public static void sort(int[] a, int p, int r) {
        if (p < r) {
            int q = partition(a, p, r);
            sort(a, p, q - 1);
            sort(a, q + 1, r);
        }
    }

    private static int partition(int[] a, int p, int r) {
        int x = a[r];
        int i = p - 1;
        for (int j = p; j < r; j++) {
            if (a[j] <= x) {
                i++;
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
        i++;
        int tmp = a[i];
        a[i] = a[r];
        a[r] = tmp;
        return i;
    }
}
