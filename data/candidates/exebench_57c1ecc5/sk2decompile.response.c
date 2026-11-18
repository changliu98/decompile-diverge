void cftf081(float *a) {
  float a0r, a0i, a1r, a1i, a2r, a2i, a3r, a3i, a4r, a4i, a5r, a5i, a6r, a6i,
      a7r, a7i, a8r, a8i, a9r, a9i, a10r, a10i, a11r, a11i, a12r, a12i, a13r,
      a13i, a14r, a14i, a15r, a15i, a16r, a16i, a17r, a17i, a18r, a18i, a19r,
      a19i, a20r, a20i, a21r, a21i, a22r, a22i, a23r, a23i, a24r, a24i, a25r,
      a25i, a26r, a26i, a27r, a27i, a28r, a28i, a29r, a29i, a30r, a30i, a31r,
      a31i, a32r, a32i, a33r, a33i, a34r, a34i, a35r, a35i, a36r, a36i, a37r,
      a37i, a38r, a38i, a39r, a39i, a40r, a40i, a41r, a41i, a42r, a42i, a43r,
      a43i, a44r, a44i, a45r, a45i, a46r, a46i, a47r, a47i, a48r, a48i, a49r,
      a49i, a50r, a50i, a51r, a51i, a52r, a52i, a53r, a53i, a54r, a54i, a55r,
      a55i, a56r, a56i, a57r, a57i, a58r, a58i, a59r, a59i, a60r, a60i, a61r,
      a61i, a62r, a62i, a63r, a63i, a64r, a64i, a65r, a65i, a66r, a66i, a67r,
      a67i, a68r, a68i, a69r, a69i, a70r, a70i, a71r, a71i, a72r, a72i, a73r,
      a73i, a74r, a74i, a75r, a75i, a76r, a76i, a77r, a77i, a78r, a78i, a79r,
      a79i, a80r, a80i, a81r, a81i;
  a0r = a[0];
  a0i = a[1];
  a1r = a[2];
  a1i = a[3];
  a2r = a[4];
  a2i = a[5];
  a3r = a[6];
  a3i = a[7];
  a4r = a[8];
  a4i = a[9];
  a5r = a[10];
  a5i = a[11];
  a6r = a[12];
  a6i = a[13];
  a7r = a[14];
  a7i = a[15];
  a8r = a0r + a4r;
  a8i = a0i + a4i;
  a9r = a0r - a4r;
  a9i = a0i - a4i;
  a10r = a2r + a6r;
  a10i = a2i + a6i;
  a11r = a2r - a6r;
  a11i = a2i - a6i;
  a12r = a8r + a10r;
  a12i = a8i + a10i;
  a13r = a8r - a10r;
  a13i = a8i - a10i;
  a14r = a9r - a11i;
  a14i = a9i + a11r;
  a15r = a9r + a11i;
  a15i = a9i - a11r;
  a16r = a1r + a5r;
  a16i = a1i + a5i;
  a17r = a1r - a5r;
  a17i = a1i - a5i;
  a18r = a3r + a7r;
  a18i = a3i + a7i;
  a19r = a3r - a7r;
  a19i = a3i - a7i;
  a20r = a16r + a18r;
  a20i = a16i + a18i;
  a21r = a16r - a18r;
  a21i = a16i - a18i;
  a22r = a17r - a19i;
  a22i = a17i + a19r;
  a23r = a17r + a19i;
  a23i = a17i - a19r;
  a[8] = a20r + a22r;
  a[9] = a20i + a22i;
  a[10] = a20r - a22r;
  a[11] = a20i - a22i;
  a[12] = a21r - a23i;
  a[13] = a21i + a23r;
  a[14] = a21r + a23i;
  a[15] = a21i - a23r;
  a[0] = a12r + a20r;
  a[1] = a12i + a20i;
  a[2] = a12r - a20r;
  a[3] = a12i - a20i;
  a[4] = a13r - a21i;
  a[5] = a13i + a21r;
  a[6] = a13r + a21i;
  a[7] = a13i - a21r;
}