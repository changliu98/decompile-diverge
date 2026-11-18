const char *__cdecl func0(int year)
{
  static const char * const ZODIAC_SIGNS[12] = {
    "Dragon", "Snake", "Horse", "sheep", 
    "Monkey", "Rooster", "Dog", "Pig", 
    "Rat", "Ox", "Tiger", "Hare"
  };

  // Calculate the index in the zodiac cycle.
  // The complex modulo logic is a compiler-generated equivalent for 
  // handling negative numbers in C/C++, which safely maps to a 0-11 index.
  int index = (year - 2000) % 12;
  if (index < 0)
    index += 12;

  return ZODIAC_SIGNS[index];
}