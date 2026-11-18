void crypto_sign_ed25519_ref_sc25519_mul(crypto_sign_ed25519_ref_sc25519 *r, const crypto_sign_ed25519_ref_sc25519 *x, const crypto_sign_ed25519_ref_sc25519 *y)
{
  int64_t r0 = x->v[0];
  int64_t r1 = x->v[1];
  int64_t r2 = x->v[2];
  int64_t r3 = x->v[3];
  int64_t r4 = x->v[4];
  int64_t r5 = x->v[5];
  int64_t r6 = x->v[6];
  int64_t r7 = x->v[7];
  int64_t r8 = x->v[8];
  int64_t r9 = x->v[9];

  int64_t t1;
  int64_t carry0;
  int64_t carry1;
  int64_t carry2;
  int64_t carry3;
  int64_t carry4;
  int64_t carry5;
  int64_t carry6;
  int64_t carry7;
  int64_t carry8;
  int64_t carry9;

  int64_t y0 = y->v[0];
  int64_t y1 = y->v[1];
  int64_t y2 = y->v[2];
  int64_t y3 = y->v[3];
  int64_t y4 = y->v[4];
  int64_t y5 = y->v[5];
  int64_t y6 = y->v[6];
  int64_t y7 = y->v[7];
  int64_t y8 = y->v[8];
  int64_t y9 = y->v[9];


  int64_t r00 = r0 * 121665;
  int64_t r01 = r1 * 121665;
  int64_t r02 = r2 * 121665;
  int64_t r03 = r3 * 121665;
  int64_t r04 = r4 * 121665;
  int64_t r05 = r5 * 121665;
  int64_t r06 = r6 * 121665;
  int64_t r07 = r7 * 121665;
  int64_t r08 = r8 * 121665;
  int64_t r09 = r9 * 121665;


  int64_t r10 = (r09 + (int64_t)(1 << 24)) >> 25; r00 += r10 * 19; r09 -= r10 << 25;
  int64_t r11 = (r01 + (int64_t)(1 << 24)) >> 25; r01 += r11; r00 -= r11 << 25;
  int64_t r12 = (r02 + (int64_t)(1 << 24)) >> 25; r02 += r12; r01 -= r12 << 25;
  int64_t r13 = (r03 + (int64_t)(1 << 24)) >> 25; r03 += r13; r02 -= r13 << 25;
  int64_t r14 = (r04 + (int64_t)(1 << 24)) >> 25; r04 += r14; r03 -= r14 << 25;
  int64_t r15 = (r05 + (int64_t)(1 << 24)) >> 25; r05 += r15; r04 -= r15 << 25;
  int64_t r16 = (r06 + (int64_t)(1 << 24)) >> 25; r06 += r16; r05 -= r16 << 25;
  int64_t r17 = (r07 + (int64_t)(1 << 24)) >> 25; r07 += r17; r06 -= r17 << 25;
  int64_t r18 = (r08 + (int64_t)(1 << 24)) >> 25; r08 += r18; r07 -= r18 << 25;
  int64_t r19 = (r09 + (int64_t)(1 << 24)) >> 25; r09 += r19; r08 -= r19 << 25;


  int64_t r20 = (r00 + (int64_t)(1 << 25)) >> 26; r00 -= r20 << 26;
  int64_t r21 = (r01 + (int64_t)(1 << 25)) >> 26; r01 -= r21 << 26;
  int64_t r22 = (r02 + (int64_t)(1 << 25)) >> 26; r02 -= r22 << 26;
  int64_t r23 = (r03 + (int64_t)(1 << 25)) >> 26; r03 -= r23 << 26;
  int64_t r24 = (r04 + (int64_t)(1 << 25)) >> 26; r04 -= r24 << 26;
  int64_t r25 = (r05 + (int64_t)(1 << 25)) >> 26; r05 -= r25 << 26;
  int64_t r26 = (r06 + (int64_t)(1 << 25)) >> 26; r06 -= r26 << 26;
  int64_t r27 = (r07 + (int64_t)(1 << 25)) >> 26; r07 -= r27 << 26;
  int64_t r28 = (r08 + (int64_t)(1 << 25)) >> 26; r08 -= r28 << 26;
  int64_t r29 = (r09 + (int64_t)(1 << 25)) >> 26; r09 -= r29 << 26;


  int64_t r30 = r00 + y0;
  int64_t r31 = r01 + y1;
  int64_t r32 = r02 + y2;
  int64_t r33 = r03 + y3;
  int64_t r34 = r04 + y4;
  int64_t r35 = r05 + y5;
  int64_t r36 = r06 + y6;
  int64_t r37 = r07 + y7;
  int64_t r38 = r08 + y8;
  int64_t r39 = r09 + y9;

  int64_t s0;
  int64_t s1;
  int64_t s2;
  int64_t s3;
  int64_t s4;
  int64_t s5;
  int64_t s6;
  int64_t s7;
  int64_t s8;
  int64_t s9;

  s0 = r30;
  s1 = r31;
  s2 = r32;
  s3 = r33;
  s4 = r34;
  s5 = r35;
  s6 = r36;
  s7 = r37;
  s8 = r38;
  s9 = r39;

  t1 = s9 >> 25;
  s9 &= ((int64_t)1 << 25) - 1;
  s0 += t1;
  s9 -= t1 << 25;
  s1 += s0 >> 25;
  s0 &= ((int64_t)1 << 25) - 1;
  s2 += s1 >> 25;
  s1 &= ((int64_t)1 << 25) - 1;
  s3 += s2 >> 25;
  s2 &= ((int64_t)1 << 25) - 1;
  s4 += s3 >> 25;
  s3 &= ((int64_t)1 << 25) - 1;
  s5 += s4 >> 25;
  s4 &= ((int64_t)1 << 25) - 1;
  s6 += s5 >> 25;
  s5 &= ((int64_t)1 << 25) - 1;
  s7 += s6 >> 25;
  s6 &= ((int64_t)1 << 25) - 1;
  s8 += s7 >> 25;
  s7 &= ((int64_t)1 << 25) - 1;
  s9 += s8 >> 25;
  s8 &= ((int64_t)1 << 25) - 1;
  s0 += s9 >> 25;
  s9 &= ((int64_t)1 << 25) - 1;

  r->v[0] = (int32_t)s0;
  r->v[1] = (int32_t)s1;
  r->v[2] = (int32_t)s2;
  r->v[3] = (int32_t)s3;
  r->v[4] = (int32_t)s4;
  r->v[5] = (int32_t)s5;
  r->v[6] = (int32_t)s6;
  r->v[7] = (int32_t)s7;
  r->v[8] = (int32_t)s8;
  r->v[9] = (int32_t)s9;
}