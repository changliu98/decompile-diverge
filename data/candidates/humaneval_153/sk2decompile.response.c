void _get_best_extension(const char *filename, const char **extensions,
                         int n_extensions, char *out) {
  int best_score = -1000;
  const char *best_extension = NULL;
  for (int i = 0; i < n_extensions; i++) {
    const char *extension = extensions[i];
    int score = 0;
    for (int j = 0; extension[j]; j++) {
      char c = extension[j];
      if (c >= 'A' && c <= 'Z') score++;
      if (c >= 'a' && c <= 'z') score--;
    }
    if (score > best_score) {
      best_score = score;
      best_extension = extensions[i];
    }
  }
  sprintf(out, "%s.%s", filename, best_extension);
}