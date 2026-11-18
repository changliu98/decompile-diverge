void *AcquireBilateralTLS(size_t count, size_t num_threads, size_t quantum) {
    void **tls_array;
    size_t i;
    void *ret;

    // Allocate array of pointers (count + 1 elements, 8 bytes each)
    tls_array = (void **)AcquireQuantumMemory(count + 1, 8);
    
    if (tls_array == NULL) {
        ret = NULL;
    } else {
        // Zero out the allocated memory
        memset(tls_array, 0, count * 8);
        
        i = 0;
        while (i <= count) {
            // Allocate quantum memory for each thread
            tls_array[i] = AcquireQuantumMemory(num_threads, quantum * 8);
            
            if (tls_array[i] == NULL) {
                // Cleanup and return on failure
                ret = DestroyBilateralTLS(count, tls_array);
                return ret;
            }
            i++;
        }
        ret = tls_array;
    }
    
    return ret;
}