// Retrieves the current GPU processor ID and increments the base ID by the total number of CU counts.
// Returns the original GPU processor ID before the increment.
uint get_and_inc_gpu_processor_id(uint cu_count_increment)
{
    // Store the current low GPU processor ID in a temporary variable
    uint original_gpu_processor_id = current_gpu_processor_id;
    // Increment the low GPU processor ID by the total number of CU counts
    current_gpu_processor_id += cu_count_increment;
    // Return the original GPU processor ID
    return original_gpu_processor_id;
}