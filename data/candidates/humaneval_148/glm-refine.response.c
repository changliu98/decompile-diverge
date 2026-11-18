#include <string.h>
#include <stdlib.h>

// Assuming off_3D60 is an array of planet names defined elsewhere in the binary
extern const char *off_3D60[8];

char **get_planets_between(const char *planet1, const char *planet2, int *returnSize)
{
  const char *planets[8];
  int pos1 = -1;
  int pos2 = -1;
  int temp, i;
  char **out;

  // Initialize the local array of planet names
  memcpy(planets, off_3D60, sizeof(planets));

  // Find the indices of the two given planets
  for (i = 0; i < 8; ++i)
  {
    if (strcmp(planets[i], planet1) == 0)
      pos1 = i;
    if (strcmp(planets[i], planet2) == 0)
      pos2 = i;
  }

  // If either planet is not found, or they are the same planet, return empty
  if (pos1 == -1 || pos2 == -1 || pos1 == pos2)
  {
    *returnSize = 0;
    return NULL;
  }

  // Ensure pos1 is the smaller index and pos2 is the larger index
  if (pos1 > pos2)
  {
    temp = pos1;
    pos1 = pos2;
    pos2 = temp;
  }

  // Calculate the number of planets between them
  *returnSize = pos2 - pos1 - 1;

  // If there are planets between them, allocate memory and populate the array
  if (*returnSize > 0)
  {
    out = (char **)malloc(sizeof(char *) * (*returnSize));
    for (i = pos1 + 1; i < pos2; ++i)
    {
      out[i - pos1 - 1] = (char *)planets[i];
    }
    return out;
  }
  else
  {
    // Planets are adjacent, no planets in between
    *returnSize = 0;
    return NULL;
  }
}