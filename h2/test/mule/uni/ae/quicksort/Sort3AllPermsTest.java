package mule.uni.ae.quicksort;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import static org.junit.Assert.assertEquals;

/**
 * Test suite for the 3-element sorting algorithm.
 * <p>
 * The tests in this class are quite simply all 6 permutations of the
 * elements {1..3}, and verification that the algorithm correctly sorts
 * all the permutations.
 */
@RunWith(Parameterized.class)
public class Sort3AllPermsTest {
    /**
     * The parameters for this test suite are all the 6 permutations
     * of the elements {1..3}.
     */
    @Parameters
    public static Collection<Object[]> perms() {
        // All permutations as a 2-dimensional int array
        int[][] perms = {
            {1,2,3},{1,3,2},
            {2,1,3},{2,3,1},
            {3,1,2},{3,2,1}
        };

        // Create and return a list (collection) of Object arrays for JUnit
        List<Object[]> result = new ArrayList<>();
        for (int[] perm : perms) {
            result.add(new Object[]{perm});
        }
        return result;
    }

    /**
     * Current array to sort
     */
    private int[] array;

    /**
     * Instantiate a Sort3AllPermsTest to sort the given array.
     * <p>
     * This constructor is invoked by JUnit for each test, as per the
     * parameters specified in the {@link #perms} method.
     */
    public Sort3AllPermsTest(int[] array) {
        this.array = array;
    }

    /**
     * All permutations must sort to {1,2,3}.
     */
    @Test
    public void testPermutation() {
        Sort3.sort(array, 0, 1, 2);

        assertEquals(1, array[0]);
        assertEquals(2, array[1]);
        assertEquals(3, array[2]);
    }
}
