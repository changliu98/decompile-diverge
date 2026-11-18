// Copies the MAC address from the 'from' buffer to the 'setto' buffer
void set_mac(char *destination, char *source)
{
    int index;
    // Iterate through each byte of the 6-byte MAC address
    for (index = 0; index < 6; index++) {
        destination[index] = source[index];
    }
}