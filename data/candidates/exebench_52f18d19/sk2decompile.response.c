static inline int atomicIncrement(int *address) {
# 102 "/scratch/repos/new/home/jordi_armengol_estape/c-scraper/outputs/2022-01-22/02-19-57/repos/GPUOpen-ProfessionalCompute-Samples/FluidSimulation/refs/heads/master/common/inc/atomic.h"
  return __sync_fetch_and_add((long *)address, 1);
}