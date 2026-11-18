int
unicoder_utf16_decode(
    uint32_t * result,
    const unsigned char * data,
    unsigned int endianness)
{
  uint16_t dbyteA, dbyteB;

  if ((endianness != 2) && (endianness != 1)) {
    return -4;
  }

  if (data == NULL) {
    return -1;
  }

  if (result == NULL) {
    return -1;
  }

  if (endianness == 1) {
    dbyteA = (data[0] << 8) | data[1];
    dbyteB = (data[2] << 8) | data[3];
  } else {
    dbyteA = data[0] | (data[1] << 8);
    dbyteB = data[2] | (data[3] << 8);
  }

  if ((dbyteA >= 0xD800) && (dbyteA <= 0xDFFF)) {
    if ((dbyteA >= 0xD800) && (dbyteA <= 0xDBFF)) {
      if ((dbyteB >= 0xDC00) && (dbyteB <= 0xDFFF)) {
        *result = 0;
        *result |= (dbyteA & 0x3FF);
        *result <<= 10;
        *result |= (dbyteB & 0x3FF);
        *result += 0x10000;

        return 4;
      }
    }

    return -8;
  }

  if (dbyteA > 0x10FFFF) {
    return -16;
  }

  *result = dbyteA;

  return 2;
}