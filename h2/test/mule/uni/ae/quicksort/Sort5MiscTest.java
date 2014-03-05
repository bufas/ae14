package mule.uni.ae.quicksort;

import static org.junit.Assert.assertTrue;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import java.util.Arrays;
import java.util.Collection;

@RunWith(Parameterized.class)
public class Sort5MiscTest {
    /**
     * The parameters for this test suite are various arrays, sorted
     * and unsorted, with various indices to sort.
     */
    @Parameters
    public static Collection<Object[]> perms() {
        return Arrays.asList(new Object[][] {
            // First five elements
            {0,1,2,3,4,new int[]{0,1,2,3,4,5,6,7,8,9}}, // sorted
            {0,1,2,3,4,new int[]{9,8,7,6,5,4,3,2,1,0}}, // reverse
            {0,1,2,3,4,new int[]{5,8,1,2,3,9,0,6,4,7}}, // "random"

            // Last five elements
            {5,6,7,8,9,new int[]{0,1,2,3,4,5,6,7,8,9}},
            {5,6,7,8,9,new int[]{9,8,7,6,5,4,3,2,1,0}},
            {5,6,7,8,9,new int[]{5,8,1,2,3,9,0,6,4,7}},

            // Every other element
            {1,3,5,7,9,new int[]{0,1,2,3,4,5,6,7,8,9}},
            {1,3,5,7,9,new int[]{9,8,7,6,5,4,3,2,1,0}},
            {1,3,5,7,9,new int[]{5,8,1,2,3,9,0,6,4,7}},

            // "Front, mid, and back"
            {0,1,4,8,9,new int[]{0,1,2,3,4,5,6,7,8,9}},
            {0,1,4,8,9,new int[]{9,8,7,6,5,4,3,2,1,0}},
            {0,1,4,8,9,new int[]{5,8,1,2,3,9,0,6,4,7}},
        });
    }

    /**
     * Current array to sort
     */
    private int[] array;
    /**
     * Indices
     */
    private int e1, e2, e3, e4, e5;

    /**
     * Instantiate a Sort5AllPermsTest to sort the given array.
     * <p>
     * This constructor is invoked by JUnit for each test, as per the
     * parameters specified in the {@link #perms} method.
     */
    public Sort5MiscTest(int e1, int e2, int e3, int e4, int e5, int[] array) {
        this.array = array;
        this.e1 = e1;
        this.e2 = e2;
        this.e3 = e3;
        this.e4 = e4;
        this.e5 = e5;
    }

    /**
     * When sorted, it must be true that e1 < e2 < e3 < e4 < e5
     */
    @Test
    public void testPermutation() {
        Sort5.sort(array, e1, e2, e3, e4, e5);

        assertTrue(array[e1] < array[e2]);
        assertTrue(array[e2] < array[e3]);
        assertTrue(array[e3] < array[e4]);
        assertTrue(array[e4] < array[e5]);
    }
}
