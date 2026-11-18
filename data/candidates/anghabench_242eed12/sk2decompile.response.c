static unsigned int wacom_intuos_id_mangle(unsigned int id) {
  unsigned int tmp;
  tmp = id & 0x00000fff;
  id &= 0xfffff000;
  id |= tmp << 4;
  return id;
}