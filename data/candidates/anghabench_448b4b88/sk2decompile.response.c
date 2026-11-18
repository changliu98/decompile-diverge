static bool s390_cpumsf_reached_trailer(unsigned int trailer_offset,
                                        unsigned int offset) {
  unsigned int trailer_end;
  trailer_end = S390_CPUMSF_TRAILER_SIZE - 4 -
                (offset & (S390_CPUMSF_TRAILER_SIZE - 1));
  if (trailer_end >= trailer_offset) return true;
  return false;
}