void applyNoiseGate(float in, float *out, float threshold, float knee, float ratio, float range, float attack, float release) {
 if(in > threshold + knee) {
  *out += attack;
 } else if(in < threshold - knee) {
  *out += release;
 } else {
  *out = in;
 }

 if(*out < range) *out = range;
 if(*out > range + knee) *out = range + knee;
}