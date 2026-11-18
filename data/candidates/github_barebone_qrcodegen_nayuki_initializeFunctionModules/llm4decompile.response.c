void initializeFunctionModules(int version, unsigned char *qrcode) {
 int qrsize, i, j, numAlign;
 unsigned char alignPatPos[7];

 qrsize = 17 + 4 * version;
 memset(qrcode, 0, (size_t)(((qrsize * qrsize) + 7) / 8 + 1));
 qrcode[0] = (unsigned char)qrsize;
 fillRectangle(6, 0, 1, qrsize, qrcode);
 fillRectangle(0, 6, qrsize, 1, qrcode);
 fillRectangle(0, 0, 9, 9, qrcode);
 fillRectangle(qrsize - 8, 0, 8, 9, qrcode);
 fillRectangle(0, qrsize - 8, 9, 8, qrcode);
 numAlign = getAlignmentPatternPositions(version, alignPatPos);
 for (i = 0; i < numAlign; i++) {
  for (j = 0; j < numAlign; j++) {
   if (!((i == 0 && j == 0) || (i == 0 && j == numAlign - 1) || (i == numAlign - 1 && j == 0)))
    fillRectangle(alignPatPos[i] - 2, alignPatPos[j] - 2, 5, 5, qrcode);
  }
 }
 if (version >= 7) {
  fillRectangle(qrsize - 11, 0, 3, 6, qrcode);
  fillRectangle(0, qrsize - 11, 6, 3, qrcode);
 }
}