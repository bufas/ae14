package mule.uni.ae.quicksort;

/**
 * Triple-pivot QuickSort implementation due to Kushagra et. al from their
 * 2013 paper <i>Multi-Pivot Quicksort: Theory and Experiments</i>.
 */
public class QuickSortTriple {
    private static final int TINY_SIZE = 10;
    private static final int YARO_SIZE = 30;

    public static void sort(int[] a) {
//    public static int sort(int[] a) {
//        comparisons = 0;
        sort(a, 0, a.length - 1);
//        return comparisons;
    }
//    private static int comparisons;

    public static void sort(int[] A, int left, int right) {
        // 0 -> nothing, 1 -> sorted
        int length = right - left + 1;
//        comparisons++;
        if (length <= 1) {
            return;
        }

        // InsertionSort for small arrays
//        comparisons++;
        if (length < TINY_SIZE) {
//            comparisons += InsertionSort.sort(A, left, right);
            InsertionSort.sort(A, left, right);
            return;
        }

//        if (length < YARO_SIZE) {
//            QuickSortYaroslavskiyOpt.sort(A, left, right);
//            return;
//        }

        // Sort pivots
//        comparisons += Sort3.sort(A, left, left+1, right);
        Sort3.sort(A, left, left+1, right);

        // Partition step
        int a = left + 2;
        int b = left + 2;
        int c = right - 1;
        int d = right - 1;

        int p = A[left];
        int q = A[left+1];
        int r = A[right];

        int t;

        while (b <= c) {
//            comparisons++;
            while (A[b] < q && b <= c) {
//                comparisons++;
//                comparisons++;
                if (A[b] < p) {
                    t = A[a]; A[a] = A[b]; A[b] = t; // Swap A[a], A[b]
                    a++;
                }
//                comparisons++;
                b++;
            }
            while (A[c] > q && b <= c) {
//                comparisons++;
//                comparisons++;
                if (A[c] > r) {
                    t = A[c]; A[c] = A[d]; A[d] = t; // Swap A[c], A[d]
                    d--;
                }
//                comparisons++;
                c--;
            }
            if (b <= c) {
                if (A[b] > r) {
                    if (A[c] < p) {
                        t = A[c]; A[c] = A[b]; A[b] = A[a]; A[a] = t;
//                        t = A[b]; A[b] = A[a]; A[a] = t; // Swap A[b], A[a]
//                        t = A[a]; A[a] = A[c]; A[c] = t; // Swap A[a], A[c]
                        a++;
                    } else {
                        t = A[b]; A[b] = A[c]; A[c] = t; // Swap A[b], A[c]
                    }
//                    comparisons++;
                    t = A[c]; A[c] = A[d]; A[d] = t; // Swap A[c], A[d]
                    b++;
                    c--;
                    d--;
                } else {
                    if (A[c] < p) {
                        t = A[c]; A[c] = A[b]; A[b] = A[a]; A[a] = t;
//                        t = A[b]; A[b] = A[a]; A[a] = t; // Swap A[b], A[a]
//                        t = A[a]; A[a] = A[c]; A[c] = t; // Swap A[a], A[c]
                        a++;
                    } else {
                        t = A[b]; A[b] = A[c]; A[c] = t; // Swap A[b], A[c]
                    }
//                    comparisons++;
                    b++;
                    c--;
                }
//                comparisons++;
            }
//            comparisons++;
        }
        a--;
        b--;
        c++;
        d++;

        t = A[left+1]; A[left+1] = A[a]; A[a] = t; // Swap A[left+1], A[a]
        t = A[a];      A[a]      = A[b]; A[b] = t; // Swap A[a], A[b]
        a--;
        t = A[left];   A[left]   = A[a]; A[a] = t; // Swap A[left], A[a]
        t = A[right];  A[right]  = A[d]; A[d] = t; // Swap A[right], A[d]

        // Recursively sort each section
        sort(A, left, a - 1);
        sort(A, a,    b);
        sort(A, c,    d - 1);
        sort(A, d,    right);
    }
}
