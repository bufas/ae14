package mule.uni.ae.quicksort;

/**
 * Identical to {@link mule.uni.ae.quicksort.QuickSortYaroslavskiyOpt} with the exception of
 * using pivots 1 and 3 instead of 2 and 4.
 */
public class QuickSortYaroslavskiyOpt13 {
    private static final int DIST_SIZE = 13;
    private static final int TINY_SIZE = 17;

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
//        comparisons++;
        if (length < TINY_SIZE) {
//            comparisons += InsertionSort.sort(a, left, right);
            InsertionSort.sort(a, left, right);
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
//        comparisons += Sort5.sort(a, m1, m2, m3, m4, m5);
        Sort5.sort(a, m1, m2, m3, m4, m5);

        // Pivots (1,3)
        int pivot1 = a[m1];
        int pivot2 = a[m3];

        boolean diffPivots = pivot1 != pivot2;
//        comparisons++;
        a[m1] = a[left];
        a[m3] = a[right];

        // Center part pointers
        int less  = left  + 1;
        int great = right - 1;

        // Sorting
        if (diffPivots) {
            for (int k = less; k <= great; k++) {
//                comparisons++;
                x = a[k];
                if (x < pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                } else if (x > pivot2) {
//                    comparisons++;
                    while (a[great] > pivot2 && k < great) {
//                        comparisons++;
//                        comparisons++;
                        great--;
                    }
                    a[k] = a[great];
                    a[great--] = x;
                    x = a[k];
                    if (x < pivot1) {
                        a[k] = a[less];
                        a[less++] = x;
                    }
//                    comparisons++;
                }
//                comparisons++;
            }
        } else {
            // This block is almost identical to the one above;
            // differences marked by comments
            for (int k = less; k <= great; k++) {
//                comparisons++;
                x = a[k];
//                comparisons++;
                if (x == pivot1) {          //
                    continue;               // New block
                }                           //
                if (x < pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                } else {                    // else-if  -->  else
                    while (a[great] > pivot2 && k < great) {
//                        comparisons++;
//                        comparisons++;
                        great--;
                    }
                    a[k] = a[great];
                    a[great--] = x;
                    x = a[k];
                    if (x < pivot1) {
                        a[k] = a[less];
                        a[less++] = x;
                    }
//                    comparisons++;
                }
//                comparisons++;
            }
        }
//        comparisons++;
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
//                comparisons++;
                x = a[k];
                if (x == pivot1) {
                    a[k] = a[less];
                    a[less++] = x;
                } else if (x == pivot2) {   // '>'  -->  '=='
//                    comparisons++;
                    a[k] = a[great];        // while-loop removed
                    a[great--] = x;
                    x = a[k];
                    if (x == pivot1) {      // '<'  -->  '=='
                        a[k] = a[less];
                        a[less++] = x;
                    }
//                    comparisons++;
                }
//                comparisons++;
            }
        }
//        comparisons += 2;

        // Center part
        if (diffPivots) {
            sort(a, less, great);
        }
//        comparisons++;
    }
}
