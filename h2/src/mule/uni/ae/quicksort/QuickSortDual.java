package mule.uni.ae.quicksort;

/**
 * Dual-pivot QuickSort implementation, similar to the JRE7 implementation,
 * according to <i>Engineering Java 7's Dual Pivot QuickSort Using MaLiJAn</i>
 * by Wild et al.
 */
public class QuickSortDual {
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
        int length = right - left + 1;
//        comparisons++;
        if (length < 5) {
//            comparisons += InsertionSort.sort(a, left, right);
            InsertionSort.sort(a, left, right);
            return;
        }

        int s7 = (length >> 3) + (length >> 6) + 1;
        int e3 = (left + right) >>> 1;
        int e2 = e3 - s7;
        int e1 = e2 - s7; if (length == 8) e1++; //comparisons++;
        int e4 = e3 + s7;
        int e5 = e4 + s7;

//        comparisons += Sort5.sort(a, e1, e2, e3, e4, e5);
        Sort5.sort(a, e1, e2, e3, e4, e5);

        int pIndex = e2;
        int qIndex = e4;

        int l = left + 1;
        int g = right - 1;
        int k = l;

        int p = a[pIndex]; a[pIndex] = a[left];
        int q = a[qIndex]; a[qIndex] = a[right];

        while (k <= g) {
//            comparisons++;
            int ak = a[k];
            if (ak < p) {
                a[k] = a[l];
                a[l] = ak;
                l++;
            } else if (ak >= q) {
//                comparisons++;
                while (a[g] > q && k < g) {
//                    comparisons++;
//                    comparisons++;
                    g--;
                }
                if (a[g] < p) {
                    a[k] = a[l];
                    a[l] = a[g];
                    l++;
                } else {
                    a[k] = a[g];
                }
//                comparisons++;
                a[g] = ak;
                g--;
            }
//            comparisons++;
            k++;
        }
        l--;
        g++;

        a[left]  = a[l]; a[l] = p;
        a[right] = a[g]; a[g] = q;

        sort(a, left,  l - 1);
        sort(a, g + 1, right);
        sort(a, l, g);
    }
}
