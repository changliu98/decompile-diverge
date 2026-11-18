void qr_getSize(int version, int ecl, int size[2], int modules[2],
                int *ecc_level) {
  size[0] = size[1] = version;
  *ecc_level = ecl;
  modules[0] = version;
  modules[1] = ecl;
}