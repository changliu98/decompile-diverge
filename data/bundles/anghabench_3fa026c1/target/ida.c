int __cdecl rdbEncodeInteger(__int64 value, unsigned __int8 *enc)
{
  if ( value < -128 || value > 127 )
  {
    if ( value < -32768 || value > 0x7FFF )
    {
      if ( value < (__int64)0xFFFFFFFF80000000LL || value > 0x7FFFFFFF )
      {
        return 0;
      }
      else
      {
        *enc = RDB_ENC_INT32 | ((_BYTE)RDB_ENCVAL << 6);
        *(_WORD *)(enc + 1) = value;
        enc[3] = BYTE2(value);
        enc[4] = BYTE3(value);
        return 5;
      }
    }
    else
    {
      *enc = RDB_ENC_INT16 | ((_BYTE)RDB_ENCVAL << 6);
      *(_WORD *)(enc + 1) = value;
      return 3;
    }
  }
  else
  {
    *enc = RDB_ENC_INT8 | ((_BYTE)RDB_ENCVAL << 6);
    enc[1] = value;
    return 2;
  }
}