int
csio_scsi_itnexus_loss_error(uint16_t error)
{
	switch (error) {
	case SAM_STAT_CHECK_CONDITION:
	case SAM_STAT_CONDITION_GOOD:
	case SAM_STAT_RESERVATION_CONFLICT:
	case SAM_STAT_TASK_SET_FULL:
	case SAM_STAT_BUSY:
		return 1;
	default:
		return 0;
	}
}