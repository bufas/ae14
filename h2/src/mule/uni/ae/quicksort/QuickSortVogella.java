package mule.uni.ae.quicksort;

public class QuickSortVogella {
    public static void sort(int[] a) {
        if (a == null || a.length == 0){
            return;
        }
        sort(a, 0, a.length - 1);
    }

    private static void sort(int[] a, int low, int high) {
        int pivot = a[low + (high-low)/2];
        int i = low, j = high;

        while (i <= j) {
            while (a[i] < pivot) {
                i++;
            }
            while (a[j] > pivot) {
                j--;
            }
            if (i <= j) {
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;

                i++;
                j--;
            }
        }
        // Recursion
        if (low < j)
            sort(a, low, j);
        if (i < high)
            sort(a, i, high);
    }
}
