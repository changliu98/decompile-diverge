char **func0(char *planet1, char *planet2, int *returnSize)
{
  char *planets[] = { "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
  int pos1 = -1;
  int pos2 = -1;
  int i;
  int temp;
  char **out;
  for (i = 0; i < 8; i++)
  {
    if (strcmp(planets[i], planet1) == 0)
      pos1 = i;
    if (strcmp(planets[i], planet2) == 0)
      pos2 = i;
  }
  if (pos1 == -1 || pos2 == -1 || pos1 == pos2)
  {
    *returnSize = 0;
    return ((void *)0);
  }
  if (pos1 > pos2)
  {
    temp = pos1;
    pos1 = pos2;
    pos2 = temp;
  }
  *returnSize = pos2 - pos1 - 1;
  if (*returnSize > 0)
  {
    out = (char **)malloc(((*returnSize)) * sizeof(char *));
    for (i = pos1 + 1; i < pos2; i++)
    {
      out[i - pos1 - 1] = planets[i];
    }
    return out;
  }
  else
  {
    *returnSize = 0;
    return ((void *)0);
  }
}