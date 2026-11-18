char * selectOpName(int id)

{
  char *z;
  int id_local;
  
  if (id == 0x80) {
    z = "INTERSECT";
  }
  else if (id == 0x81) {
    z = "EXCEPT";
  }
  else if (id == 0x82) {
    z = "UNION ALL";
  }
  else {
    z = "UNION";
  }
  return z;
}