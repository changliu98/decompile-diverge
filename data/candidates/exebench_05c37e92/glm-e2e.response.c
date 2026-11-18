void put_user_long(unsigned long val, unsigned int *ptr) {
    *ptr = (unsigned int)val;
}