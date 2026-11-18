void cftf161(float *a, float *w) {
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
      a79i, a80r, a80i, a81r, a81i, a82r, a82i, a83r, a83i, a84r, a84i, a85r,
      a85i, a86r, a86i, a87r, a87i, a88r, a88i, a89r, a89i, a90r, a90i, a91r,
      a91i, a92r, a92i, a93r, a93i, a94r, a94i, a95r, a95i, a96r, a96i, a97r,
      a97i, a98r, a98i, a99r, a99i, a100r, a100i, a101r, a101i, a102r, a102i,
      a103r, a103i, a104r, a104i, a105r, a105i, a106r, a106i, a107r, a107i,
      a108r, a108i, a109r, a109i, a110r, a110i, a111r, a111i, a112r, a112i,
      a113r, a113i, a114r, a114i, a115r, a115i, a116r, a116i, a117r, a117i,
      a118r, a118i, a119r, a119i, a120r, a120i, a121r, a121i, a122r, a122i,
      a123r, a123i, a124r, a124i, a125r, a125i, a126r, a126i, a127r, a127i,
      a128r, a128i, a129r, a129i, a130r, a130i, a131r, a131i, a132r, a132i,
      a133r, a133i, a134r, a134i, a135r, a135i, a136r, a136i, a137r, a137i,
      a138r, a138i, a139r, a139i, a140r, a140i, a141r, a141i, a142r, a142i,
      a143r, a143i, a144r, a144i, a145r, a145i, a146r, a146i, a147r, a147i,
      a148r, a148i, a149r, a149i, a150r, a150i, a151r, a151i, a152r, a152i,
      a153r, a153i, a154r, a154i, a155r, a155i, a156r, a156i, a157r, a157i,
      a158r, a158i, a159r, a159i, a160r, a160i, a161r, a161i;
  a0r = a[0];
  a0i = a[1];
  a1r = a[16];
  a1i = a[17];
  a2r = a[8];
  a2i = a[9];
  a3r = a[24];
  a3i = a[25];
  a4r = a0r + a1r;
  a4i = a0i + a1i;
  a5r = a0r - a1r;
  a5i = a0i - a1i;
  a6r = a2r + a3r;
  a6i = a2i + a3i;
  a7r = a2r - a3r;
  a7i = a2i - a3i;
  a8r = a4r + a6r;
  a8i = a4i + a6i;
  a9r = a4r - a6r;
  a9i = a4i - a6i;
  a10r = a5r - a7i;
  a10i = a5i + a7r;
  a11r = a5r + a7i;
  a11i = a5i - a7r;
  a12r = a[2];
  a12i = a[3];
  a13r = a[18];
  a13i = a[19];
  a14r = a[10];
  a14i = a[11];
  a15r = a[26];
  a15i = a[27];
  a16r = a12r + a13r;
  a16i = a12i + a13i;
  a17r = a12r - a13r;
  a17i = a12i - a13i;
  a18r = a14r + a15r;
  a18i = a14i + a15i;
  a19r = a14r - a15r;
  a19i = a14i - a15i;
  a20r = a16r + a18r;
  a20i = a16i + a18i;
  a21r = a16r - a18r;
  a21i = a16i - a18i;
  a22r = a17i - a19i;
  a22i = a17r + a19r;
  a23r = a17r + a19i;
  a23i = a17i - a19r;
  a24r = a8r + a20r;
  a24i = a8i + a20i;
  a25r = a8r - a20r;
  a25i = a8i - a20i;
  a26r = a9r - a21i;
  a26i = a9i + a21r;
  a27r = a9r + a21i;
  a27i = a9i - a21r;
  a28r = a[4];
  a28i = a[5];
  a29r = a[20];
  a29i = a[21];
  a30r = a[12];
  a30i = a[13];
  a31r = a[28];
  a31i = a[29];
  a32r = a28r + a29r;
  a32i = a28i + a29i;
  a33r = a28r - a29r;
  a33i = a28i - a29i;
  a34r = a30r + a31r;
  a34i = a30i + a31i;
  a35r = a30r - a31r;
  a35i = a30i - a31i;
  a36r = a32r + a34r;
  a36i = a32i + a34i;
  a37r = a32r - a34r;
  a37i = a32i - a34i;
  a38r = a33i - a35i;
  a38i = a33r + a35r;
  a39r = a33r + a35i;
  a39i = a33i - a35r;
  a40r = a24r + a36r;
  a40i = a24i + a36i;
  a41r = a24r - a36r;
  a41i = a24i - a36i;
  a42r = a25r - a37i;
  a42i = a25i + a37r;
  a43r = a25r + a37i;
  a43i = a25i - a37r;
  a44r = w[1];
  a44i = w[2];
  a45r = w[3];
  a45i = w[4];
  a46r = a44r * a39i;
  a46i = a45r * a39i;
  a47r = a44i * a39i;
  a47i = a45i * a39i;
  a48r = a44r * a38r;
  a48i = a45r * a38r;
  a49r = a44i * a38r;
  a49i = a45i * a38r;
  a50r = a44r * a37r;
  a50i = a45r * a37r;
  a51r = a44i * a37r;
  a51i = a45i * a37r;
  a52r = a44r * a36r;
  a52i = a45r * a36r;
  a53r = a44i * a36r;
  a53i = a45i * a36r;
  a54r = a46r - a48i;
  a54i = a46i - a48r;
  a55r = a47r - a49i;
  a55i = a47i - a49r;
  a56r = a46r + a48i;
  a56i = a46i + a48r;
  a57r = a47r + a49i;
  a57i = a47i + a49r;
  a58r = a48r - a50i;
  a58i = a49r - a51i;
  a59r = a51r - a53i;
  a59i = a51i - a53r;
  a60r = a48r + a50i;
  a60i = a49r + a51i;
  a61r = a51r + a53i;
  a61i = a51i + a53r;
  a62r = a52i - a54r;
  a62i = a53r - a55r;
  a63r = a54r - a56r;
  a63i = a55r - a57r;
  a64r = a52i + a54r;
  a64i = a53r + a55r;
  a65r = a54r + a56r;
  a65i = a55r + a57r;
  a[24] = a56r + a60r;
  a[25] = a56i + a60i;
  a[26] = a56r - a60r;
  a[27] = a56i - a60i;
  a[28] = a57r - a61i;
  a[29] = a57i + a61r;
  a[30] = a57r + a61i;
  a[31] = a57i - a61r;
  a[16] = a40r + a58r;
  a[17] = a40i + a58i;
  a[18] = a40r - a58r;
  a[19] = a40i - a58i;
  a[20] = a41r - a59i;
  a[21] = a42i + a59r;
  a[22] = a41r