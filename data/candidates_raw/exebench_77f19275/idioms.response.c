void get_subvalue(char *instring, int inlength, int fieldno, int valueno, int subvalueno, int *outstart, int *outlength)
{
  int start_pos; int fieldn2; int field_end_pos;
  int valuen2; int value_end_pos; int subvaluen2; int subvalue_end_pos;
  int fieldnoa = fieldno; int valuenoa = valueno;
  int i;
  *outstart = 0;
  *outlength = 0;
  if (fieldno <= 0)
  {
    if (fieldno < 0)
      return;
    if (valueno == 0 && subvalueno == 0)
    {
      *outlength = inlength;
      return;
    }
    fieldnoa = 1;
  }
  start_pos = 0;
  for (fieldn2 = 1; fieldn2 < fieldnoa; fieldn2++)
  {
    while (1)
    {
      int is_not_field_separator = (start_pos < inlength &&
        ((instring[start_pos] == (0xe9)) ?
        (instring[start_pos + 1] != (0xe2)) :
        1));
      if (!is_not_field_separator)
        break;
      start_pos++;
    }
    if (start_pos >= inlength)
      return;
    start_pos += 2;
  }
  for (field_end_pos = start_pos; ; field_end_pos++)
  {
    int is_not_field_separator = (field_end_pos < inlength &&
      ((instring[field_end_pos] == (0xe9)) ?
      (instring[field_end_pos + 1] != (0xe2)) :
      1));
    if (!is_not_field_separator)
      break;
  }
  if (valueno <= 0)
  {
    if (valueno < 0)
      return;
    if (subvalueno == 0)
    {
      *outstart = start_pos;
      *outlength = field_end_pos - start_pos;
      return;
    }
    valuenoa = 1;
  }
  for (valuen2 = 1; valuen2 < valuenoa; valuen2++)
  {
    while (1)
    {
      int is_not_value_separator = (start_pos < inlength &&
        ((instring[start_pos] == (0xe9)) ?
        (instring[start_pos + 1] != (0xe3)) :
        1));
      if (!is_not_value_separator)
        break;
      start_pos++;
    }
    if (start_pos >= inlength)
      return;
    start_pos += 2;
    if (start_pos > field_end_pos)
      return;
  }
  for (value_end_pos = start_pos; ; value_end_pos++)
  {
    int is_not_value_separator = (value_end_pos < field_end_pos &&
      ((instring[value_end_pos] == (0xe9)) ?
      (instring[value_end_pos + 1] != (0xe3)) :
      1));
    if (!is_not_value_separator)
      break;
  }
  if (subvalueno <= 0)
  {
    if (subvalueno < 0)
      return;
    *outstart = start_pos;
    *outlength = value_end_pos - start_pos;
  }
  for (subvaluen2 = 1; subvaluen2 < subvalueno; subvaluen2++)
  {
    while (1)
    {
      int is_not_subvalue_separator = (start_pos < field_end_pos &&
        ((instring[start_pos] == (0xe9)) ?
        (instring[start_pos + 1] != (0xe4)) :
        1));
      if (!is_not_subvalue_separator)
        break;
      start_pos++;
    }
    if (start_pos >= inlength)
      return;
    start_pos += 2;
    if (start_pos > value_end_pos)
      return;
  }
  for (subvalue_end_pos = start_pos; ; subvalue_end_pos++)
  {
    int is_not_subvalue_separator = (subvalue_end_pos < value_end_pos &&
      ((instring[subvalue_end_pos] == (0xe9)) ?
      (instring[subvalue_end_pos + 1] != (0xe4)) :
      1));
    if (!is_not_subvalue_separator)
      break;
  }
  *outstart = start_pos;
  *outlength = (subvalue_end_pos < value_end_pos) ?
    (subvalue_end_pos - start_pos) :
    (value_end_pos - start_pos);
}