__attribute__((used)) static const char *ata_err_string(unsigned int err_mask)
{
	const char *err_string;

	if (err_mask & AC_ERR_HOST_BUS)
		err_string = "host bus error";
	else if (err_mask & AC_ERR_ATA_BUS)
		err_string = "ATA bus error";
	else if (err_mask & AC_ERR_TIMEOUT)
		err_string = "timeout";
	else if (err_mask & AC_ERR_HSM)
		err_string = "HSM violation";
	else if (err_mask & AC_ERR_SYSTEM)
		err_string = "internal error";
	else if (err_mask & AC_ERR_MEDIA)
		err_string = "media error";
	else if (err_mask & AC_ERR_INVALID)
		err_string = "invalid argument";
	else if (err_mask & AC_ERR_DEV)
		err_string = "device error";
	else if (err_mask & AC_ERR_NCQ)
		err_string = "NCQ error";
	else if (err_mask & AC_ERR_NODEV_HINT)
		err_string = "Polling detection error";
	else
		err_string = "unknown error";

	return err_string;
}