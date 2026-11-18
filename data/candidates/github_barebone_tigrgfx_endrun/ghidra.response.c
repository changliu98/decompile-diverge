void endrun(Save *s)

{
  uint uVar1;
  Save *s_local;
  
  s->runlen = s->runlen - 1;
  literal(s,s->prev);
  if (s->runlen < 0x43) {
    if (s->runlen < 0x23) {
      if (s->runlen < 0x13) {
        if (s->runlen < 0xb) {
          if (s->runlen < 3) {
            while (uVar1 = s->runlen, s->runlen = uVar1 - 1, uVar1 != 0) {
              literal(s,s->prev);
            }
          }
          else {
            encodelen(s,0x101,0,s->runlen - 3);
          }
        }
        else {
          encodelen(s,0x109,1,s->runlen - 0xb);
        }
      }
      else {
        encodelen(s,0x10d,2,s->runlen - 0x13);
      }
    }
    else {
      encodelen(s,0x111,3,s->runlen - 0x23);
    }
  }
  else {
    encodelen(s,0x115,4,s->runlen - 0x43);
  }
  return;
}