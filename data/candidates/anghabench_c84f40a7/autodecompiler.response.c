static int
byte_row_gbk1(int opcode)
{
 int op;

 if ((opcode >= 0x82) && (opcode <= 0xff))
  op = opcode - 0x82;
 else
  op = -1;

 return (op);
}