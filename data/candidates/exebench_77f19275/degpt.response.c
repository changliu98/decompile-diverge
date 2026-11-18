void extract(char *instring,int inlength,int fieldno,int valueno,int subvalueno,int *outstart,
            int *outlength)

{
  bool bVar1;
  int subvalue_end_pos;
  int subvaluen2;
  int value_end_pos;
  int valuen2;
  int field_end_pos;
  int fieldn2;
  int start_pos;
  int *outstart_local;
  int subvalueno_local;
  int valueno_local;
  int fieldno_local;
  int inlength_local;
  char *instring_local;
  
  *outstart = 0;
  *outlength = 0;
  fieldno_local = fieldno;
  if (fieldno < 1) {
    if (fieldno < 0) {
      return;
    }
    if ((valueno == 0) && (subvalueno == 0)) {
      *outlength = inlength;
      return;
    }
    fieldno_local = 1;
  }
  start_pos = 0;
  for (fieldn2 = 1; fieldn2 < fieldno_local; fieldn2 = fieldn2 + 1) {
    while( true ) {
      bVar1 = false;
      if ((start_pos < inlength) && (bVar1 = true, instring[start_pos] == -0x35)) {
        bVar1 = instring[start_pos + 1] != -0x42;
      }
      if (!bVar1) break;
      start_pos = start_pos + 1;
    }
    if (inlength <= start_pos) {
      return;
    }
    start_pos = start_pos + 2;
  }
  field_end_pos = start_pos;
  while( true ) {
    bVar1 = false;
    if ((field_end_pos < inlength) && (bVar1 = true, instring[field_end_pos] == -0x35)) {
      bVar1 = instring[field_end_pos + 1] != -0x42;
    }
    if (!bVar1) break;
    field_end_pos = field_end_pos + 1;
  }
  valueno_local = valueno;
  if (valueno < 1) {
    if (valueno < 0) {
      return;
    }
    if (subvalueno == 0) {
      *outstart = start_pos;
      *outlength = field_end_pos - start_pos;
      return;
    }
    valueno_local = 1;
  }
  valuen2 = 1;
  while( true ) {
    if (valueno_local <= valuen2) {
      value_end_pos = start_pos;
      while( true ) {
        bVar1 = false;
        if ((value_end_pos < field_end_pos) && (bVar1 = true, instring[value_end_pos] == -0x35)) {
          bVar1 = instring[value_end_pos + 1] != -0x43;
        }
        if (!bVar1) break;
        value_end_pos = value_end_pos + 1;
      }
      if (subvalueno < 1) {
        if (subvalueno < 0) {
          return;
        }
        *outstart = start_pos;
        *outlength = value_end_pos - start_pos;
      }
      subvaluen2 = 1;
      while( true ) {
        if (subvalueno <= subvaluen2) {
          subvalue_end_pos = start_pos;
          while( true ) {
            bVar1 = false;
            if ((subvalue_end_pos < value_end_pos) &&
               (bVar1 = true, instring[subvalue_end_pos] == -0x35)) {
              bVar1 = instring[subvalue_end_pos + 1] != -0x44;
            }
            if (!bVar1) break;
            subvalue_end_pos = subvalue_end_pos + 1;
          }
          if (subvalue_end_pos < value_end_pos) {
            *outstart = start_pos;
            *outlength = subvalue_end_pos - start_pos;
          }
          else {
            *outstart = start_pos;
            *outlength = value_end_pos - start_pos;
          }
          return;
        }
        while( true ) {
          bVar1 = false;
          if ((start_pos < field_end_pos) && (bVar1 = true, instring[start_pos] == -0x35)) {
            bVar1 = instring[start_pos + 1] != -0x44;
          }
          if (!bVar1) break;
          start_pos = start_pos + 1;
        }
        if (inlength <= start_pos) break;
        start_pos = start_pos + 1;
        if (value_end_pos < start_pos) {
          return;
        }
        subvaluen2 = subvaluen2 + 1;
      }
      return;
    }
    while( true ) {
      bVar1 = false;
      if ((start_pos < inlength) && (bVar1 = true, instring[start_pos] == -0x35)) {
        bVar1 = instring[start_pos + 1] != -0x43;
      }
      if (!bVar1) break;
      start_pos = start_pos + 1;
    }
    if (inlength <= start_pos) break;
    start_pos = start_pos + 2;
    if (field_end_pos < start_pos) {
      return;
    }
    valuen2 = valuen2 + 1;
  }
  return;
}