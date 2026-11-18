// Retrieves the float value at index i from the memory-mapped address array.
// Parameters:
//   addr - Pointer to the memory-mapped float array.
//   i    - Index of the element to retrieve.
// Returns:
//   The float value at the specified index.
float mmapGet(float *memory_map, long index)
{
    return memory_map[index];
}