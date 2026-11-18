void __cdecl helper_float_19_recursive(float *buf, int depth)
{
  int j, k, j_0, k_0, j_1, k_1, j_2, k_2, j_3, k_3, j_4, k_4;

  switch ( depth )
  {
    case 13:
      for ( j = 0; j < 0x2000; j += 64 )
      {
        for ( k = 0; k < 8; k += 8 )
        {
          float *base = &buf[j + k];
          
          // Stage 1: Complex shuffling and additions/subtractions
          for (int i = 0; i < 8; ++i) {
            __m256 v = _mm256_loadu_ps(base + i * 8);
            __m256 v_perm_a0 = _mm256_permute_ps(v, 0xA0);
            __m256 v_perm_f5 = _mm256_permute_ps(v, 0xF5);
            __m256 v_neg = _mm256_xor_ps(_mm256_setzero_ps(), v_perm_f5);
            v = _mm256_addsub_ps(v_perm_a0, v_neg);
            
            __m256 v_perm_44 = _mm256_permute_ps(v, 0x44);
            __m256 v_perm_ee = _mm256_permute_ps(v, 0xEE);
            __m256 v_neg_ee = _mm256_xor_ps(_mm256_setzero_ps(), v_perm_ee);
            __m256 v_blend = _mm256_blend_ps(v_perm_ee, v_neg_ee, 0xCC);
            v = _mm256_add_ps(v_blend, v_perm_44);
            
            __m256 v_zero = _mm256_setzero_ps();
            __m256 v_sub = _mm256_sub_ps(v_zero, v);
            __m256 v_perm2_0 = _mm256_permute2f128_ps(v, v, 0);
            __m256 v_perm2_1 = _mm256_permute2f128_ps(v, v_sub, 0x31);
            v = _mm256_add_ps(v_perm2_1, v_perm2_0);
            
            _mm256_storeu_ps(base + i * 8, v);
          }

          // Stage 2: Standard 8-point butterfly
          FFT_BUTTERFLY_8(base, base + 8, base + 16, base + 24, base + 32, base + 40, base + 48, base + 56);
        }
      }
      
      for ( j_0 = 0; j_0 < 0x2000; j_0 += 512 )
      {
        for ( k_0 = 0; k_0 < 64; k_0 += 8 )
        {
          float *base = &buf[j_0 + k_0];
          FFT_BUTTERFLY_8(base, base + 64, base + 128, base + 192, base + 256, base + 320, base + 384, base + 448);
        }
      }
      
      for ( j_1 = 0; j_1 < 0x2000; j_1 += 4096 )
      {
        for ( k_1 = 0; k_1 < 512; k_1 += 8 )
        {
          float *base = &buf[j_1 + k_1];
          FFT_BUTTERFLY_8(base, base + 512, base + 1024, base + 1536, base + 2048, base + 2560, base + 3072, base + 3584);
        }
      }
      
      for ( j_2 = 0; j_2 < 0x2000; j_2 += 0x2000 )
      {
        for ( k_2 = 0; k_2 < 4096; k_2 += 8 )
        {
          float *base = &buf[j_2 + k_2];
          __m256 v0 = _mm256_loadu_ps(base);
          __m256 v1 = _mm256_loadu_ps(base + 4096);
          _mm256_storeu_ps(base, _mm256_add_ps(v0, v1));
          _mm256_storeu_ps(base + 4096, _mm256_sub_ps(v0, v1));
        }
      }
      break;
      
    case 16:
      helper_float_19_recursive(buf, 13);
      helper_float_19_recursive(buf + 0x2000, 13);
      helper_float_19_recursive(buf + 0x4000, 13);
      helper_float_19_recursive(buf + 24576, 13);
      helper_float_19_recursive(buf + 0x8000, 13);
      helper_float_19_recursive(buf + 40960, 13);
      helper_float_19_recursive(buf + 49152, 13);
      helper_float_19_recursive(buf + 57344, 13);
      
      for ( j_3 = 0; j_3 < 0x10000; j_3 += 0x10000 )
      {
        for ( k_3 = 0; k_3 < 0x2000; k_3 += 8 )
        {
          float *base = &buf[j_3 + k_3];
          FFT_BUTTERFLY_8(base, base + 0x2000, base + 0x4000, base + 24576, base + 0x8000, base + 40960, base + 49152, base + 57344);
        }
      }
      break;
      
    case 19:
      helper_float_19_recursive(buf, 16);
      helper_float_19_recursive(buf + 0x10000, 16);
      helper_float_19_recursive(buf + 0x20000, 16);
      helper_float_19_recursive(buf + 196608, 16);
      helper_float_19_recursive(buf + 0x40000, 16);
      helper_float_19_recursive(buf + 327680, 16);
      helper_float_19_recursive(buf + 393216, 16);
      helper_float_19_recursive(buf + 458752, 16);
      
      for ( j_4 = 0; j_4 < 0x80000; j_4 += 0x80000 )
      {
        for ( k_4 = 0; k_4 < 0x10000; k_4 += 8 )
        {
          float *base = &buf[j_4 + k_4];
          FFT_BUTTERFLY_8(base, base + 0x10000, base + 0x20000, base + 196608, base + 0x40000, base + 327680, base + 393216, base + 458752);
        }
      }
      break;
  }
}