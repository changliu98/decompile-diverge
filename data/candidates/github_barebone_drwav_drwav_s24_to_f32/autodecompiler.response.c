void drwav_s24_to_f32(char *buffer_out, char *buffer_in, size_t sample_count) {
 if (buffer_out == NULL || buffer_in == NULL) return;

 int i;
 for (i = 0; i < sample_count; i++) {
  int sample = ((int) buffer_in[i*3] << 8) | ((int) buffer_in[i*3+1] << 16) | ((int) buffer_in[i*3+2] << 24);
  float f = (float) (sample >> 8);
  *(float *) (buffer_out + i * sizeof(float)) = f / 8388608.0;
 }
}