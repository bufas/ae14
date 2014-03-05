package mule.uni.ae.quicksort;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import mule.uni.ae.quicksort.util.Permutation;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import java.lang.reflect.Method;
import java.util.*;

/**
 * Test suite consisting of various correctness tests for the different
 * sorting algorithms.
 * <p>
 * A parameterized runner is used to avoid having to duplicate test code,
 * but since all the sorting algorithms are implemented as static methods
 * in classes that share no common interface, it is necessary to use
 * reflection, because Java doesn't support duck typing.
 * <p>
 * {@code PrimitiveArrayArgumentToVariableArgMethod} is suppressed to
 * avoid dumb warnings about passing {@code int[]} to a method expecting
 * a varargs parameter, i.e. {@link Method#invoke(Object, Object...)}.
 */
@RunWith(Parameterized.class)
@SuppressWarnings("PrimitiveArrayArgumentToVariableArgMethod")
public class SortTest {
    /**
     * The classes to test. Each class must provide a public facing, static
     * method called "sort", that takes an {@code int[]} as its only argument.
     */
    @Parameters
    public static Collection<Object[]> sorts() {
        return Arrays.asList(new Object[][]{
            {InsertionSort.class},
            {QuickSort.class},
            {QuickSortDual.class},
            {QuickSortYaroslavskiy.class}
        });
    }

    /**
     * The reflected method instance for later invocation.
     */
    private Method sort;

    /**
     * Instantiate a new SortTest to test the given class.
     * <p>
     * This constructor is invoked by JUnit for each test, as per the
     * parameter specified in the {@link #sorts} method.
     */
    public SortTest(Class<?> clazz) {
        try {
            sort = clazz.getMethod("sort", int[].class);
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
    }



    //-------------------------------------------------------------------------
    //
    //      Basic tests
    //
    //-------------------------------------------------------------------------

    /**
     * An already sorted array should remain sorted.
     */
    @Test
    public void sortedArrayRemainsSorted() throws Exception {
        int[] expected = {0,1,2,3,4,5,6,7,8,9};
        int[] actual   = {0,1,2,3,4,5,6,7,8,9};

        sort.invoke(null, actual);

        for (int i = 0; i < 10; i++) {
            assertEquals(expected[i], actual[i]);
        }
    }

    /**
     * Reversed array.
     */
    @Test
    public void reverseArrayBecomesSorted() throws Exception {
        int[] expected = {0,1,2,3,4,5,6,7,8,9};
        int[] actual   = {9,8,7,6,5,4,3,2,1,0};

        sort.invoke(null, actual);

        for (int i = 0; i < 10; i++) {
            assertEquals(expected[i], actual[i]);
        }
    }

    /**
     * Sorts all permutations of the elements 1,2,3,4,5.
     * <p>
     * An "exhaustive search"-style test (a total of 5! = 120 permutations) to
     * crash test various permutations of the same elements.
     */
    @Test
    public void allPermutationsOfFive() throws Exception {
        List<String> perms = new ArrayList<>();
        Permutation.permutation(perms, "12345");

        int[] expected = {1,2,3,4,5};

        for (String perm : perms) {
            int[] actual = new int[5];
            for (int i = 0; i < 5; i++) {
                actual[i] = Character.getNumericValue(perm.charAt(i));
            }

            sort.invoke(null, actual);

            for (int i = 0; i < 5; i++) {
                assertEquals(expected[i], actual[i]);
            }
        }
    }



    //-------------------------------------------------------------------------
    //
    //      "Random" tests
    //
    //-------------------------------------------------------------------------

    /**
     * The seeds used in the random tests below
     */
    private static final long[] seeds = {
        1, 10, 1337, Long.MAX_VALUE, Integer.MAX_VALUE, Byte.MAX_VALUE
    };

    /**
     * Sorts random permutations of elements [1..10].
     */
    @Test
    public void r10() throws Exception {
        for (int s = 0; s < seeds.length; s++) {
            int[] a = createArray(10, new Random(s));
            sort.invoke(null, a);
            verifySorted(a);
        }
    }

    /**
     * Sorts random permutations of elements [1..100].
     */
    @Test
    public void r100() throws Exception {
        for (int s = 0; s < seeds.length; s++) {
            int[] a = createArray(100, new Random(s));
            sort.invoke(null, a);
            verifySorted(a);
        }
    }

    /**
     * Sorts random permutations of elements [1..1000].
     */
    @Test
    public void r1000() throws Exception {
        for (int s = 0; s < seeds.length; s++) {
            int[] a = createArray(1000, new Random(s));
            sort.invoke(null, a);
            verifySorted(a);
        }
    }

    /**
     * Sorts random permutations of elements [1..10000].
     */
    @Test
    public void r10000() throws Exception {
        for (int s = 0; s < seeds.length; s++) {
            int[] a = createArray(10000, new Random(s));
            sort.invoke(null, a);
            verifySorted(a);
        }
    }

    /**
     * Sorts random permutations of elements [1..100000].
     */
    @Test
    public void r100000() throws Exception {
        for (int s = 0; s < seeds.length; s++) {
            int[] a = createArray(100000, new Random(s));
            sort.invoke(null, a);
            verifySorted(a);
        }
    }



    //-------------------------------------------------------------------------
    //
    //      Utility methods
    //
    //-------------------------------------------------------------------------

    /**
     * Utility method for creating a random array of the elements
     * in the range [1..n] using the given RNG for shuffling.
     */
    private int[] createArray(int n, Random rand) {
        List<Integer> list = new ArrayList<>(n);
        for (int i = 0; i < n; i++) {
            list.add(i+1);
        }
        Collections.shuffle(list, rand);
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            result[i] = list.get(i);
        }
        return result;
    }

    /**
     * Utility method for verifying that an array is sorted.
     */
    private void verifySorted(int[] a) {
        for (int i = 0; i < (a.length - 1); i++) {
            assertTrue(a[i] < a[i+1]);
        }
    }
}
