void __cdecl extract(
        char *instring,
        int inlength,
        int fieldno,
        int valueno,
        int subvalueno,
        int *outstart,
        int *outlength)
{
  int v7; // ecx
  bool v8; // [rsp+0h] [rbp-48h]
  bool v9; // [rsp+1h] [rbp-47h]
  bool v10; // [rsp+2h] [rbp-46h]
  bool v11; // [rsp+3h] [rbp-45h]
  bool v12; // [rsp+4h] [rbp-44h]
  bool v13; // [rsp+5h] [rbp-43h]
  bool v14; // [rsp+6h] [rbp-42h]
  bool v15; // [rsp+7h] [rbp-41h]
  bool v16; // [rsp+8h] [rbp-40h]
  bool v17; // [rsp+9h] [rbp-3Fh]
  bool v18; // [rsp+Ah] [rbp-3Eh]
  bool v19; // [rsp+Bh] [rbp-3Dh]
  int subvalue_end_pos; // [rsp+Ch] [rbp-3Ch]
  int subvaluen2; // [rsp+10h] [rbp-38h]
  int value_end_pos; // [rsp+14h] [rbp-34h]
  int valuen2; // [rsp+18h] [rbp-30h]
  int field_end_pos; // [rsp+1Ch] [rbp-2Ch]
  int fieldn2; // [rsp+20h] [rbp-28h]
  int start_pos; // [rsp+24h] [rbp-24h]
  int valuenoa; // [rsp+34h] [rbp-14h]
  int fieldnoa; // [rsp+38h] [rbp-10h]

  fieldnoa = fieldno;
  valuenoa = valueno;
  *outstart = 0;
  *outlength = 0;
  if ( fieldno <= 0 )
  {
    if ( fieldno < 0 )
      return;
    if ( !valueno && !subvalueno )
    {
      *outlength = inlength;
      return;
    }
    fieldnoa = 1;
  }
  start_pos = 0;
  for ( fieldn2 = 1; fieldn2 < fieldnoa; ++fieldn2 )
  {
    while ( 1 )
    {
      v19 = 0;
      if ( start_pos < inlength )
      {
        v18 = 1;
        if ( instring[start_pos] == -53 )
          v18 = instring[start_pos + 1] != -66;
        v19 = v18;
      }
      if ( !v19 )
        break;
      ++start_pos;
    }
    if ( start_pos >= inlength )
      return;
    start_pos += 2;
  }
  for ( field_end_pos = start_pos; ; ++field_end_pos )
  {
    v17 = 0;
    if ( field_end_pos < inlength )
    {
      v16 = 1;
      if ( instring[field_end_pos] == -53 )
        v16 = instring[field_end_pos + 1] != -66;
      v17 = v16;
    }
    if ( !v17 )
      break;
  }
  if ( valueno <= 0 )
  {
    if ( valueno < 0 )
      return;
    if ( !subvalueno )
    {
      *outstart = start_pos;
      *outlength = field_end_pos - start_pos;
      return;
    }
    valuenoa = 1;
  }
  for ( valuen2 = 1; valuen2 < valuenoa; ++valuen2 )
  {
    while ( 1 )
    {
      v15 = 0;
      if ( start_pos < inlength )
      {
        v14 = 1;
        if ( instring[start_pos] == -53 )
          v14 = instring[start_pos + 1] != -67;
        v15 = v14;
      }
      if ( !v15 )
        break;
      ++start_pos;
    }
    if ( start_pos >= inlength )
      return;
    start_pos += 2;
    if ( start_pos > field_end_pos )
      return;
  }
  for ( value_end_pos = start_pos; ; ++value_end_pos )
  {
    v13 = 0;
    if ( value_end_pos < field_end_pos )
    {
      v12 = 1;
      if ( instring[value_end_pos] == -53 )
        v12 = instring[value_end_pos + 1] != -67;
      v13 = v12;
    }
    if ( !v13 )
      break;
  }
  if ( subvalueno <= 0 )
  {
    if ( subvalueno < 0 )
      return;
    *outstart = start_pos;
    *outlength = value_end_pos - start_pos;
  }
  for ( subvaluen2 = 1; subvaluen2 < subvalueno; ++subvaluen2 )
  {
    while ( 1 )
    {
      v11 = 0;
      if ( start_pos < field_end_pos )
      {
        v10 = 1;
        if ( instring[start_pos] == -53 )
          v10 = instring[start_pos + 1] != -68;
        v11 = v10;
      }
      if ( !v11 )
        break;
      ++start_pos;
    }
    if ( start_pos >= inlength )
      return;
    if ( ++start_pos > value_end_pos )
      return;
  }
  for ( subvalue_end_pos = start_pos; ; ++subvalue_end_pos )
  {
    v9 = 0;
    if ( subvalue_end_pos < value_end_pos )
    {
      v8 = 1;
      if ( instring[subvalue_end_pos] == -53 )
        v8 = instring[subvalue_end_pos + 1] != -68;
      v9 = v8;
    }
    if ( !v9 )
      break;
  }
  *outstart = start_pos;
  if ( subvalue_end_pos < value_end_pos )
    v7 = subvalue_end_pos - start_pos;
  else
    v7 = value_end_pos - start_pos;
  *outlength = v7;
}