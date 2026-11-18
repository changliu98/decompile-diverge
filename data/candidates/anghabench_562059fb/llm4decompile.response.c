const char *selectOpName(int op){
  switch( op ){
    case SQLITE_INTERSECT: return "INTERSECT";
    case SQLITE_UNION: return "UNION";
    case SQLITE_EXCEPT: return "EXCEPT";
    case SQLITE_UNION_ALL: return "UNION ALL";
    default: return "UNION";
  }
}