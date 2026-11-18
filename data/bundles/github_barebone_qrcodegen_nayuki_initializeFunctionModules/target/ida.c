void __cdecl initializeFunctionModules(int version, uint8_t *qrcode)
{
  int j; // [rsp+8h] [rbp-28h]
  int i; // [rsp+Ch] [rbp-24h]
  int numAlign; // [rsp+10h] [rbp-20h]
  uint8_t alignPatPos[7]; // [rsp+15h] [rbp-1Bh] BYREF
  int qrsize; // [rsp+1Ch] [rbp-14h]
  uint8_t *qrcodea; // [rsp+20h] [rbp-10h]
  int versiona; // [rsp+2Ch] [rbp-4h]

  versiona = version;
  qrcodea = qrcode;
  qrsize = 4 * version + 17;
  memset(qrcode, 0, (qrsize * qrsize + 7) / 8 + 1);
  *qrcode = qrsize;
  fillRectangle(6, 0, 1, qrsize, qrcodea);
  fillRectangle(0, 6, qrsize, 1, qrcodea);
  fillRectangle(0, 0, 9, 9, qrcodea);
  fillRectangle(qrsize - 8, 0, 8, 9, qrcodea);
  fillRectangle(0, qrsize - 8, 9, 8, qrcodea);
  numAlign = getAlignmentPatternPositions(versiona, alignPatPos);
  for ( i = 0; i < numAlign; ++i )
  {
    for ( j = 0; j < numAlign; ++j )
    {
      if ( (i || j) && (i || j != numAlign - 1) && (i != numAlign - 1 || j) )
        fillRectangle(alignPatPos[i] - 2, alignPatPos[j] - 2, 5, 5, qrcodea);
    }
  }
  if ( versiona >= 7 )
  {
    fillRectangle(qrsize - 11, 0, 3, 6, qrcodea);
    fillRectangle(0, qrsize - 11, 6, 3, qrcodea);
  }
}