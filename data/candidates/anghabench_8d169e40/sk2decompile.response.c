unsigned char fsp_test_invert_cmd(unsigned char cmd) {
  if ((cmd == 0xe9) || (cmd == 0xee) || (cmd == 0xf2) || (cmd == 0xff))
    return (~cmd);
  else
    return (cmd);
}