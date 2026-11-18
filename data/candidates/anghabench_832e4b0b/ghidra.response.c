bool csio_scsi_itnexus_loss_error(uint16_t error)

{
  uint16_t error_local;
  uint local_c;
  
  local_c = (uint)(error - 0x80 < 5);
  return local_c;
}