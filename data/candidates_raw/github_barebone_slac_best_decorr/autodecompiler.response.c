int best_decorr(int16_t *samples, int len, int channels)
{
   int best_magnitude = magnitude_bits(samples, len, channels);
   int best_decorr_index;
   int decorr_index = 0;

   for (;;) {
      if (decorr_index < 7) {
         int magnitude = decorrelate(samples, len, channels);
         decorr_index++;
         if (magnitude < best_magnitude) {
            best_decorr_index = decorr_index;
            best_magnitude = magnitude;
            continue;
         }
         correlate(samples, len, channels);
         decorr_index--;
      }

      if (decorr_index == 0) {
         int magnitude = correlate(samples, len, channels);
         decorr_index--;
         if (magnitude < best_magnitude) {
            best_decorr_index = decorr_index;
            best_magnitude = magnitude;
            continue;
         }
         decorrelate(samples, len, channels);
         decorr_index++;
      } else {
         return best_decorr_index;
      }
   }
}