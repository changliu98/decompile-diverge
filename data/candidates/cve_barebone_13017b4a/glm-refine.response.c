int __cdecl jpeg_size(uint8_t *data, uint32_t data_size, int *width, int *height)
{
  uint16_t block_length;
  uint32_t i;

  // Check minimum size for SOI + APP0 markers (4 bytes)
  if (data_size > 3 && data[0] == 0xFF && data[1] == JPEG_SOI && data[2] == 0xFF && data[3] == JPEG_APP0)
  {
    i = 4; // Skip SOI (2 bytes) and APP0 marker (2 bytes)
    
    // Check minimum size for JFIF header (11 bytes) and validate "JFIF\0" identifier
    if (data_size > 0xA && data[6] == 'J' && data[7] == 'F' && data[8] == 'I' && data[9] == 'F' && data[10] == 0)
    {
      block_length = BE16(&data[4]); // Read length of APP0 block
      
      // Iterate through JPEG markers
      while (i < data_size)
      {
        uint32_t next_marker_pos = i + block_length;
        
        // Boundary check: ensure we can read at least the marker and its length (2 bytes)
        if (next_marker_pos + 1 >= data_size)
          return -1;
          
        // Every JPEG segment must start with 0xFF
        if (data[next_marker_pos] != 0xFF)
          return -1;
          
        // Check if we found the Start Of Frame (SOF0) marker
        if (data[next_marker_pos + 1] == JPEG_SOF0)
        {
          // SOF0 payload: [length(2)] [precision(1)] [height(2)] [width(2)]
          *height = BE16(&data[next_marker_pos + 5]);
          *width  = BE16(&data[next_marker_pos + 7]);
          return 0; // Success
        }
        
        // Move to the next marker payload (skip 0xFF and marker byte)
        i = next_marker_pos + 2;
        block_length = BE16(&data[i]); // Read length of the current block
      }
    }
  }
  
  return -1; // Invalid JPEG or dimensions not found
}