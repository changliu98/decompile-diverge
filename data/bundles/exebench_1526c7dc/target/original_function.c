static inline void atomic_and(volatile size_t* x,size_t val) {

  __sync_and_and_fetch(x,val);







}