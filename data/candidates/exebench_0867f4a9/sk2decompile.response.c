int compter_mots(char *chaine, size_t *taille_max) {
  int nb_mots = 0;
  int dans_chaine = 0;
  size_t taille_mot = 0;
  size_t taille_max_mot = 0;
  char *p;
  p = strchr(chaine, '\0') - 1;
  while (*p == ' ') {
    *p = '\0';
    p--;
  }
  p = chaine;
  while (*p == ' ') {
    p++;
  }
  if (*p != '\0') {
    nb_mots = 1;
  }
  while (*p != '\0') {
    if (*p == '"' || *p == '\'') {
      dans_chaine = !dans_chaine;
    } else if (*p == ' ' && !dans_chaine) {
      if (taille_mot > taille_max_mot) {
        taille_max_mot = taille_mot;
      }
      taille_mot = 0;
      nb_mots++;
      while (*p == ' ') {
        p++;
      }
      p--;
    } else {
      taille_mot++;
    }
    p++;
  }
  if (taille_mot > taille_max_mot) {
    taille_max_mot = taille_mot;
  }
  *taille_max = taille_max_mot;
  return nb_mots;
}