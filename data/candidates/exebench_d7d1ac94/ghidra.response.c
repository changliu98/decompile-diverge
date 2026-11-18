int imul_dbl(unsigned_long *m)

{
  undefined1 auVar1 [16];
  unsigned_long uVar2;
  int rc;
  unsigned_long *m_local;
  
  auVar1 = SEXT816((long)*m) * SEXT816((long)m[1]);
  uVar2 = *m * m[1];
  *m = uVar2;
  m[1] = auVar1._8_8_;
  return (uint)(SEXT816((long)uVar2) != auVar1);
}