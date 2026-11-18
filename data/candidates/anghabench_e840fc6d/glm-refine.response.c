char base64_encode_value(char value_in)
{
    // The base64 alphabet only has 64 characters (indices 0 to 63).
    // If the input is within this valid range, return the corresponding character.
    if (value_in >= 0 && value_in <= 63)
        return base64_encode_value_encoding[value_in];
    
    // 61 is the ASCII code for '=', which is used as the padding character
    // in base64 encoding for invalid or out-of-bounds inputs.
    return '=';
}