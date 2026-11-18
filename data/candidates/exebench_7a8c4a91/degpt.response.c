void removeCharactersInPlace(char *aString,char *excludeChars)

{
  char cVar1;
  char *excludePtr;
  _Bool found;
  char *address;
  char *excludeChars_local;
  char *aString_local;
  
  address = aString;
  for (aString_local = aString; excludePtr = excludeChars, *aString_local != '\0';
      aString_local = aString_local + 1) {
    do {
      cVar1 = *excludePtr;
      excludePtr = excludePtr + 1;
    } while (*excludePtr != '\0' && *aString_local != cVar1);
    if (*aString_local != cVar1) {
      *address = *aString_local;
      address = address + 1;
    }
  }
  *address = '\0';
  return;
}