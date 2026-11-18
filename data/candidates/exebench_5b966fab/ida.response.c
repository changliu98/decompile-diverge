void __cdecl load_inv(float *I, const float *M)
{
  __m128i v2; // xmm0
  float v3; // xmm2_4
  __m128i v4; // xmm0
  __m128i v5; // xmm4
  __m128i v6; // xmm3
  __m128i v7; // xmm0
  float v8; // xmm2_4
  __m128i v9; // xmm0
  __m128i v10; // xmm4
  float v11; // xmm1_4
  __m128i v12; // xmm0
  __m128i v13; // xmm3
  __m128i v14; // xmm0
  float v15; // xmm2_4
  __m128i v16; // xmm0
  __m128i v17; // xmm4
  __m128i v18; // xmm3
  __m128i v19; // xmm0
  float v20; // xmm2_4
  __m128i v21; // xmm0
  __m128i v22; // xmm4
  float v23; // xmm1_4
  __m128i v24; // xmm0
  __m128i v25; // xmm3
  __m128i v26; // xmm0
  float v27; // xmm2_4
  __m128i v28; // xmm0
  __m128i v29; // xmm4
  float v30; // xmm1_4
  __m128i v31; // xmm0
  __m128i v32; // xmm3
  __m128i v33; // xmm0
  float v34; // xmm2_4
  __m128i v35; // xmm0
  __m128i v36; // xmm4
  __m128i v37; // xmm3
  __m128i v38; // xmm0
  float v39; // xmm2_4
  __m128i v40; // xmm0
  __m128i v41; // xmm4
  float v42; // xmm1_4
  __m128i v43; // xmm0
  __m128i v44; // xmm3
  __m128i v45; // xmm0
  float v46; // xmm2_4
  __m128i v47; // xmm0
  __m128i v48; // xmm4
  __m128i v49; // xmm3
  __m128i v50; // xmm0
  float v51; // xmm2_4
  __m128i v52; // xmm0
  __m128i v53; // xmm4
  __m128i v54; // xmm3
  __m128i v55; // xmm0
  float v56; // xmm2_4
  __m128i v57; // xmm0
  __m128i v58; // xmm4
  float v59; // xmm1_4
  __m128i v60; // xmm0
  __m128i v61; // xmm3
  __m128i v62; // xmm0
  float v63; // xmm2_4
  __m128i v64; // xmm0
  __m128i v65; // xmm4
  __m128i v66; // xmm3
  __m128i v67; // xmm0
  float v68; // xmm2_4
  __m128i v69; // xmm0
  __m128i v70; // xmm4
  float v71; // xmm1_4
  __m128i v72; // xmm0
  __m128i v73; // xmm3
  __m128i v74; // xmm0
  float v75; // xmm2_4
  __m128i v76; // xmm0
  __m128i v77; // xmm4
  float v78; // xmm1_4
  __m128i v79; // xmm0
  __m128i v80; // xmm3
  __m128i v81; // xmm0
  float v82; // xmm2_4
  __m128i v83; // xmm0
  __m128i v84; // xmm4
  __m128i v85; // xmm3
  __m128i v86; // xmm0
  float v87; // xmm2_4
  __m128i v88; // xmm0
  __m128i v89; // xmm4
  float v90; // xmm1_4
  __m128i v91; // xmm0
  __m128i v92; // xmm3
  __m128i v93; // xmm0
  float v94; // xmm2_4
  __m128i v95; // xmm0
  __m128i v96; // xmm4
  __m128i v97; // xmm3
  float d; // [rsp+0h] [rbp-54h]
  float T; // [rsp+4h] [rbp-50h]
  float T_4; // [rsp+8h] [rbp-4Ch]
  float T_8; // [rsp+Ch] [rbp-48h]
  float T_12; // [rsp+10h] [rbp-44h]
  float T_16; // [rsp+14h] [rbp-40h]
  float T_20; // [rsp+18h] [rbp-3Ch]
  float T_24; // [rsp+1Ch] [rbp-38h]
  float T_28; // [rsp+20h] [rbp-34h]
  float T_32; // [rsp+24h] [rbp-30h]
  float T_36; // [rsp+28h] [rbp-2Ch]
  float T_40; // [rsp+2Ch] [rbp-28h]
  float T_44; // [rsp+30h] [rbp-24h]
  float T_48; // [rsp+34h] [rbp-20h]
  float T_52; // [rsp+38h] [rbp-1Ch]
  float T_56; // [rsp+3Ch] [rbp-18h]
  float T_60; // [rsp+40h] [rbp-14h]

  v2 = (__m128i)*((unsigned int *)M + 11);
  *(float *)v2.m128i_i32 = *(float *)v2.m128i_i32 * M[14];
  v3 = (float)(M[10] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v2) ^ 0x80000000);
  v4 = (__m128i)*((unsigned int *)M + 9);
  v5 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v5.m128i_i32 = *(float *)v5.m128i_i32 * M[14];
  *(float *)v4.m128i_i32 = *(float *)v4.m128i_i32
                         * (float)((float)(M[6] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v5) ^ 0x80000000));
  v6 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v6.m128i_i32 = *(float *)v6.m128i_i32 * M[10];
  T = (float)(M[13] * (float)((float)(M[6] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v6) ^ 0x80000000)))
    + (float)((float)(M[5] * v3) + COERCE_FLOAT(_mm_cvtsi128_si32(v4) ^ 0x80000000));
  v7 = (__m128i)*((unsigned int *)M + 11);
  *(float *)v7.m128i_i32 = *(float *)v7.m128i_i32 * M[14];
  v8 = (float)(M[10] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v7) ^ 0x80000000);
  v9 = (__m128i)*((unsigned int *)M + 8);
  v10 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v10.m128i_i32 = *(float *)v10.m128i_i32 * M[14];
  *(float *)v9.m128i_i32 = *(float *)v9.m128i_i32
                         * (float)((float)(M[6] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v10) ^ 0x80000000));
  v11 = (float)(M[4] * v8) + COERCE_FLOAT(_mm_cvtsi128_si32(v9) ^ 0x80000000);
  v12 = (__m128i)*((unsigned int *)M + 12);
  v13 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v13.m128i_i32 = *(float *)v13.m128i_i32 * M[10];
  *(float *)v12.m128i_i32 = (float)(*(float *)v12.m128i_i32
                                  * (float)((float)(M[6] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v13) ^ 0x80000000)))
                          + v11;
  LODWORD(T_4) = _mm_cvtsi128_si32(v12) ^ 0x80000000;
  v14 = (__m128i)*((unsigned int *)M + 11);
  *(float *)v14.m128i_i32 = *(float *)v14.m128i_i32 * M[13];
  v15 = (float)(M[9] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v14) ^ 0x80000000);
  v16 = (__m128i)*((unsigned int *)M + 8);
  v17 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v17.m128i_i32 = *(float *)v17.m128i_i32 * M[13];
  *(float *)v16.m128i_i32 = *(float *)v16.m128i_i32
                          * (float)((float)(M[5] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v17) ^ 0x80000000));
  v18 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v18.m128i_i32 = *(float *)v18.m128i_i32 * M[9];
  T_8 = (float)(M[12] * (float)((float)(M[5] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v18) ^ 0x80000000)))
      + (float)((float)(M[4] * v15) + COERCE_FLOAT(_mm_cvtsi128_si32(v16) ^ 0x80000000));
  v19 = (__m128i)*((unsigned int *)M + 10);
  *(float *)v19.m128i_i32 = *(float *)v19.m128i_i32 * M[13];
  v20 = (float)(M[9] * M[14]) + COERCE_FLOAT(_mm_cvtsi128_si32(v19) ^ 0x80000000);
  v21 = (__m128i)*((unsigned int *)M + 8);
  v22 = (__m128i)*((unsigned int *)M + 6);
  *(float *)v22.m128i_i32 = *(float *)v22.m128i_i32 * M[13];
  *(float *)v21.m128i_i32 = *(float *)v21.m128i_i32
                          * (float)((float)(M[5] * M[14]) + COERCE_FLOAT(_mm_cvtsi128_si32(v22) ^ 0x80000000));
  v23 = (float)(M[4] * v20) + COERCE_FLOAT(_mm_cvtsi128_si32(v21) ^ 0x80000000);
  v24 = (__m128i)*((unsigned int *)M + 12);
  v25 = (__m128i)*((unsigned int *)M + 6);
  *(float *)v25.m128i_i32 = *(float *)v25.m128i_i32 * M[9];
  *(float *)v24.m128i_i32 = (float)(*(float *)v24.m128i_i32
                                  * (float)((float)(M[5] * M[10]) + COERCE_FLOAT(_mm_cvtsi128_si32(v25) ^ 0x80000000)))
                          + v23;
  LODWORD(T_12) = _mm_cvtsi128_si32(v24) ^ 0x80000000;
  v26 = (__m128i)*((unsigned int *)M + 11);
  *(float *)v26.m128i_i32 = *(float *)v26.m128i_i32 * M[14];
  v27 = (float)(M[10] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v26) ^ 0x80000000);
  v28 = (__m128i)*((unsigned int *)M + 9);
  v29 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v29.m128i_i32 = *(float *)v29.m128i_i32 * M[14];
  *(float *)v28.m128i_i32 = *(float *)v28.m128i_i32
                          * (float)((float)(M[2] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v29) ^ 0x80000000));
  v30 = (float)(M[1] * v27) + COERCE_FLOAT(_mm_cvtsi128_si32(v28) ^ 0x80000000);
  v31 = (__m128i)*((unsigned int *)M + 13);
  v32 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v32.m128i_i32 = *(float *)v32.m128i_i32 * M[10];
  *(float *)v31.m128i_i32 = (float)(*(float *)v31.m128i_i32
                                  * (float)((float)(M[2] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v32) ^ 0x80000000)))
                          + v30;
  LODWORD(T_16) = _mm_cvtsi128_si32(v31) ^ 0x80000000;
  v33 = (__m128i)*((unsigned int *)M + 11);
  *(float *)v33.m128i_i32 = *(float *)v33.m128i_i32 * M[14];
  v34 = (float)(M[10] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v33) ^ 0x80000000);
  v35 = (__m128i)*((unsigned int *)M + 8);
  v36 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v36.m128i_i32 = *(float *)v36.m128i_i32 * M[14];
  *(float *)v35.m128i_i32 = *(float *)v35.m128i_i32
                          * (float)((float)(M[2] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v36) ^ 0x80000000));
  v37 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v37.m128i_i32 = *(float *)v37.m128i_i32 * M[10];
  T_20 = (float)(M[12] * (float)((float)(M[2] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v37) ^ 0x80000000)))
       + (float)((float)(*M * v34) + COERCE_FLOAT(_mm_cvtsi128_si32(v35) ^ 0x80000000));
  v38 = (__m128i)*((unsigned int *)M + 11);
  *(float *)v38.m128i_i32 = *(float *)v38.m128i_i32 * M[13];
  v39 = (float)(M[9] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v38) ^ 0x80000000);
  v40 = (__m128i)*((unsigned int *)M + 8);
  v41 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v41.m128i_i32 = *(float *)v41.m128i_i32 * M[13];
  *(float *)v40.m128i_i32 = *(float *)v40.m128i_i32
                          * (float)((float)(M[1] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v41) ^ 0x80000000));
  v42 = (float)(*M * v39) + COERCE_FLOAT(_mm_cvtsi128_si32(v40) ^ 0x80000000);
  v43 = (__m128i)*((unsigned int *)M + 12);
  v44 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v44.m128i_i32 = *(float *)v44.m128i_i32 * M[9];
  *(float *)v43.m128i_i32 = (float)(*(float *)v43.m128i_i32
                                  * (float)((float)(M[1] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v44) ^ 0x80000000)))
                          + v42;
  LODWORD(T_24) = _mm_cvtsi128_si32(v43) ^ 0x80000000;
  v45 = (__m128i)*((unsigned int *)M + 10);
  *(float *)v45.m128i_i32 = *(float *)v45.m128i_i32 * M[13];
  v46 = (float)(M[9] * M[14]) + COERCE_FLOAT(_mm_cvtsi128_si32(v45) ^ 0x80000000);
  v47 = (__m128i)*((unsigned int *)M + 8);
  v48 = (__m128i)*((unsigned int *)M + 2);
  *(float *)v48.m128i_i32 = *(float *)v48.m128i_i32 * M[13];
  *(float *)v47.m128i_i32 = *(float *)v47.m128i_i32
                          * (float)((float)(M[1] * M[14]) + COERCE_FLOAT(_mm_cvtsi128_si32(v48) ^ 0x80000000));
  v49 = (__m128i)*((unsigned int *)M + 2);
  *(float *)v49.m128i_i32 = *(float *)v49.m128i_i32 * M[9];
  T_28 = (float)(M[12] * (float)((float)(M[1] * M[10]) + COERCE_FLOAT(_mm_cvtsi128_si32(v49) ^ 0x80000000)))
       + (float)((float)(*M * v46) + COERCE_FLOAT(_mm_cvtsi128_si32(v47) ^ 0x80000000));
  v50 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v50.m128i_i32 = *(float *)v50.m128i_i32 * M[14];
  v51 = (float)(M[6] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v50) ^ 0x80000000);
  v52 = (__m128i)*((unsigned int *)M + 5);
  v53 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v53.m128i_i32 = *(float *)v53.m128i_i32 * M[14];
  *(float *)v52.m128i_i32 = *(float *)v52.m128i_i32
                          * (float)((float)(M[2] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v53) ^ 0x80000000));
  v54 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v54.m128i_i32 = *(float *)v54.m128i_i32 * M[6];
  T_32 = (float)(M[13] * (float)((float)(M[2] * M[7]) + COERCE_FLOAT(_mm_cvtsi128_si32(v54) ^ 0x80000000)))
       + (float)((float)(M[1] * v51) + COERCE_FLOAT(_mm_cvtsi128_si32(v52) ^ 0x80000000));
  v55 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v55.m128i_i32 = *(float *)v55.m128i_i32 * M[14];
  v56 = (float)(M[6] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v55) ^ 0x80000000);
  v57 = (__m128i)*((unsigned int *)M + 4);
  v58 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v58.m128i_i32 = *(float *)v58.m128i_i32 * M[14];
  *(float *)v57.m128i_i32 = *(float *)v57.m128i_i32
                          * (float)((float)(M[2] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v58) ^ 0x80000000));
  v59 = (float)(*M * v56) + COERCE_FLOAT(_mm_cvtsi128_si32(v57) ^ 0x80000000);
  v60 = (__m128i)*((unsigned int *)M + 12);
  v61 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v61.m128i_i32 = *(float *)v61.m128i_i32 * M[6];
  *(float *)v60.m128i_i32 = (float)(*(float *)v60.m128i_i32
                                  * (float)((float)(M[2] * M[7]) + COERCE_FLOAT(_mm_cvtsi128_si32(v61) ^ 0x80000000)))
                          + v59;
  LODWORD(T_36) = _mm_cvtsi128_si32(v60) ^ 0x80000000;
  v62 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v62.m128i_i32 = *(float *)v62.m128i_i32 * M[13];
  v63 = (float)(M[5] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v62) ^ 0x80000000);
  v64 = (__m128i)*((unsigned int *)M + 4);
  v65 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v65.m128i_i32 = *(float *)v65.m128i_i32 * M[13];
  *(float *)v64.m128i_i32 = *(float *)v64.m128i_i32
                          * (float)((float)(M[1] * M[15]) + COERCE_FLOAT(_mm_cvtsi128_si32(v65) ^ 0x80000000));
  v66 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v66.m128i_i32 = *(float *)v66.m128i_i32 * M[5];
  T_40 = (float)(M[12] * (float)((float)(M[1] * M[7]) + COERCE_FLOAT(_mm_cvtsi128_si32(v66) ^ 0x80000000)))
       + (float)((float)(*M * v63) + COERCE_FLOAT(_mm_cvtsi128_si32(v64) ^ 0x80000000));
  v67 = (__m128i)*((unsigned int *)M + 6);
  *(float *)v67.m128i_i32 = *(float *)v67.m128i_i32 * M[13];
  v68 = (float)(M[5] * M[14]) + COERCE_FLOAT(_mm_cvtsi128_si32(v67) ^ 0x80000000);
  v69 = (__m128i)*((unsigned int *)M + 4);
  v70 = (__m128i)*((unsigned int *)M + 2);
  *(float *)v70.m128i_i32 = *(float *)v70.m128i_i32 * M[13];
  *(float *)v69.m128i_i32 = *(float *)v69.m128i_i32
                          * (float)((float)(M[1] * M[14]) + COERCE_FLOAT(_mm_cvtsi128_si32(v70) ^ 0x80000000));
  v71 = (float)(*M * v68) + COERCE_FLOAT(_mm_cvtsi128_si32(v69) ^ 0x80000000);
  v72 = (__m128i)*((unsigned int *)M + 12);
  v73 = (__m128i)*((unsigned int *)M + 2);
  *(float *)v73.m128i_i32 = *(float *)v73.m128i_i32 * M[5];
  *(float *)v72.m128i_i32 = (float)(*(float *)v72.m128i_i32
                                  * (float)((float)(M[1] * M[6]) + COERCE_FLOAT(_mm_cvtsi128_si32(v73) ^ 0x80000000)))
                          + v71;
  LODWORD(T_44) = _mm_cvtsi128_si32(v72) ^ 0x80000000;
  v74 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v74.m128i_i32 = *(float *)v74.m128i_i32 * M[10];
  v75 = (float)(M[6] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v74) ^ 0x80000000);
  v76 = (__m128i)*((unsigned int *)M + 5);
  v77 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v77.m128i_i32 = *(float *)v77.m128i_i32 * M[10];
  *(float *)v76.m128i_i32 = *(float *)v76.m128i_i32
                          * (float)((float)(M[2] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v77) ^ 0x80000000));
  v78 = (float)(M[1] * v75) + COERCE_FLOAT(_mm_cvtsi128_si32(v76) ^ 0x80000000);
  v79 = (__m128i)*((unsigned int *)M + 9);
  v80 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v80.m128i_i32 = *(float *)v80.m128i_i32 * M[6];
  *(float *)v79.m128i_i32 = (float)(*(float *)v79.m128i_i32
                                  * (float)((float)(M[2] * M[7]) + COERCE_FLOAT(_mm_cvtsi128_si32(v80) ^ 0x80000000)))
                          + v78;
  LODWORD(T_48) = _mm_cvtsi128_si32(v79) ^ 0x80000000;
  v81 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v81.m128i_i32 = *(float *)v81.m128i_i32 * M[10];
  v82 = (float)(M[6] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v81) ^ 0x80000000);
  v83 = (__m128i)*((unsigned int *)M + 4);
  v84 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v84.m128i_i32 = *(float *)v84.m128i_i32 * M[10];
  *(float *)v83.m128i_i32 = *(float *)v83.m128i_i32
                          * (float)((float)(M[2] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v84) ^ 0x80000000));
  v85 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v85.m128i_i32 = *(float *)v85.m128i_i32 * M[6];
  T_52 = (float)(M[8] * (float)((float)(M[2] * M[7]) + COERCE_FLOAT(_mm_cvtsi128_si32(v85) ^ 0x80000000)))
       + (float)((float)(*M * v82) + COERCE_FLOAT(_mm_cvtsi128_si32(v83) ^ 0x80000000));
  v86 = (__m128i)*((unsigned int *)M + 7);
  *(float *)v86.m128i_i32 = *(float *)v86.m128i_i32 * M[9];
  v87 = (float)(M[5] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v86) ^ 0x80000000);
  v88 = (__m128i)*((unsigned int *)M + 4);
  v89 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v89.m128i_i32 = *(float *)v89.m128i_i32 * M[9];
  *(float *)v88.m128i_i32 = *(float *)v88.m128i_i32
                          * (float)((float)(M[1] * M[11]) + COERCE_FLOAT(_mm_cvtsi128_si32(v89) ^ 0x80000000));
  v90 = (float)(*M * v87) + COERCE_FLOAT(_mm_cvtsi128_si32(v88) ^ 0x80000000);
  v91 = (__m128i)*((unsigned int *)M + 8);
  v92 = (__m128i)*((unsigned int *)M + 3);
  *(float *)v92.m128i_i32 = *(float *)v92.m128i_i32 * M[5];
  *(float *)v91.m128i_i32 = (float)(*(float *)v91.m128i_i32
                                  * (float)((float)(M[1] * M[7]) + COERCE_FLOAT(_mm_cvtsi128_si32(v92) ^ 0x80000000)))
                          + v90;
  LODWORD(T_56) = _mm_cvtsi128_si32(v91) ^ 0x80000000;
  v93 = (__m128i)*((unsigned int *)M + 6);
  *(float *)v93.m128i_i32 = *(float *)v93.m128i_i32 * M[9];
  v94 = (float)(M[5] * M[10]) + COERCE_FLOAT(_mm_cvtsi128_si32(v93) ^ 0x80000000);
  v95 = (__m128i)*((unsigned int *)M + 4);
  v96 = (__m128i)*((unsigned int *)M + 2);
  *(float *)v96.m128i_i32 = *(float *)v96.m128i_i32 * M[9];
  *(float *)v95.m128i_i32 = *(float *)v95.m128i_i32
                          * (float)((float)(M[1] * M[10]) + COERCE_FLOAT(_mm_cvtsi128_si32(v96) ^ 0x80000000));
  v97 = (__m128i)*((unsigned int *)M + 2);
  *(float *)v97.m128i_i32 = *(float *)v97.m128i_i32 * M[5];
  T_60 = (float)(M[8] * (float)((float)(M[1] * M[6]) + COERCE_FLOAT(_mm_cvtsi128_si32(v97) ^ 0x80000000)))
       + (float)((float)(*M * v94) + COERCE_FLOAT(_mm_cvtsi128_si32(v95) ^ 0x80000000));
  d = (float)(M[12] * T_48) + (float)((float)(M[8] * T_32) + (float)((float)(*M * T) + (float)(M[4] * T_16)));
  *I = T / d;
  I[1] = T_16 / d;
  I[2] = T_32 / d;
  I[3] = T_48 / d;
  I[4] = T_4 / d;
  I[5] = T_20 / d;
  I[6] = T_36 / d;
  I[7] = T_52 / d;
  I[8] = T_8 / d;
  I[9] = T_24 / d;
  I[10] = T_40 / d;
  I[11] = T_56 / d;
  I[12] = T_12 / d;
  I[13] = T_28 / d;
  I[14] = T_44 / d;
  I[15] = T_60 / d;
}