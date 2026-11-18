int toup(int character)
{
  // Check if the character is a lowercase letter (ASCII 'a' to 'z')
  if ((0x60 < character) && (character < 0x7b)) {
    // Convert lowercase to uppercase by subtracting 0x20 (32 in decimal)
    character = character - 0x20;
  }
  // Return the character (unchanged if not lowercase, or converted if it was)
  return character;
}