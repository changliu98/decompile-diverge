void __cdecl endrun(Save *s)
{
  // Emit the first literal of the run
  --s->runlen;
  literal(s, s->prev);

  // Encode the remaining run length using variable-length codes
  if (s->runlen < 3)
  {
    // Run length 0 to 2: Emit as raw literals
    while (s->runlen > 0)
    {
      s->runlen--;
      literal(s, s->prev);
    }
  }
  else if (s->runlen < 0xB)
  {
    // Run length 3 to 10: 8 possible values (0x101 base, 0 extra bits)
    encodelen(s, 0x101u, 0, s->runlen - 3);
  }
  else if (s->runlen < 0x13)
  {
    // Run length 11 to 18: 8 possible values (0x109 base, 1 extra bit)
    encodelen(s, 0x109u, 1u, s->runlen - 11);
  }
  else if (s->runlen < 0x23)
  {
    // Run length 19 to 34: 16 possible values (0x10D base, 2 extra bits)
    encodelen(s, 0x10Du, 2u, s->runlen - 19);
  }
  else if (s->runlen < 0x43)
  {
    // Run length 35 to 66: 32 possible values (0x111 base, 3 extra bits)
    encodelen(s, 0x111u, 3u, s->runlen - 35);
  }
  else
  {
    // Run length >= 67: 64+ possible values (0x115 base, 4 extra bits)
    encodelen(s, 0x115u, 4u, s->runlen - 67);
  }
}