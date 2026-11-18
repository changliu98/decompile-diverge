bool __cdecl alps_check_valid_firmware_id(unsigned __int8 *id)
{
    // Check if the first byte is 0x73 ('s')
    if (*id != 0x73)
        return false;

    // Check the second byte for valid firmware IDs
    return id[1] == 0x07 || 
           id[1] == 0x08 || 
           (id[1] & 0xF0) == 0xB0 ||  // Matches 0xB0 - 0xBF
           (id[1] & 0xF0) == 0xC0;    // Matches 0xC0 - 0xCF
}