package mule.uni.ae.quicksort;

/**
 * Dual-pivot QuickSort implementation due to Vladimir Yaroslavskiy in his
 * paper <i>Dual-Pivot Quicksort</i>, 2009.
 * <p>
 * This implementation is identical to Yaroslavskiy's, with the exception of a
 * few variable names and modifications to, and additional, comments. It uses
 * a possibly sub-optimal algorithm for sorting the 5 indices, and the in-line
 * InsertionSort may be sup-optimal due to an additional assignment operation.
 */
public class QuickSortYaroslavskiy {
    private static final int DIST_SIZE = 13;
    private static final int TINY_SIZE = 17;

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
        int length = right - left;
        int x;

        // InsertionSort for small sizes
        if (length < TINY_SIZE) {
            for (int i = left + 1; i <= right; i++) {
                for (int j = i; j > left && a[j] < a[j-1]; j--) {
                    x = a[j-1];
                    a[j-1] = a[j];
                    a[j] = x;
                }
            }
            return;
        }

        // Median indices
        int sixth = length / 6;
        int m1 = left + sixth;
        int m2 = m1 + sixth;
        int m3 = m2 + sixth;
        int m4 = m3 + sixth;
        int m5 = m4 + sixth;

        // 5-element sorting
        if (a[m1] > a[m2]) { x = a[m1]; a[m1] = a[m2]; a[m2] = x; }
        if (a[m4] > a[m5]) { x = a[m4]; a[m4] = a[m5]; a[m5] = x; }
        if (a[m1] > a[m3]) { x = a[m1]; a[m1] = a[m3]; a[m3] = x; }
        if (a[m2] > a[m3]) { x = a[m2]; a[m2] = a[m3]; a[m3] = x; }
        if (a[m1] > a[m4]) { x = a[m1]; a[m1] = a[m4]; a[m4] = x; }
        if (a[m3] > a[m4]) { x = a[m3]; a[m3] = a[m4]; a[m4] = x; }
        if (a[m2] > a[m5]) { x = a[m2]; a[m2] = a[m5]; a[m5] = x; }
        if (a[m2] > a[m3]) { x = a[m2]; a[m2] = a[m3]; a[m3] = x; }
        if (a[m4] > a[m5]) { x = a[m4]; a[m4] = a[m5]; a[m5] = x; }

        // Pivots (2,4)
        int pivot1 = a[m2];
        int pivot2 = a[m4];

        boolean diffPivots = pivot1 != pivot2;
        a[m2] = a[left];
        a[m4] = a[right];

        // Center part pointers
        int less  = left  + 1;
        int great = right - 1;

        // Sorting
        if (diffPivots) {
            for (int k = less; k <= great; k++) {
                x = a[k];
                if (x < pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                } else if (x > pivot2) {
                    while (a[great] > pivot2 && k < great) {
                        great--;
                    }
                    a[k] = a[great];
                    a[great--] = x;
                    x = a[k];
                    if (x < pivot1) {
                        a[k] = a[less];
                        a[less++] = x;
                    }
                }
            }
        } else {
            // This block is almost identical to the one above;
            // differences marked by comments
            for (int k = less; k <= great; k++) {
                x = a[k];
                if (x == pivot1) {          //
                    continue;               // New block
                }                           //
                if (x < pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                } else {                    // else-if  -->  else
                    while (a[great] > pivot2 && k < great) {
                        great--;
                    }
                    a[k] = a[great];
                    a[great--] = x;
                    x = a[k];
                    if (x < pivot1) {
                        a[k] = a[less];
                        a[less++] = x;
                    }
                }
            }
        }
        // Swap
        a[left] = a[less-1];
        a[less-1] = pivot1;

        a[right] = a[great+1];
        a[great+1] = pivot2;

        // Left and right parts
        sort(a, left,      less - 2);
        sort(a, great + 2, right);

        // Equal elements
        if (great - less > length - DIST_SIZE && diffPivots) {
            // Again, this block closely resembles the one above;
            // differences marked by comments
            for (int k = less; k <= great; k++) {
                x = a[k];
                if (x == pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                } else if (x == pivot2) {   // '>'  -->  '=='
                    a[k] = a[great];        // while-loop removed
                    a[great--] = x;
                    x = a[k];
                    if (x == pivot1) {      // '<'  -->  '=='
                        a[k] = a[less];
                        a[less++] = x;
                    }
                }
            }
        }

        // Center part
        if (diffPivots) {
            sort(a, less, great);
        }
    }
}
