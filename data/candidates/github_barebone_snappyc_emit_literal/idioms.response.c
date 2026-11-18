char *emit_literal(char *op, char *literal, int len, _Bool allow_fast_path)
{
  char *end = op + (len - 1);
  if (end < (op + 60 - 1))
  {
    *op++ = (len - 1) << 2;
    if (allow_fast_path && len <= 16)
    {
      copy_literal(literal, op);
      copy_literal(literal + 8, op + 9);
      return op + (len);
    }
  }
  else
  {
    int count = 0;
    end = op + 1;
    while (end < (op + 60))
    {
      *end++ = (len - 1);
      len = (len - 1) / 256;
      count++;
    }
    ((void) sizeof ((!(!(count >= 1))) ? 1 : 0), __extension__ ({ if (!(!(count >= 1))) ; else __assert_fail ("!(!(count >= 1))", "func.c", 583, __extension__ __PRETTY_FUNCTION__); }));
    ((void) sizeof ((!(!(count <= 4))) ? 1 : 0), __extension__ ({ if (!(!(count <= 4))) ; else __assert_fail ("!(!(count <= 4))", "func.c", 584, __extension__ __PRETTY_FUNCTION__); }));
    *op = (count + (60 - 1)) << 2;
  }
  end = op + 1;
  *op = (len - 1) << 2;
  copy_literal(end, literal);
  return end + (len);
}