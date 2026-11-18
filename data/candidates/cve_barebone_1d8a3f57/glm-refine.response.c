Optimized and annotated function
int __cdecl stszin(int size)
{
  uint32_t current_size;         // Size of the current chunk/sample
  uint32_t current_offset;       // Running total offset of chunk sizes
  uint32_t i;                    // Loop counter

  // Skip the first two 32-bit fields (likely 'version' and 'flags' from the MP4 atom header)
  u32in();
  u32in();
  
  // Read the number of entries (sample/chunk count)
  dword_40B0 = u32in();
  
  // Allocate an array of 32-bit unsigned integers to store cumulative offsets.
  // Size is (count + 1) * 4 bytes. The first element will act as a base offset of 0.
  qword_40A8 = (uint64_t)malloc(4ULL * (uint64_t)(dword_40B0 + 1));
  if ( !qword_40A8 )
    return -1;
    
  current_offset = 0;
  *(uint32_t *)qword_40A8 = 0;  // Initialize the first offset to 0
  
  // Iterate through each entry
  for ( i = 0; i < dword_40B0; ++i )
  {
    current_size = u32in();
    current_offset += current_size;
    
    // Track the maximum chunk size seen so far
    if ( dword_40B8 < current_size )
      dword_40B8 = current_size;
      
    // Store the cumulative offset for the current entry
    *(uint32_t *)(qword_40A8 + 4ULL * (i + 1)) = current_offset;
    
    // Overflow check: if the new offset is less than the previous offset, 
    // a 32-bit unsigned integer wraparound occurred.
    if ( current_offset < *(uint32_t *)(qword_40A8 + 4ULL * i) )
      return -1;
  }
  
  return size;
}