// Converts a hexadecimal character to its integer value.
// Handles lowercase ('a'-'f'), uppercase ('A'-'F'), and digit ('0'-'9') characters.
int hex2int(int hexChar)
{
    // Convert lowercase hex digits 'a'-'f' (0x61-0x66) to 10-15
    if (hexChar >= 0x61 && hexChar <= 0x66)
        return hexChar - 0x57;
    // Convert uppercase hex digits 'A'-'F' (0x41-0x46) to 10-15
    if (hexChar >= 0x41 && hexChar <= 0x46)
        return hexChar - 0x37;
    // Convert digit characters '0'-'9' to 0-9
    return hexChar - 0x30;
}