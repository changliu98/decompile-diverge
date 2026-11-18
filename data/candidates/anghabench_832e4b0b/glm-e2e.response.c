bool csio_scsi_itnexus_loss_error(unsigned short error_code) {
    if (error_code - 0x80 <= 4) {
        return true;
    } else {
        return false;
    }
}