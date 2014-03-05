package mule.uni.ae.quicksort.util;

import java.util.List;

/**
 * Utility class for generating permutations of strings.
 */
public class Permutation {
    /**
     * Generate and print all permutations of a string (e.g "12345")
     * to {@code stdout}.
     *
     * @param str the string whose permutations to generate
     */
    public static void permutation(String str) {
        permutation("", str);
    }

    /**
     * Internal helper for {@link #permutation(String)}.
     */
    private static void permutation(String prefix, String str) {
        int n = str.length();
        if (n == 0) {
            System.out.println(prefix);
        } else {
            for (int i = 0; i < n; i++) {
                permutation(prefix + str.charAt(i), str.substring(0, i) + str.substring(i + 1, n));
            }
        }
    }

    /**
     * Generate all permutations of a string (e.g "12345") and add
     * them to the given list.
     *
     * @param list the list to add the permutations to
     * @param str the string whose permutations to generate
     */
    public static void permutation(List<String> list, String str) {
        permutation(list, "", str);
    }

    /**
     * Internal helper for {@link #permutation(List, String)}.
     */
    private static void permutation(List<String> list, String prefix, String str) {
        int n = str.length();
        if (n == 0) {
            list.add(prefix);
        } else {
            for (int i = 0; i < n; i++) {
                permutation(list, prefix + str.charAt(i), str.substring(0, i) + str.substring(i + 1, n));
            }
        }
    }
}
