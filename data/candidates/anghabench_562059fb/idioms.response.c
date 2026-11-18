char *selectOpName(int op)
{
  switch (op) {
    case 128:
      return "INTERSECT";
    case 129:
      return "EXCEPT";
    case 130:
      return "UNION ALL";
  }
  return "UNION";
}