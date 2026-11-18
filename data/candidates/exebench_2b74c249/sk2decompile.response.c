int setsize(unsigned long size, unsigned int *nr_sets, unsigned int *nr_ways,
            unsigned int *nr_blocks) {
  int ret = 0;
  unsigned long nr_sets_tmp = 1024;
  unsigned long nr_ways_tmp = 62;
  unsigned long nr_blocks_tmp = size / (nr_sets_tmp * nr_ways_tmp);
  if (size % (nr_sets_tmp * nr_ways_tmp)) {
    nr_ways_tmp++;
    nr_blocks_tmp = size / (nr_sets_tmp * nr_ways_tmp);
    if (size % (nr_sets_tmp * nr_ways_tmp)) {
      nr_sets_tmp++;
      nr_blocks_tmp = size / (nr_sets_tmp * nr_ways_tmp);
    }
  }
  if (nr_sets_tmp == 0) ret = -1;
  *nr_sets = nr_sets_tmp;
  *nr_blocks = nr_blocks_tmp;
  *nr_ways = nr_ways_tmp;
  return ret;
}