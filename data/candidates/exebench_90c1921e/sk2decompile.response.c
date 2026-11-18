void ifft8pt(float *a, float scale) {
  float a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15,
      b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11, b12, b13, b14, b15, c0,
      c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, d0, d1,
      d2, d3, d4, d5, d6, d7, d8, d9, d10, d11, d12, d13, d14, d15, e0, e1, e2,
      e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, f0, f1, f2, f3,
      f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, g0, g1, g2, g3, g4,
      g5, g6, g7, g8, g9, g10, g11, g12, g13, g14, g15, h0, h1, h2, h3, h4, h5,
      h6, h7, h8, h9, h10, h11, h12, h13, h14, h15, i0, i1, i2, i3, i4, i5, i6,
      i7, i8, i9, i10, i11, i12, i13, i14, i15, j0, j1, j2, j3, j4, j5, j6, j7,
      j8, j9, j10, j11, j12, j13, j14, j15, k0, k1, k2, k3, k4, k5, k6, k7, k8,
      k9, k10, k11, k12, k13, k14, k15, l0, l1, l2, l3, l4, l5, l6, l7, l8, l9,
      l10, l11, l12, l13, l14, l15, m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,
      m11, m12, m13, m14, m15, n0, n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11,
      n12, n13, n14, n15, o0, o1, o2, o3, o4, o5, o6, o7, o8, o9, o10, o11, o12,
      o13, o14, o15, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13,
      p14, p15, q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14,
      q15, r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15,
      s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, t0,
      t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, u0, u1,
      u2, u3, u4, u5, u6, u7, u8, u9, u10, u11, u12, u13, u14, u15, v0, v1, v2,
      v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, w0, w1, w2, w3,
      w4, w5, w6, w7, w8, w9, w10, w11, w12, w13, w14, w15, x0, x1, x2, x3, x4,
      x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, y0, y1, y2, y3, y4, y5,
      y6, y7, y8, y9, y10, y11, y12, y13, y14, y15, z0, z1, z2, z3, z4, z5, z6,
      z7, z8, z9, z10, z11, z12, z13, z14, z15;
  a0 = a[0];
  a1 = a[1];
  a2 = a[2];
  a3 = a[3];
  a4 = a[4];
  a5 = a[5];
  a6 = a[6];
  a7 = a[7];
  a8 = a[8];
  a9 = a[9];
  a10 = a[10];
  a11 = a[11];
  a12 = a[12];
  a13 = a[13];
  a14 = a[14];
  a15 = a[15];
  b0 = a0 + a8;
  b1 = a1 + a9;
  b2 = a0 - a8;
  b3 = a1 - a9;
  b4 = a2 - a6;
  b5 = a3 - a7;
  b6 = a2 + a6;
  b7 = a3 + a7;
  a0 = b0 + b6;
  a1 = b1 + b7;
  b8 = b0 - b6;
  b9 = b1 - b7;
  b10 = b2 + b5;
  b11 = b3 - b4;
  b2 = b2 - b5;
  b3 = b3 + b4;
  b12 = a4 + a10;
  b13 = a5 + a11;
  b14 = a4 - a10;
  b15 = a5 - a11;
  c0 = a6 - a12;
  c1 = a7 - a13;
  c2 = a6 + a12;
  c3 = a7 + a13;
  a4 = b12 + c2;
  a5 = b13 + c3;
  b12 = b12 - c2;
  b13 = b13 - c3;
  c4 = b2 + b11;
  c5 = b3 - b10;
  b2 = b2 - b11;
  b3 = b3 + b10;
  c6 = b8 + b15;
  c7 = b9 - b14;
  b8 = b8 - b15;
  b9 = b9 + b14;
  c8 = b2 + c5;
  c9 = b3 - c4;
  b2 = b2 - c5;
  b3 = b3 + c4;
  c10 = b8 + c7;
  c11 = b9 - c6;
  b8 = b8 - c7;
  b9 = b9 + c6;
  c12 = b2 + c9;
  c13 = b3 - c8;
  b2 = b2 - c9;
  b3 = b3 + c8;
  c14 = b8 + c11;
  c15 = b9 - c10;
  b8 = b8 - c11;
  b9 = b9 + c10;
  d0 = a0 + a4;
  d1 = a1 + a5;
  d2 = a0 - a4;
  d3 = a1 - a5;
  d4 = b0 + b12;
  d5 = b1 + b13;
  b0 = b0 - b12;
  b1 = b1 - b13;
  d6 = b2 + c13;
  d7 = b3 - c12;
  b2 = b2 - c13;
  b3 = b3 + c12;
  d8 = b0 + d5;
  d9 = b1 + d6;
  b0 = b0 - d5;
  b1 = b1 - d6;
  d10 = b2 + d7;
  d11 = b3 - d8;
  b2 = b2 - d7;
  b3 = b3 + d8;
  d12 = b2 + d11;
  d13 = b3 - d10;
  b2 = b2 - d11;
  b3 = b3 + d10;
  d14 = b8 + d15;
  d15 = b9 - d14;
  b8 = b8 - d15;
  b9 = b9 + d14;
  e0 = a8 + a12;
  e1 = a9 + a13;
  e2 = a8 - a12;
  e3 = a9 - a13;
  e4 = b8 + b12;
  e5 = b9 + b13;
  e6 = b8 - b12;
  e7 = b9 - b13;
  e8 = c0 + c2;
  e9 = c1 + c3;
  e10 = c0 - c2;
  e11 = c1 - c3;
  e12 = d0 + d2;
  e13 = d1 + d3;
  e14 = d0 - d2;
  e15 = d1 - d3;
  f0 = b0 + e5;
  f1 = b1 + e6;
  f2 = b0 - e5;
  f3 = b1 - e6;
  f4 = c8 + e9;
  f5 = c9 - e8;
  c8 = c8 - e9;
  c9 = c9 + e8;
  f6 = d8 + e13;
  f7 = d9 - e12;
  d8 = d8 - e13;
  d9 = d9 + e12;
  f8 = b2 + f7;
  f9 = b3 - f6;
  b2 = b2 - f7;
  b3 = b3 + f6;
  f10 = c2 + f5;
  f11 = c3 - f4;
  c2 = c2 - f5;
  c3 = c3 + f4;
  f12 = d2 + f9;
  f13 = d3 - f8;
  d2 = d2 - f9;
  d3 = d3 + f8;
  f14 = c2 + f11;
  f15 = c3 - f10;
  c2 = c2 - f11;
  c3 = c3 + f10;
  g0 = b0 + f1;
  g1 = b1 - f0;
  b0 = b0 - f1;
  b1 = b1 + f0;
  g2 = c8 + f3;
  g3 = c9 - f2;
  c8 = c8 - f3;
  c9 = c9 + f2;
  g4 = d8 + f13;
  g5 = d9 - f12;
  d8 = d8 - f13;
  d9 = d9 + f12;
  g6 = b2 + g5;
  g7 = b3 - g4;
  b2 = b2 - g5;
  b3 = b3 + g4;
  g8 = c2 + g3;
  g9 = c3 - g2;
  c2 = c2 - g3;
  c3 = c3 + g2;
  g10 = d2 + g7;
  g11 = d3 - g6;
  d2 = d2 - g7;
  d3 = d3 + g6;
  g12 = c2 + g9;
  g13 = c3 - g8;
  c2 = c2 - g9;
  c3 = c3 + g8;
  h0 = b0 + g1;
  h1 = b1 - g0;
  b0 = b0 - g1;
  b1 = b1 + g0;
  h2 = c8 + g3;
  h3 = c9 - g2;
  c8 = c8 - g3;
  c9 = c9 + g2;
  h4 = d8 + g13;
  h5 = d9 - g12;
  d8 = d8 - g13;
  d9 = d9 + g12;
  h6 = b2 + h5;
  h7 = b3 - h4;
  b2 = b2 - h5;
  b3 = b3 + h4;
  h8 = c2 + h3;
  h9 = c3 - h2;
  c2 = c2 - h3;
  c3 = c3 + h2;
  h10 = d2 + h7;
  h11 = d3 - h6;
  d2 = d2 - h7;
  d3 = d3 + h6;
  h12 = c2 + h9;
  h13 = c3 - h8;
  c2 = c2 - h9;
  c3 = c3 + h8;
  i0 = b0 + h1;
  i1 = b1 - h0;
  b0 = b0 - h1;
  b1 = b1 + h0;
  i2 = c8 + h3;
  i3 = c9 - h2;
  c8 = c8 - h3;
  c9 = c9 + h2;
  i4 = d8 + h13;
  i5 = d9 - h12;
  d8 = d8 - h13;
  d9 = d9 + h12;
  i6 = b2 + i5;
  i7 = b3 - i4;
  b2 = b2 - i5;
  b3 = b3 + i4;
  i8 = c2 + i3;
  i9 = c3 - i2;
  c2 = c2 - i3;
  c3 = c3 + i2;
  i10 = d2 + i7;
  i11 = d3 - i6;
  d2 = d2 - i7;
  d3 = d3 + i6;
  i12 = c2 + i9;
  i13 = c3 - i8;
  c2 = c2 - i9;
  c3 = c3 + i8;
  j0 = b0 + i1;
  j1 = b1 - i0;
  b0 = b0 - i1;
  b1 = b1 + i0;
  j2 = c8 + i3;
  j3 = c9 - i2;
  c8 =