static int func0(struct kvm_vcpu *vcpu, char *data,
				unsigned int offset, unsigned int length)
{
	unsigned char *cdb = (unsigned char *)data;
	unsigned char opcode, flags, rw, rw_len;
	unsigned int i, j;
	unsigned long gpa;
	int ret;

	for (i = 0; i < length;) {
		opcode = cdb[i];
		flags = cdb[i + 1];
		rw = cdb[i + 2];
		rw_len = cdb[i + 3];
		i += 4;
		switch (opcode) {
		case 0x42:
			rw_len = rw;
			break;
		case 0x43:
			rw_len = rw;
			break;
		case 0x44:
			rw_len = rw;
			break;
		case 0x45:
			rw_len = rw;
			break;
		case 0x46:
			rw_len = rw;
			break;
		case 0x47:
			rw_len = rw;
			break;
		case 0x48:
			rw_len = rw;
			break;
		case 0x49:
			rw_len = rw;
			break;
		case 0x4a:
			rw_len = rw;
			break;
		case 0x4b:
			rw_len = rw;
			break;
		case 0x4c:
			rw_len = rw;
			break;
		case 0x4d:
			rw_len = rw;
			break;
		case 0x4e:
			rw_len = rw;
			break;
		case 0x4f:
			rw_len = rw;
			break;
		case 0x50:
			rw_len = rw;
			break;
		case 0x5