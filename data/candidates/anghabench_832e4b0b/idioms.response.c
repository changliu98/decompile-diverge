static int csio_scsi_itnexus_loss_error(int error)
{
    return (error - 128 < 5);
}