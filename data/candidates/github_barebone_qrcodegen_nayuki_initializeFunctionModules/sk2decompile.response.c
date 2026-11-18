static void initializeFunctionModules(int version, unsigned char *function) {
  int functionSize = version * 4 + 17;
  int x, y;
  int numAlign;
  unsigned char align[7];
  memset(function, 0, (functionSize * functionSize + 7) / 8 + 1);
  function[0] = (unsigned char)functionSize;
  fillRectangle(6, 0, 1, functionSize, function);
  fillRectangle(0, 6, functionSize, 1, function);
  fillRectangle(0, 0, 9, 9, function);
  fillRectangle(functionSize - 8, 0, 8, 9, function);
  fillRectangle(0, functionSize - 8, 9, 8, function);
  numAlign = getAlignmentPatternPositions(version, align);
  for (y = 0; y < numAlign; y++) {
    for (x = 0; x < numAlign; x++) {
      if (y == 0 && x == 0) {
        continue;
      }
      if (y == 0 && x == numAlign - 1) {
        continue;
      }
      if (y == numAlign - 1 && x == 0) {
        continue;
      }
      fillRectangle(align[y] - 2, align[x] - 2, 5, 5, function);
    }
  }
  if (version >= 7) {
    fillRectangle(functionSize - 11, 0, 3, 6, function);
    fillRectangle(0, functionSize - 11, 6, 3, function);
  }
}