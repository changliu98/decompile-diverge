static const char *ata_err_string(unsigned int err) {
  if (err & ATA_EBUS) return "host bus error";
  if (err & ATA_DEV) return "ATA bus error";
  if (err & ATA_TIMEOUT) return "timeout";
  if (err & ATA_HSM) return "HSM violation";
  if (err & ATA_ERR) return "internal error";
  if (err & ATA_MEDIA) return "media error";
  if (err & ATA_INVALID) return "invalid argument";
  if (err & ATA_DEV_ERR) return "device error";
  if (err & ATA_NCQ_ERR) return "NCQ error";
  if (err & ATA_PDEV_ERR) return "Polling detection error";
  return "unknown error";
}