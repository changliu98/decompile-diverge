// Recursive function to determine if a subset of the first n elements of 'set' sums to 'sum'
// Parameters:
//   set - pointer to the array of integers
//   n   - number of elements to consider from the array
//   sum - target sum to achieve
// Returns:
//   true if a subset exists that sums to 'sum', false otherwise
_Bool hasSubsetSum(int *numbers, int count, int targetSum)
{
    // Base case: if the target sum is 0, an empty subset satisfies the condition
    if (targetSum == 0) return true;
    
    // Base case: if no elements are left to consider but sum is not 0, no subset exists
    if (count == 0) return false;
    
    // If the current element is greater than the remaining sum, it cannot be included
    if (targetSum < numbers[count - 1]) return hasSubsetSum(numbers, count - 1, targetSum);
    
    // Recursive case: either exclude the current element or include it
    return hasSubsetSum(numbers, count - 1, targetSum) || hasSubsetSum(numbers, count - 1, targetSum - numbers[count - 1]);
}