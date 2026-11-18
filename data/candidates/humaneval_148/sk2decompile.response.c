char **func0(char *start, char *end, int *size) {
  char *planets[] = {"Mercury", "Venus",  "Earth",  "Mars",  "Jupiter",
                     "Saturn",  "Uranus", "Neptune"};
  int start_index = -1, end_index = -1;
  for (int i = 0; i < 8; i++) {
    if (!strcmp(planets[i], start)) start_index = i;
    if (!strcmp(planets[i], end)) end_index = i;
  }
  if (start_index == -1 || end_index == -1 || start_index == end_index) {
    *size = 0;
    return NULL;
  }
  if (start_index > end_index) {
    int temp = start_index;
    start_index = end_index;
    end_index = temp;
  }
  *size = end_index - start_index - 1;
  if (*size <= 0) {
    *size = 0;
    return NULL;
  }
  char **result = malloc(sizeof(char *) * *size);
  for (int i = start_index + 1; i < end_index; i++) {
    result[i - start_index - 1] = planets[i];
  }
  return result;
}