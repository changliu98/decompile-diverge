static int
func0(char *class_name, char **extensions, int ext_count,
                   char *best_ext)
{
    int i, j;
    int max_strength = -1000;
    char *best = NULL;

    for (i = 0;; i++) {
        char *ext, c;
        int strength;

        if (i >= ext_count) break;
        ext = extensions[i];
        strength = 0;
        for (j = 0;; j++) {
            if (!ext[j]) {
                if (strength > max_strength) {
                    max_strength = strength;
                    best = ext;
                }
                break;
            }
            c = ext[j];
            switch (c) {
              case 'A': case 'B': case 'C': case 'D': case 'E':
              case 'F': case 'G': case 'H': case 'I': case 'J':
              case 'K': case 'L': case 'M': case 'N': case 'O':
              case 'P': case 'Q': case 'R': case 'S': case 'T':
              case 'U': case 'V': case 'W': case 'X': case 'Y':
              case 'Z':
                strength++;
                break;
              case 'a': case 'b': case 'c': case 'd': case 'e':
              case 'f': case 'g': case 'h': case 'i': case 'j':
              case 'k': case 'l': case 'm': case 'n': case 'o':
              case 'p': case 'q': case 'r': case 's': case 't':
              case 'u': case 'v': case 'w': case 'x': case 'y':
              case 'z':
                strength--;
                break;
            }
        }
    }

    return sprintf(best_ext, "%s.%s", class_name, best);
}