/*
 * ata_err_string - Convert ATA error mask to human-readable string
 *
 * @err_mask: Bitmask of ATA error codes (AC_ERR_* flags)
 *
 * Returns a static string describing the first matching error condition
 * found in the error mask. If no specific error bit is set, returns
 * "unknown error".
 *
 * The function checks error flags in a specific priority order:
 * 1. Host bus errors
 * 2. ATA bus errors
 * 3. Timeouts
 * 4. Host State Machine (HSM) violations
 * 5. Internal/system errors
 * 6. Media errors
 * 7. Invalid arguments
 * 8. Device errors
 * 9. NCQ (Native Command Queuing) errors
 * 10. Polling detection errors (no device detected)
 */
char * ata_err_string(uint error_mask)
{
	/* Check for host bus error */
	if (error_mask & AC_ERR_HOST_BUS) return "host bus error";
	
	/* Check for ATA bus error */
	if (error_mask & AC_ERR_ATA_BUS) return "ATA bus error";
	
	/* Check for timeout error */
	if (error_mask & AC_ERR_TIMEOUT) return "timeout";
	
	/* Check for Host State Machine violation */
	if (error_mask & AC_ERR_HSM) return "HSM violation";
	
	/* Check for internal/system error */
	if (error_mask & AC_ERR_SYSTEM) return "internal error";
	
	/* Check for media error */
	if (error_mask & AC_ERR_MEDIA) return "media error";
	
	/* Check for invalid argument error */
	if (error_mask & AC_ERR_INVALID) return "invalid argument";
	
	/* Check for device error */
	if (error_mask & AC_ERR_DEV) return "device error";
	
	/* Check for NCQ (Native Command Queuing) error */
	if (error_mask & AC_ERR_NCQ) return "NCQ error";
	
	/* Check for polling detection error (no device detected) */
	if (error_mask & AC_ERR_NODEV_HINT) return "Polling detection error";
	
	/* Return default message if no specific error bit is set */
	return "unknown error";
}