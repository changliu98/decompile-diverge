// Converts an uppercase ASCII character to lowercase.
// If the character is between 'A' (0x41) and 'Z' (0x5A),
// it adds 0x20 to convert it to its lowercase equivalent.
// Otherwise, returns the character unchanged.
int lowercase(int character)
{
    // Check if the character is an uppercase letter (A-Z)
    if ((0x40 < character) && (character < 0x5b)) {
        // Convert to lowercase by adding 32 (0x20)
        character += 0x20;
    }
    // Return the resulting character
    return character;
}