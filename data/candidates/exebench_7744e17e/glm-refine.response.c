void __cdecl ee_readn(unsigned int command_ee, unsigned int *result_ee)
{
  // Check if the command exceeds the valid boundary (0x80)
  if ( command_ee <= 0x80 )
  {
    // Success path: Construct the 64-bit response.
    // High 32-bits (result_ee[0]) = 0x00000000 (Status: OK)
    // Low 32-bits  (result_ee[1]) = (command_ee << 8) | 0x38000
    *result_ee       = 0; 
    result_ee[1]     = (command_ee << 8) + 0x38000; // 229376 == 0x38000
  }
  else
  {
    // Error path: Command out of bounds.
    // High 32-bits (result_ee[0]) = 502 (0x1F6) (Status: Error / Invalid Command)
    // Low 32-bits  (result_ee[1]) = Unmodified (contains whatever was previously in memory)
    *result_ee       = 502; 
  }
}