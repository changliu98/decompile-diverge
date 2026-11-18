int __cdecl hexagon_v6_op(
        RAnal *anal,
        RAnalOp *op,
        unsigned __int64 addr,
        const unsigned __int8 *buf,
        int len,
        RAnalOpMask mask)
{
  int size; // [rsp+0h] [rbp-40h]
  unsigned int data; // [rsp+4h] [rbp-3Ch]
  HexInsn hi; // [rsp+8h] [rbp-38h] BYREF
  RAnalOpMask maska; // [rsp+10h] [rbp-30h]
  int lena; // [rsp+14h] [rbp-2Ch]
  const unsigned __int8 *bufa; // [rsp+18h] [rbp-28h]
  unsigned __int64 addra; // [rsp+20h] [rbp-20h]
  RAnalOp *opa; // [rsp+28h] [rbp-18h]
  RAnal *anala; // [rsp+30h] [rbp-10h]

  anala = anal;
  opa = op;
  addra = addr;
  bufa = buf;
  lena = len;
  maska = mask;
  memset(&hi, 0, sizeof(hi));
  data = r_read_le32(bufa);
  size = hexagon_disasm_instruction(data, &hi, addra);
  opa->size = size;
  if ( size <= 0 )
    return size;
  opa->addr = addra;
  return hexagon_anal_instruction(&hi, opa);
}