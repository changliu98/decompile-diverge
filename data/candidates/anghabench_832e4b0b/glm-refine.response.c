bool __cdecl csio_scsi_itnexus_loss_error(uint16_t error)
{
    return error >= 128 && error <= 132;
}