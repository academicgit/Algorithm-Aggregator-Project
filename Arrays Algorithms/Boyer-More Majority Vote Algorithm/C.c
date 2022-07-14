// Implement the Boyer-More Majority Vote Algorithm in C
#include <stdio.h>
// Function to find majority element present in a given array
int MajorityElement(int nums[], int n)
{
    // 'm stores the majority element'
    int m;
    // initialize i to 0
    int i = 0;
    // do for each element 'nums[j]' in the array
    for (int j = 0; j < n; j++)
    {
        // if i is 0, then set m to nums[j]
        if (i == 0)
            m = nums[j];
        // if nums[j] is same as m, then increment i
        if (nums[j] == m)
            i++;
        // else decrement i
        else
            i--;
    }
    // return m
    return m;
}
// Driver program to test above function
int main()
{
    // array of integers
    int nums[] = { 1, 8, 7, 4, 1, 7, 7, 7, 7, 7, 7 };
    // size of array
    int n = sizeof(nums) / sizeof(nums[0]);
    // print the majority element
    printf("Majority element is %d", MajorityElement(nums, n));
    return 0;
}