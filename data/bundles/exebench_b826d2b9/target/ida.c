void __cdecl helper_float_21_recursive(float *buf, int depth)
{
  int k_5; // [rsp+Ch] [rbp-44h]
  int j_5; // [rsp+10h] [rbp-40h]
  int k_4; // [rsp+14h] [rbp-3Ch]
  int j_4; // [rsp+18h] [rbp-38h]
  int k_3; // [rsp+1Ch] [rbp-34h]
  int j_3; // [rsp+20h] [rbp-30h]
  int k_2; // [rsp+24h] [rbp-2Ch]
  int j_2; // [rsp+28h] [rbp-28h]
  int k_1; // [rsp+2Ch] [rbp-24h]
  int j_1; // [rsp+30h] [rbp-20h]
  int k_0; // [rsp+34h] [rbp-1Ch]
  int j_0; // [rsp+38h] [rbp-18h]
  int k; // [rsp+3Ch] [rbp-14h]
  int j; // [rsp+40h] [rbp-10h]

  switch ( depth )
  {
    case 13:
      for ( j = 0; j < 0x2000; j += 64 )
      {
        for ( k = 0; k < 8; k += 8 )
        {
          _RAX = &buf[j + k];
          _RCX = _RAX + 8;
          _RDX = _RAX + 16;
          _RSI = _RAX + 24;
          _RDI = _RAX + 32;
          _R8 = _RAX + 40;
          _R9 = _RAX + 48;
          _R10 = _RAX + 56;
          __asm
          {
            vmovups ymm0, ymmword ptr [rax]
            vmovups ymm1, ymmword ptr [rcx]
            vmovups ymm2, ymmword ptr [rdx]
            vmovups ymm3, ymmword ptr [rsi]
            vmovups ymm4, ymmword ptr [rdi]
            vmovups ymm5, ymmword ptr [r8]
            vmovups ymm6, ymmword ptr [r9]
            vmovups ymm7, ymmword ptr [r10]
            vpermilps ymm8, ymm0, 0A0h
            vpermilps ymm9, ymm0, 0F5h
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vaddsubps ymm0, ymm8, ymm11
            vpermilps ymm8, ymm1, 0A0h
            vpermilps ymm9, ymm1, 0F5h
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vaddsubps ymm1, ymm8, ymm11
            vpermilps ymm8, ymm2, 0A0h
            vpermilps ymm9, ymm2, 0F5h
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vaddsubps ymm2, ymm8, ymm11
            vpermilps ymm8, ymm3, 0A0h
            vpermilps ymm9, ymm3, 0F5h
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vaddsubps ymm3, ymm8, ymm11
            vpermilps ymm8, ymm4, 0A0h
            vpermilps ymm9, ymm4, 0F5h
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vaddsubps ymm4, ymm8, ymm11
            vpermilps ymm8, ymm5, 0A0h
            vpermilps ymm9, ymm5, 0F5h
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vaddsubps ymm5, ymm8, ymm11
            vpermilps ymm8, ymm6, 0A0h
            vpermilps ymm9, ymm6, 0F5h
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vaddsubps ymm6, ymm8, ymm11
            vpermilps ymm8, ymm7, 0A0h
            vpermilps ymm9, ymm7, 0F5h
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vaddsubps ymm7, ymm8, ymm11
            vpermilps ymm8, ymm0, 44h ; 'D'
            vpermilps ymm9, ymm0, 0EEh
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vblendps ymm12, ymm9, ymm11, 0CCh
            vaddps  ymm0, ymm12, ymm8
            vpermilps ymm8, ymm1, 44h ; 'D'
            vpermilps ymm9, ymm1, 0EEh
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vblendps ymm12, ymm9, ymm11, 0CCh
            vaddps  ymm1, ymm12, ymm8
            vpermilps ymm8, ymm2, 44h ; 'D'
            vpermilps ymm9, ymm2, 0EEh
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vblendps ymm12, ymm9, ymm11, 0CCh
            vaddps  ymm2, ymm12, ymm8
            vpermilps ymm8, ymm3, 44h ; 'D'
            vpermilps ymm9, ymm3, 0EEh
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vblendps ymm12, ymm9, ymm11, 0CCh
            vaddps  ymm3, ymm12, ymm8
            vpermilps ymm8, ymm4, 44h ; 'D'
            vpermilps ymm9, ymm4, 0EEh
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vblendps ymm12, ymm9, ymm11, 0CCh
            vaddps  ymm4, ymm12, ymm8
            vpermilps ymm8, ymm5, 44h ; 'D'
            vpermilps ymm9, ymm5, 0EEh
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vblendps ymm12, ymm9, ymm11, 0CCh
            vaddps  ymm5, ymm12, ymm8
            vpermilps ymm8, ymm6, 44h ; 'D'
            vpermilps ymm9, ymm6, 0EEh
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vblendps ymm12, ymm9, ymm11, 0CCh
            vaddps  ymm6, ymm12, ymm8
            vpermilps ymm8, ymm7, 44h ; 'D'
            vpermilps ymm9, ymm7, 0EEh
            vxorps  ymm10, ymm10, ymm10
            vsubps  ymm11, ymm10, ymm9
            vblendps ymm12, ymm9, ymm11, 0CCh
            vaddps  ymm7, ymm12, ymm8
            vxorps  ymm8, ymm8, ymm8
            vsubps  ymm9, ymm8, ymm0
            vperm2f128 ymm10, ymm0, ymm0, 0
            vperm2f128 ymm11, ymm0, ymm9, 31h ; '1'
            vaddps  ymm0, ymm11, ymm10
            vxorps  ymm8, ymm8, ymm8
            vsubps  ymm9, ymm8, ymm1
            vperm2f128 ymm10, ymm1, ymm1, 0
            vperm2f128 ymm11, ymm1, ymm9, 31h ; '1'
            vaddps  ymm1, ymm11, ymm10
            vxorps  ymm8, ymm8, ymm8
            vsubps  ymm9, ymm8, ymm2
            vperm2f128 ymm10, ymm2, ymm2, 0
            vperm2f128 ymm11, ymm2, ymm9, 31h ; '1'
            vaddps  ymm2, ymm11, ymm10
            vxorps  ymm8, ymm8, ymm8
            vsubps  ymm9, ymm8, ymm3
            vperm2f128 ymm10, ymm3, ymm3, 0
            vperm2f128 ymm11, ymm3, ymm9, 31h ; '1'
            vaddps  ymm3, ymm11, ymm10
            vxorps  ymm8, ymm8, ymm8
            vsubps  ymm9, ymm8, ymm4
            vperm2f128 ymm10, ymm4, ymm4, 0
            vperm2f128 ymm11, ymm4, ymm9, 31h ; '1'
            vaddps  ymm4, ymm11, ymm10
            vxorps  ymm8, ymm8, ymm8
            vsubps  ymm9, ymm8, ymm5
            vperm2f128 ymm10, ymm5, ymm5, 0
            vperm2f128 ymm11, ymm5, ymm9, 31h ; '1'
            vaddps  ymm5, ymm11, ymm10
            vxorps  ymm8, ymm8, ymm8
            vsubps  ymm9, ymm8, ymm6
            vperm2f128 ymm10, ymm6, ymm6, 0
            vperm2f128 ymm11, ymm6, ymm9, 31h ; '1'
            vaddps  ymm6, ymm11, ymm10
            vxorps  ymm8, ymm8, ymm8
            vsubps  ymm9, ymm8, ymm7
            vperm2f128 ymm10, ymm7, ymm7, 0
            vperm2f128 ymm11, ymm7, ymm9, 31h ; '1'
            vaddps  ymm7, ymm11, ymm10
            vaddps  ymm8, ymm0, ymm1
            vsubps  ymm9, ymm0, ymm1
            vaddps  ymm10, ymm2, ymm3
            vsubps  ymm11, ymm2, ymm3
            vaddps  ymm12, ymm4, ymm5
            vsubps  ymm13, ymm4, ymm5
            vaddps  ymm14, ymm6, ymm7
            vsubps  ymm15, ymm6, ymm7
            vaddps  ymm0, ymm8, ymm10
            vsubps  ymm2, ymm8, ymm10
            vaddps  ymm1, ymm9, ymm11
            vsubps  ymm3, ymm9, ymm11
            vaddps  ymm4, ymm12, ymm14
            vsubps  ymm6, ymm12, ymm14
            vaddps  ymm5, ymm13, ymm15
            vsubps  ymm7, ymm13, ymm15
            vaddps  ymm8, ymm0, ymm4
            vsubps  ymm12, ymm0, ymm4
            vaddps  ymm9, ymm1, ymm5
            vsubps  ymm13, ymm1, ymm5
            vaddps  ymm10, ymm2, ymm6
            vsubps  ymm14, ymm2, ymm6
            vaddps  ymm11, ymm3, ymm7
            vsubps  ymm15, ymm3, ymm7
            vmovups ymmword ptr [rax], ymm8
            vmovups ymmword ptr [rcx], ymm9
            vmovups ymmword ptr [rdx], ymm10
            vmovups ymmword ptr [rsi], ymm11
            vmovups ymmword ptr [rdi], ymm12
            vmovups ymmword ptr [r8], ymm13
            vmovups ymmword ptr [r9], ymm14
            vmovups ymmword ptr [r10], ymm15
          }
        }
      }
      for ( j_0 = 0; j_0 < 0x2000; j_0 += 512 )
      {
        for ( k_0 = 0; k_0 < 64; k_0 += 8 )
        {
          _RAX = &buf[j_0 + k_0];
          _RCX = _RAX + 64;
          _RDX = _RAX + 128;
          _RSI = _RAX + 192;
          _RDI = _RAX + 256;
          _R8 = _RAX + 320;
          _R9 = _RAX + 384;
          _R10 = _RAX + 448;
          __asm
          {
            vmovups ymm0, ymmword ptr [rax]
            vmovups ymm1, ymmword ptr [rcx]
            vmovups ymm2, ymmword ptr [rdx]
            vmovups ymm3, ymmword ptr [rsi]
            vmovups ymm4, ymmword ptr [rdi]
            vmovups ymm5, ymmword ptr [r8]
            vmovups ymm6, ymmword ptr [r9]
            vmovups ymm7, ymmword ptr [r10]
            vaddps  ymm8, ymm0, ymm1
            vsubps  ymm9, ymm0, ymm1
            vaddps  ymm10, ymm2, ymm3
            vsubps  ymm11, ymm2, ymm3
            vaddps  ymm12, ymm4, ymm5
            vsubps  ymm13, ymm4, ymm5
            vaddps  ymm14, ymm6, ymm7
            vsubps  ymm15, ymm6, ymm7
            vaddps  ymm0, ymm8, ymm10
            vsubps  ymm2, ymm8, ymm10
            vaddps  ymm1, ymm9, ymm11
            vsubps  ymm3, ymm9, ymm11
            vaddps  ymm4, ymm12, ymm14
            vsubps  ymm6, ymm12, ymm14
            vaddps  ymm5, ymm13, ymm15
            vsubps  ymm7, ymm13, ymm15
            vaddps  ymm8, ymm0, ymm4
            vsubps  ymm12, ymm0, ymm4
            vaddps  ymm9, ymm1, ymm5
            vsubps  ymm13, ymm1, ymm5
            vaddps  ymm10, ymm2, ymm6
            vsubps  ymm14, ymm2, ymm6
            vaddps  ymm11, ymm3, ymm7
            vsubps  ymm15, ymm3, ymm7
            vmovups ymmword ptr [rax], ymm8
            vmovups ymmword ptr [rcx], ymm9
            vmovups ymmword ptr [rdx], ymm10
            vmovups ymmword ptr [rsi], ymm11
            vmovups ymmword ptr [rdi], ymm12
            vmovups ymmword ptr [r8], ymm13
            vmovups ymmword ptr [r9], ymm14
            vmovups ymmword ptr [r10], ymm15
          }
        }
      }
      for ( j_1 = 0; j_1 < 0x2000; j_1 += 4096 )
      {
        for ( k_1 = 0; k_1 < 512; k_1 += 8 )
        {
          _RAX = &buf[j_1 + k_1];
          _RCX = _RAX + 512;
          _RDX = _RAX + 1024;
          _RSI = _RAX + 1536;
          _RDI = _RAX + 2048;
          _R8 = _RAX + 2560;
          _R9 = _RAX + 3072;
          _R10 = _RAX + 3584;
          __asm
          {
            vmovups ymm0, ymmword ptr [rax]
            vmovups ymm1, ymmword ptr [rcx]
            vmovups ymm2, ymmword ptr [rdx]
            vmovups ymm3, ymmword ptr [rsi]
            vmovups ymm4, ymmword ptr [rdi]
            vmovups ymm5, ymmword ptr [r8]
            vmovups ymm6, ymmword ptr [r9]
            vmovups ymm7, ymmword ptr [r10]
            vaddps  ymm8, ymm0, ymm1
            vsubps  ymm9, ymm0, ymm1
            vaddps  ymm10, ymm2, ymm3
            vsubps  ymm11, ymm2, ymm3
            vaddps  ymm12, ymm4, ymm5
            vsubps  ymm13, ymm4, ymm5
            vaddps  ymm14, ymm6, ymm7
            vsubps  ymm15, ymm6, ymm7
            vaddps  ymm0, ymm8, ymm10
            vsubps  ymm2, ymm8, ymm10
            vaddps  ymm1, ymm9, ymm11
            vsubps  ymm3, ymm9, ymm11
            vaddps  ymm4, ymm12, ymm14
            vsubps  ymm6, ymm12, ymm14
            vaddps  ymm5, ymm13, ymm15
            vsubps  ymm7, ymm13, ymm15
            vaddps  ymm8, ymm0, ymm4
            vsubps  ymm12, ymm0, ymm4
            vaddps  ymm9, ymm1, ymm5
            vsubps  ymm13, ymm1, ymm5
            vaddps  ymm10, ymm2, ymm6
            vsubps  ymm14, ymm2, ymm6
            vaddps  ymm11, ymm3, ymm7
            vsubps  ymm15, ymm3, ymm7
            vmovups ymmword ptr [rax], ymm8
            vmovups ymmword ptr [rcx], ymm9
            vmovups ymmword ptr [rdx], ymm10
            vmovups ymmword ptr [rsi], ymm11
            vmovups ymmword ptr [rdi], ymm12
            vmovups ymmword ptr [r8], ymm13
            vmovups ymmword ptr [r9], ymm14
            vmovups ymmword ptr [r10], ymm15
          }
        }
      }
      for ( j_2 = 0; j_2 < 0x2000; j_2 += 0x2000 )
      {
        for ( k_2 = 0; k_2 < 4096; k_2 += 8 )
        {
          _RAX = &buf[j_2 + k_2];
          _RCX = _RAX + 4096;
          __asm
          {
            vmovups ymm0, ymmword ptr [rax]
            vmovups ymm1, ymmword ptr [rcx]
            vaddps  ymm8, ymm0, ymm1
            vsubps  ymm9, ymm0, ymm1
            vmovups ymmword ptr [rax], ymm8
            vmovups ymmword ptr [rcx], ymm9
          }
        }
      }
      break;
    case 16:
      helper_float_21_recursive(buf, 13);
      helper_float_21_recursive(buf + 0x2000, 13);
      helper_float_21_recursive(buf + 0x4000, 13);
      helper_float_21_recursive(buf + 24576, 13);
      helper_float_21_recursive(buf + 0x8000, 13);
      helper_float_21_recursive(buf + 40960, 13);
      helper_float_21_recursive(buf + 49152, 13);
      helper_float_21_recursive(buf + 57344, 13);
      for ( j_3 = 0; j_3 < 0x10000; j_3 += 0x10000 )
      {
        for ( k_3 = 0; k_3 < 0x2000; k_3 += 8 )
        {
          _RAX = &buf[j_3 + k_3];
          _RCX = _RAX + 0x2000;
          _RDX = _RAX + 0x4000;
          _RSI = _RAX + 24576;
          _RDI = _RAX + 0x8000;
          _R8 = _RAX + 40960;
          _R9 = _RAX + 49152;
          _R10 = _RAX + 57344;
          __asm
          {
            vmovups ymm0, ymmword ptr [rax]
            vmovups ymm1, ymmword ptr [rcx]
            vmovups ymm2, ymmword ptr [rdx]
            vmovups ymm3, ymmword ptr [rsi]
            vmovups ymm4, ymmword ptr [rdi]
            vmovups ymm5, ymmword ptr [r8]
            vmovups ymm6, ymmword ptr [r9]
            vmovups ymm7, ymmword ptr [r10]
            vaddps  ymm8, ymm0, ymm1
            vsubps  ymm9, ymm0, ymm1
            vaddps  ymm10, ymm2, ymm3
            vsubps  ymm11, ymm2, ymm3
            vaddps  ymm12, ymm4, ymm5
            vsubps  ymm13, ymm4, ymm5
            vaddps  ymm14, ymm6, ymm7
            vsubps  ymm15, ymm6, ymm7
            vaddps  ymm0, ymm8, ymm10
            vsubps  ymm2, ymm8, ymm10
            vaddps  ymm1, ymm9, ymm11
            vsubps  ymm3, ymm9, ymm11
            vaddps  ymm4, ymm12, ymm14
            vsubps  ymm6, ymm12, ymm14
            vaddps  ymm5, ymm13, ymm15
            vsubps  ymm7, ymm13, ymm15
            vaddps  ymm8, ymm0, ymm4
            vsubps  ymm12, ymm0, ymm4
            vaddps  ymm9, ymm1, ymm5
            vsubps  ymm13, ymm1, ymm5
            vaddps  ymm10, ymm2, ymm6
            vsubps  ymm14, ymm2, ymm6
            vaddps  ymm11, ymm3, ymm7
            vsubps  ymm15, ymm3, ymm7
            vmovups ymmword ptr [rax], ymm8
            vmovups ymmword ptr [rcx], ymm9
            vmovups ymmword ptr [rdx], ymm10
            vmovups ymmword ptr [rsi], ymm11
            vmovups ymmword ptr [rdi], ymm12
            vmovups ymmword ptr [r8], ymm13
            vmovups ymmword ptr [r9], ymm14
            vmovups ymmword ptr [r10], ymm15
          }
        }
      }
      break;
    case 19:
      helper_float_21_recursive(buf, 16);
      helper_float_21_recursive(buf + 0x10000, 16);
      helper_float_21_recursive(buf + 0x20000, 16);
      helper_float_21_recursive(buf + 196608, 16);
      helper_float_21_recursive(buf + 0x40000, 16);
      helper_float_21_recursive(buf + 327680, 16);
      helper_float_21_recursive(buf + 393216, 16);
      helper_float_21_recursive(buf + 458752, 16);
      for ( j_4 = 0; j_4 < 0x80000; j_4 += 0x80000 )
      {
        for ( k_4 = 0; k_4 < 0x10000; k_4 += 8 )
        {
          _RAX = &buf[j_4 + k_4];
          _RCX = _RAX + 0x10000;
          _RDX = _RAX + 0x20000;
          _RSI = _RAX + 196608;
          _RDI = _RAX + 0x40000;
          _R8 = _RAX + 327680;
          _R9 = _RAX + 393216;
          _R10 = _RAX + 458752;
          __asm
          {
            vmovups ymm0, ymmword ptr [rax]
            vmovups ymm1, ymmword ptr [rcx]
            vmovups ymm2, ymmword ptr [rdx]
            vmovups ymm3, ymmword ptr [rsi]
            vmovups ymm4, ymmword ptr [rdi]
            vmovups ymm5, ymmword ptr [r8]
            vmovups ymm6, ymmword ptr [r9]
            vmovups ymm7, ymmword ptr [r10]
            vaddps  ymm8, ymm0, ymm1
            vsubps  ymm9, ymm0, ymm1
            vaddps  ymm10, ymm2, ymm3
            vsubps  ymm11, ymm2, ymm3
            vaddps  ymm12, ymm4, ymm5
            vsubps  ymm13, ymm4, ymm5
            vaddps  ymm14, ymm6, ymm7
            vsubps  ymm15, ymm6, ymm7
            vaddps  ymm0, ymm8, ymm10
            vsubps  ymm2, ymm8, ymm10
            vaddps  ymm1, ymm9, ymm11
            vsubps  ymm3, ymm9, ymm11
            vaddps  ymm4, ymm12, ymm14
            vsubps  ymm6, ymm12, ymm14
            vaddps  ymm5, ymm13, ymm15
            vsubps  ymm7, ymm13, ymm15
            vaddps  ymm8, ymm0, ymm4
            vsubps  ymm12, ymm0, ymm4
            vaddps  ymm9, ymm1, ymm5
            vsubps  ymm13, ymm1, ymm5
            vaddps  ymm10, ymm2, ymm6
            vsubps  ymm14, ymm2, ymm6
            vaddps  ymm11, ymm3, ymm7
            vsubps  ymm15, ymm3, ymm7
            vmovups ymmword ptr [rax], ymm8
            vmovups ymmword ptr [rcx], ymm9
            vmovups ymmword ptr [rdx], ymm10
            vmovups ymmword ptr [rsi], ymm11
            vmovups ymmword ptr [rdi], ymm12
            vmovups ymmword ptr [r8], ymm13
            vmovups ymmword ptr [r9], ymm14
            vmovups ymmword ptr [r10], ymm15
          }
        }
      }
      break;
    case 21:
      helper_float_21_recursive(buf, 19);
      helper_float_21_recursive(buf + 0x80000, 19);
      helper_float_21_recursive(buf + 0x100000, 19);
      helper_float_21_recursive(buf + 1572864, 19);
      for ( j_5 = 0; j_5 < 0x200000; j_5 += 0x200000 )
      {
        for ( k_5 = 0; k_5 < 0x80000; k_5 += 8 )
        {
          _RAX = &buf[j_5 + k_5];
          _RCX = _RAX + 0x80000;
          _RDX = _RAX + 0x100000;
          _RSI = _RAX + 1572864;
          __asm
          {
            vmovups ymm0, ymmword ptr [rax]
            vmovups ymm1, ymmword ptr [rcx]
            vmovups ymm2, ymmword ptr [rdx]
            vmovups ymm3, ymmword ptr [rsi]
            vaddps  ymm8, ymm0, ymm1
            vsubps  ymm9, ymm0, ymm1
            vaddps  ymm10, ymm2, ymm3
            vsubps  ymm11, ymm2, ymm3
            vaddps  ymm0, ymm8, ymm10
            vsubps  ymm2, ymm8, ymm10
            vaddps  ymm1, ymm9, ymm11
            vsubps  ymm3, ymm9, ymm11
            vmovups ymmword ptr [rax], ymm0
            vmovups ymmword ptr [rcx], ymm1
            vmovups ymmword ptr [rdx], ymm2
            vmovups ymmword ptr [rsi], ymm3
          }
        }
      }
      break;
  }
}