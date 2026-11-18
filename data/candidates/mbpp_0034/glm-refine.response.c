// This function performs a binary search to find the first missing element 
// in a 1-indexed sorted array (where arr[i] is expected to be i + 1).
// Note: The original code contains an out-of-bounds read bug when mid == 0 
// (accessing arr[-1]). The semantics of the original code are preserved here.
int __cdecl find_missing_element(int *arr, int size)
{
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = (right + left) / 2;

        // If the current element is incorrect, but the previous one is correct,
        // then the missing element is exactly mid + 1.
        // This early return is essential because the else branch below would 
        // otherwise discard the right half and lose the answer.
        if (arr[mid] != mid + 1 && arr[mid - 1] == mid)
        {
            return mid + 1;
        }

        // If the current element is correct, the missing element is to the right.
        if (arr[mid] == mid + 1)
        {
            left = mid + 1;
        }
        else
        {
            // Otherwise, the missing element is to the left.
            right = mid - 1;
        }
    }

    return -1;
}