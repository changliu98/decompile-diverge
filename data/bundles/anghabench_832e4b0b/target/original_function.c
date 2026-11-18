bool
csio_scsi_itnexus_loss_error(uint16_t error)
{
	switch (error) {
	case FW_ERR_LINK_DOWN:
	case FW_RDEV_NOT_READY:
	case FW_ERR_RDEV_LOST:
	case FW_ERR_RDEV_LOGO:
	case FW_ERR_RDEV_IMPL_LOGO:
		return 1;
	}
	return 0;
}