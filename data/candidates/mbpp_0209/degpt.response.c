void func0(int *maxHeap, int heapSize, int thresholdValue, int *resultArray)
{
    // Build a max-heap from the input array
    buildHeap(maxHeap, heapSize);
    
    // If the root of the heap is less than or equal to 'a'
    if (*maxHeap <= thresholdValue) {
        // Update the root element to 'a'
        *maxHeap = thresholdValue;
        
        // Restore the heap property by heapifying from the root
        heapify(maxHeap, heapSize, 0);
        
        // Copy the modified heap to the output array
        for (int index = 0; index < heapSize; index++) {
            resultArray[index] = maxHeap[index];
        }
    }
}