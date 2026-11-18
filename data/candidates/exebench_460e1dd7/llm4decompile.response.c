void BinaryFiles__swap_bytes32(unsigned int *value)
{
 unsigned int new_value;
 unsigned char *bytes = (unsigned char*)&new_value;

 bytes[0] = *value & 0xff;
 bytes[1] = (*value & 0xff00) >> 8;
 bytes[2] = (*value & 0xff0000) >> 16;
 bytes[3] = (*value & 0xff000000) >> 24;

 *value = new_value;
}