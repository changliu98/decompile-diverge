void __cdecl Swap8Bytes(char *bytes)
{
  char t; // [rsp+1h] [rbp-9h]
  char ta; // [rsp+1h] [rbp-9h]
  char tb; // [rsp+1h] [rbp-9h]
  char tc; // [rsp+1h] [rbp-9h]

  t = *bytes;
  *bytes = bytes[7];
  bytes[7] = t;
  ta = bytes[1];
  bytes[1] = bytes[6];
  bytes[6] = ta;
  tb = bytes[2];
  bytes[2] = bytes[5];
  bytes[5] = tb;
  tc = bytes[3];
  bytes[3] = bytes[4];
  bytes[4] = tc;
}