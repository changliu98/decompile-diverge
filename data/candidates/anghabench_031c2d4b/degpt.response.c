bool tomoyo_invalid(uchar character)
{
  // Return true if the character is not null and is outside the printable ASCII range (0x21 to 0x7E)
  return character != '\0' && (character < 0x21 || 0x7e < character);
}