const char *__cdecl selectOpName(int id)
{
  switch ( id )
  {
    case 128:
      return "INTERSECT";
    case 129:
      return "EXCEPT";
    case 130:
      return "UNION ALL";
  }
  return "UNION";
}