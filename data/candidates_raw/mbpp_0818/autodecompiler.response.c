int numbersOfSubtitle(char* line)
{
 int counter = 0;

 for (int i = 0; i < strlen(line); i++)
 {
  switch (line[i])
  {
  case 'a':
  case 'b':
  case 'c':
  case 'd':
  case 'e':
  case 'f':
  case 'g':
  case 'h':
  case 'i':
  case 'j':
  case 'k':
  case 'l':
  case 'm':
  case 'n':
  case 'o':
  case 'p':
  case 'q':
  case 'r':
  case 's':
  case 't':
  case 'u':
  case 'v':
  case 'w':
  case 'x':
  case 'y':
  case 'z':
   counter++;
   break;
  default:
   break;
  }
 }

 return counter;
}