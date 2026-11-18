static int rdp_write_logon_info_v2(FILE *fp, struct serial_struct *ss)
{
	unsigned long baud = 0, close_baud = 0;
	int retval = 1;

	if (!fseek(fp, 576, SEEK_SET))
		retval = 0;
	else
		goto out;

	put_unaligned(cpu_to_le32(1), fp);
	put_unaligned(cpu_to_le32(18), fp);
	put_unaligned(cpu_to_le32(ss->line), fp);

	baud = strnlen(ss->port, sizeof(ss->port));
	if (baud >= ULONG_MAX)
		retval = 0;
	else
		put_unaligned(cpu_to_le32((baud + 1) << 1), fp);

	close_baud = strnlen(ss->close_port, sizeof(ss->close_port));
	if (close_baud >= ULONG_MAX)
		retval = 0;
	else
		put_unaligned(cpu_to_le32((close_baud + 1) << 1), fp);

	put_unaligned(cpu_to_le32(558), fp);

	if (fwrite(ss->port, baud + 1, ss->line, fp) < 0)
		retval = 0;
	else if (fwrite(ss->close_port, close_baud + 1, ss->line, fp) < 0)
		retval = 0;
	else
		retval = 1;

out:
	return retval;
}