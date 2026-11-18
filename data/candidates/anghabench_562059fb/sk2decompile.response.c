static const char* selectOpName(SelectOp op) {
  switch (op) {
    case OP_UNION:
      return "UNION";
    case OP_INTERSECT:
      return "INTERSECT";
    case OP_EXCEPT:
      return "EXCEPT";
    case OP_UNION_ALL:
      return "UNION ALL";
  }
  return "UNION";
}