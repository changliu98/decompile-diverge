// Check if the SCSI IT-Nexus loss error code is within the valid range.
// Valid error codes are in the range [0x80, 0x84] (inclusive).
// The function returns true if the error code is between 0x80 and 0x84,
// and false otherwise.
bool csio_scsi_itnexus_loss_error(uint16_t error_code)
{
  // Subtract 0x80 from the error code and check if the result is less than 5.
  // This effectively checks if the error code is in the range [0x80, 0x84].
  return (uint)(error_code - 0x80 < 5);
}