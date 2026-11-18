bool __cdecl csio_scsi_itnexus_loss_error(uint16_t error)
{
  return (unsigned int)error - 128 <= 4;
}