// Returns the size of the SDS header based on the string type.
// The 'type' parameter encodes the SDS string type in its lower 3 bits.
// The function maps these type values to their corresponding header sizes.
int sdsHdrSize(char stringType)
{
    // Extract the lower 3 bits of the type to determine the SDS string format.
    switch(stringType & 7) {
    // SDS_TYPE_0: No prefix, header size is 1 byte (just the length byte).
    case 0: return 1;
    // SDS_TYPE_1: 2-byte length prefix, header size is 3 bytes (1 byte type + 2 bytes length).
    case 1: return 3;
    // SDS_TYPE_2: 4-byte length prefix, header size is 5 bytes (1 byte type + 4 bytes length).
    case 2: return 5;
    // SDS_TYPE_3: 8-byte length prefix, header size is 9 bytes (1 byte type + 8 bytes length).
    case 3: return 9;
    // SDS_TYPE_4: Reserved or invalid type, header size is 0x11 (17 bytes) for future use or specific encoding.
    case 4: return 0x11;
    // Invalid type value, return 0 to indicate an error or unsupported type.
    default: return 0;
    }
}