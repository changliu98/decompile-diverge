static void func0(struct dasd_uid *uid, char *buf)
{
	buf[0] = uid->type;
	buf[1] = uid->format;
	buf[2] = uid->compression;
	buf[3] = uid->issuer;
	buf[4] = uid->serial_number[0];
	buf[5] = uid->serial_number[1];
	buf[6] = uid->serial_number[2];
	buf[7] = uid->serial_number[3];
	buf[8] = uid->serial_number[4];
	buf[9] = uid->serial_number[5];
	buf[10] = uid->serial_number[6];
	buf[11] = uid->serial_number[7];
	buf[12] = uid->serial_number[8];
	buf[13] = uid->serial_number[9];
	buf[14] = uid->serial_number[10];
	buf[15] = uid->serial_number[11];
}