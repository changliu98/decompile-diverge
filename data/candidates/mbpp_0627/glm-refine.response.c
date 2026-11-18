int __cdecl func0(int *array, int start, int end)
{
    // Base case: If the search range is invalid, return the first missing index.
    if (start > end)
        return end + 1;

    // If the current index doesn't match its value, the first mismatch is found.
    if (start != array[start])
        return start;

    // Find the midpoint of the current range.
    int mid = start + (end - start) / 2;

    // If the midpoint matches its value, the first mismatch must be to the right.
    if (array[mid] == mid)
        return func0(array, mid + 1, end);
    
    // Otherwise, the first mismatch is at or to the left of the midpoint.
    return func0(array, start, mid);
}