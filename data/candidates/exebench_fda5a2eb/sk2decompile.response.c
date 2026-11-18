void put_user_word(unsigned short word, unsigned short *addr) {
  {
    unsigned short *p = (unsigned short *)addr;
    *p = word;
  }
}