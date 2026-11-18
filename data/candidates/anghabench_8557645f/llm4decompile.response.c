const char *
ata_err_string(int err_mask)
{
	const char *err_str;

	if (err_mask & AC_ERR_HOST_BUS)
		err_str = "host bus error";
	else if (err_mask & AC_ERR_ATA_BUS)
		err_str = "ATA bus error";
	else if (err_mask & AC_ERR_TIMEOUT)
		err_str = "timeout";
	else if (err_mask & AC_ERR_HSM)
		err_str = "HSM violation";
	else if (err_mask & AC_ERR_SYSTEM)
		err_str = "internal error";
	else if (err_mask & AC_ERR_MEDIA)
		err_str = "media error";
	else if (err_mask & AC_ERR_INVALID)
		err_str = "invalid argument";
	else if (err_mask & AC_ERR_DEV)
		err_str = "device error";
	else if (err_mask & AC_ERR_NCQ)
		err_str = "NCQ error";
	else if (err_mask & AC_ERR_NODEV_HINT)
		err_str = "Polling detection error";
	else
		err_str = "unknown error";

	return (err_str);
}