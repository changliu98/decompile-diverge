#include <assert.h>

#include <math.h>

#include <string.h>

#include <stdarg.h>

static inline void sBitwiseXor_process(float bIn0, float bIn1, float* bOut) {







  *bOut = (float) (((int) bIn0) ^ ((int) bIn1));

}
