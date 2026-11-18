static int
get_scsi_op_code(int opcode)
{
 int op;

 if ((opcode >= 0x82) && (opcode <= 0xff))
  op = opcode - 0x82;
 else
  op = -1;

 return (op);
}