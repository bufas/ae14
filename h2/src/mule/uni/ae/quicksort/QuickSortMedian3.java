package mule.uni.ae.quicksort;

/**
 * Simple variation of the standard QuickSort, where the single pivot is
 * always the center element.
 */
public class QuickSortMedian3 {
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
        // Select pivot as median of 3
        int m = (p + r) >>> 1;
        Sort3.sort(a, p, m, r);

        // Swap the pivot to the end
        int tmp = a[m];
        a[m] = a[r];
        a[r] = tmp;

        int x = a[r];
        int i = p - 1;
        for (int j = p; j < r; j++) {
            if (a[j] <= x) {
                i++;
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
        i++;
        tmp = a[i];
        a[i] = a[r];
        a[r] = tmp;
        return i;
    }
}
