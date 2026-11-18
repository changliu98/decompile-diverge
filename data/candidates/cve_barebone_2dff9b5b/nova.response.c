static int decode_rt_routing_info(struct pt_regs *regs, unsigned long address,
			     unsigned long error_code, int si_code)
{
	unsigned char ar_opc[8];
	unsigned char ar_opcode;
	unsigned char ar_opcode_mask;
	unsigned long ar_opcode_offset;
	unsigned long ar_opcode_shift;
	unsigned long ar_opcode_value;
	unsigned long ar_opcode_value_mask;
	unsigned long ar_opcode_value_shift;
	unsigned long ar_opcode_value_offset;
	unsigned long ar_opcode_value_offset_mask;
	unsigned long ar_opcode_value_offset_shift;
	unsigned long ar_opcode_value_offset_value;
	unsigned long ar_opcode_value_offset_value_mask;
	unsigned long ar_opcode_value_offset_value_shift;
	unsigned long ar_opcode_value_offset_value_value;
	unsigned long ar_opcode_value_offset_value_value_mask;
	unsigned long ar_opcode_value_offset_value_value_shift;
	unsigned long ar_opcode_value_offset_value_value_value;
	unsigned long ar_opcode_value_offset_value_value_value_mask;
	unsigned long ar_opcode_value_offset_value_value_value_shift;
	unsigned long ar_opcode_value_offset_value_value_value_value;
	unsigned long ar_opcode_value_offset_value_value_value_value_mask;
	unsigned long ar_opcode_value_offset_value_value_value_value_shift;
	unsigned long ar_opcode_value_offset_value_value_value_value_value;
	unsigned long ar_opcode_value_offset_value_value_value_value_value_mask;
	unsigned long ar_opcode_value_offset_value_value_value_value_value_shift;
	unsigned long ar_opcode_value_offset_value_value_value_value_value_value;
	unsigned long ar_opcode_value_offset_value