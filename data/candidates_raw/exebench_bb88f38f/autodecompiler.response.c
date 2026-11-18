int clearbit(int bit, long *mask) {
 return __sync_fetch_and_and(mask, ~((long)(1 << bit)));
}