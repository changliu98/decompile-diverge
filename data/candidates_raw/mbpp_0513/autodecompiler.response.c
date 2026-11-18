char** add_tuple_to_strings(int *tuple, int cardinality, char *sep) {
  char **res = malloc(2*cardinality*sizeof(char*));
  int i, j;
  for(j=0, i=0; i<cardinality; i++) {
    asprintf(&res[j++], "%d", tuple[i]);
    res[j++] = sep;
  }
  return res;
}