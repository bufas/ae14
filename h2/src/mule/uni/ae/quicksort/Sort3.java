package mule.uni.ae.quicksort;

/**
 * Sort 3 elements in at most 3 comparisons.
 * <p>
 * This algorithm is used as a sub-procedure in the median-of-3 version
 * of the single-pivot QuickSort algorithm, and has been implemented to
 * be as efficient as possible, without any care for readability. The
 * algorithm is a little complex, but at least a little simpler than the
 * Sort5 algorithm.
 */
public class Sort3 {
    /**
     * Sort three elements of an array.
     * <p>
     * This implementation uses no less than 2 and no more than 3 comparisons
     * to sort the three elements in the given array.
     *
     * @param a the array in which the elements to sort exist
     * @param e1 index of the first element
     * @param e2 index of the second element
     * @param e3 index of the third element
     */
    public static void sort(int[] a, int e1, int e2, int e3) {
//    public static int sort(int[] a, int e1, int e2, int e3) {
//        int comparisons = 0;
        if (a[e1] < a[e2]) {
            // 1<2
            if (a[e2] > a[e3]) {
                // 1<2, 3<2
                if (a[e1] < a[e3]) {
                    // 1<3<2
                    int t = a[e2];
                    a[e2] = a[e3];
                    a[e3] = t;
                } else {
                    // 3<1<2
                    int t = a[e3];
                    a[e3] = a[e2];
                    a[e2] = a[e1];
                    a[e1] = t;
                }
//                comparisons++;
            }
//            comparisons++;
            // 1<2<3 - sorted!
        } else {
            // 2<1
            if (a[e1] > a[e3]) {
                // 2<1, 3<1
                if (a[e2] < a[e3]) {
                    // 2<3<1
                    int t = a[e1];
                    a[e1] = a[e2];
                    a[e2] = a[e3];
                    a[e3] = t;
                } else {
                    // 3<2<1
                    int t = a[e1];
                    a[e1] = a[e3];
                    a[e3] = t;
                }
//                comparisons++;
            } else {
                // 2<1<3
                int t = a[e2];
                a[e2] = a[e1];
                a[e1] = t;
            }
//            comparisons++;
        }
//        comparisons++;
//        return comparisons;
    }
}
