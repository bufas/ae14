package mule.uni.ae.quicksort;

/**
 * Effective solution to the "sort 5 elements in 7 comparisons" problem.
 * <p>
 * This algorithm is used as a sub-procedure in the multi-pivot QuickSort
 * algorithm, and has been implemented to be as efficient as possible,
 * without any care for readability. The algorithm is a little complex,
 * but nothing a cup of coffee and a big cookie can't solve.
 */
public class Sort5 {
    /**
     * Sort five elements of an array.
     * <p>
     * This implementation uses no less than 6 and no more than 7 comparisons
     * to sort the five elements in the given array.
     *
     * @param a the array in which the elements to sort exist
     * @param e1 index of the first element
     * @param e2 index of the second element
     * @param e3 index of the third element
     * @param e4 index of the fourth element
     * @param e5 index of the fifth element
     */
    public static void sort(int[] a, int e1, int e2, int e3, int e4, int e5) {
//    public static int sort(int[] a, int e1, int e2, int e3, int e4, int e5) {
//        int comparisons = 0;
        if (a[e1] > a[e2]) {
            int t = a[e1];
            a[e1] = a[e2];
            a[e2] = t;
        } // 1<2
//        comparisons++;

        if (a[e3] > a[e4]) {
            int t = a[e3];
            a[e3] = a[e4];
            a[e4] = t;
        } // 1<2, 3<4
//        comparisons++;

        if (a[e2] > a[e4]) {
            int t = a[e2];
            a[e2] = a[e4];
            a[e4] = t;
            int u = a[e1];
            a[e1] = a[e3];
            a[e3] = u;
        } // 1<2<4, 3<4
//        comparisons++;

        // Figure out where 5 goes in 1<2<4
        if (a[e5] > a[e2]) {
            // 5>2, 5>4?
            if (a[e5] > a[e4]) {
                // 1<2<4<5, 3<4
                if (a[e3] < a[e2]) {
                    // 1<2<4<5, 3<4, 3<2
                    if (a[e3] < a[e1]) {
                        // 3<1<2<4<5
                        int t = a[e3];
                        a[e3] = a[e2];
                        a[e2] = a[e1];
                        a[e1] = t;
                    } else {
                        // 1<3<2<4<5
                        int t = a[e3];
                        a[e3] = a[e2];
                        a[e2] = t;
                    }
//                    comparisons++;
                }
//                comparisons++;
                // else:
                // 1<2<4<5, 3<4, 2<3
                // 1<2<3<4<5
                // Sorted! This is the only case of just 6 comparisons
            } else {
                // 1<2<5<4, 3<4
                if (a[e3] < a[e2]) {
                    // 1<2<5<4, 3<4, 3<2
                    if (a[e3] < a[e1]) {
                        // 3<1<2<5<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = t;     // 5 -> 4
                        t = a[e3];
                        a[e3] = a[e2]; // 2 -> 3
                        a[e2] = a[e1]; // 1 -> 2
                        a[e1] = t;     // 3 -> 1
                    } else {
                        // 1<3<2<5<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = t;     // 5 -> 4
                        t = a[e3];
                        a[e3] = a[e2]; // 2 -> 3
                        a[e2] = t;     // 3 -> 2
                    }
//                    comparisons++;
                } else {
                    // 1<2<5<4, 3<4, 2<3
                    if (a[e3] < a[e5]) {
                        // 1<2<3<5<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = t;     // 5 -> 4
                    } else {
                        // 1<2<5<3<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e3]; // 3 -> 4
                        a[e3] = t;     // 5 -> 3
                    }
//                    comparisons++;
                }
//                comparisons++;
            }
//            comparisons++;
        } else {
            // 5<2, 5>1?
            if (a[e5] > a[e1]) {
                // 1<5<2<4, 3<4
                if (a[e3] < a[e5]) {
                    // 1<5<2<4, 3<4, 3<5
                    if (a[e3] < a[e1]) {
                        // 3<1<5<2<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e2]; // 2 -> 4
                        a[e2] = a[e1]; // 1 -> 2
                        a[e1] = a[e3]; // 3 -> 1
                        a[e3] = t;     // 5 -> 3
                    } else {
                        // 1<3<5<2<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e2]; // 2 -> 4
                        a[e2] = a[e3]; // 3 -> 2
                        a[e3] = t;     // 5 -> 3
                    }
//                    comparisons++;
                } else {
                    // 1<5<2<4, 3<4, 5<3
                    if (a[e3] < a[e2]) {
                        // 1<5<3<2<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e2]; // 2 -> 4
                        a[e2] = t;     // 5 -> 2
                    } else {
                        // 1<5<2<3<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e3]; // 3 -> 4
                        a[e3] = a[e2]; // 2 -> 3
                        a[e2] = t;     // 5 -> 2
                    }
//                    comparisons++;
                }
//                comparisons++;
            } else {
                // 5<1<2<4, 3<4
                if (a[e3] < a[e1]) {
                    // 5<1<2<4, 3<4, 3<1
                    if (a[e3] < a[e5]) {
                        // 3<5<1<2<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e2]; // 2 -> 4
                        a[e2] = t;     // 5 -> 2
                        t = a[e1];
                        a[e1] = a[e3]; // 3 -> 1
                        a[e3] = t;     // 1 -> 3
                    } else {
                        // 5<3<1<2<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e2]; // 2 -> 4
                        a[e2] = a[e3]; // 3 -> 2
                        a[e3] = a[e1]; // 1 -> 3
                        a[e1] = t;     // 5 -> 1
                    }
//                    comparisons++;
                } else {
                    // 5<1<2<4, 3<4, 1<3
                    if (a[e3] < a[e2]) {
                        // 5<1<3<2<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e2]; // 2 -> 4
                        a[e2] = a[e1]; // 1 -> 2
                        a[e1] = t;     // 5 -> 1
                    } else {
                        // 5<1<2<3<4
                        int t = a[e5];
                        a[e5] = a[e4]; // 4 -> 5
                        a[e4] = a[e3]; // 3 -> 4
                        a[e3] = a[e2]; // 2 -> 3
                        a[e2] = a[e1]; // 1 -> 2
                        a[e1] = t;     // 5 -> 1
                    }
//                    comparisons++;
                }
//                comparisons++;
            }
//            comparisons++;
        }
//        comparisons++;
//        return comparisons;
    }
}
