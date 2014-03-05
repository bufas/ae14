package mule.uni.ae.quicksort;

/**
 * Basic implementation of InsertionSort, due to Wikipedia.
 * <p>
 * This algorithm uses a very simple optimization for the swapping step,
 * in that the current element is stored before the inner {@code while}
 * loop, such that swapping becomes unnecessary. As such, the current
 * element is stored, the array is shifted to the right, and finally the
 * current element is inserted into place.
 *
 * @see <a href="http://en.wikipedia.org/wiki/Insertion_sort">InsertionSort on Wikipedia</a>
 */
public class InsertionSort {
    /**
     * Sort the given array.
     *
     * @param a an array
     */
    public static void sort(int[] a) {
        sort(a, 0, a.length - 1);
    }

    /**
     * Sort the given array in the range {@code [left;right]} (both inclusive).
     *
     * @param a an array
     * @param left index of the first element in the range
     * @param right index of the last element in the range
     */
    public static void sort(int[] a, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int x = a[i];
            int j = i;
            while (j > left && a[j-1] > x) {
                a[j] = a[j-1];
                j--;
            }
            a[j] = x;
        }
    }
}
