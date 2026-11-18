void tableset(float samplerate, float cutoff, int order, float *filter) {
 filter[0] = (int)(samplerate * cutoff - .9999);
 filter[1] = order - 1;
}