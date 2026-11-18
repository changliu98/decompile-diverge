static int csio_scsi_itnexus_loss_error(int err) {
  switch (err) {
    case DID_IMM_RETRY:
    case DID_BUS_BUSY:
    case DID_NO_CONNECT:
    case DID_TRANSPORT_FAIL:
    case DID_ABORTED:
      return 1;
    default:
      return 0;
  }
}