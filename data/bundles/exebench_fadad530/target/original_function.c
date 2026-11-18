void
ToIUPAC(char *seq, int is_aseq)
{
  if (is_aseq) {
    for (; *seq != '\0'; seq++)
      if (strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *seq) == NULL && ! ((*seq) == ' ' || (*seq) == '.' || (*seq) == '_' || (*seq) == '-' || (*seq) == '~')) *seq = 'N';
  } else {
    for (; *seq != '\0'; seq++)
      if (strchr("ACGTUNRYMKSWHBVDacgtunrymkswhbvd", *seq) == NULL) *seq = 'N';
  }
}