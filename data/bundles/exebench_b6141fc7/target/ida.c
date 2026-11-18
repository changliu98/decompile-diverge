void __cdecl R16SRFFT(float *input, float *output)
{
  float v2; // xmm0_4
  float v3; // xmm0_4
  float v4; // xmm0_4
  float v5; // xmm0_4
  float v6; // xmm0_4
  float v7; // xmm0_4
  float v8; // xmm0_4
  float v9; // xmm0_4
  float v10; // xmm0_4
  float v11; // xmm0_4
  float out15; // [rsp+0h] [rbp-54h]
  float out15a; // [rsp+0h] [rbp-54h]
  float out14; // [rsp+4h] [rbp-50h]
  float out14a; // [rsp+4h] [rbp-50h]
  float out14b; // [rsp+4h] [rbp-50h]
  float out13; // [rsp+8h] [rbp-4Ch]
  float out13a; // [rsp+8h] [rbp-4Ch]
  float out13b; // [rsp+8h] [rbp-4Ch]
  float out12; // [rsp+Ch] [rbp-48h]
  float out11; // [rsp+10h] [rbp-44h]
  float out11a; // [rsp+10h] [rbp-44h]
  float out11b; // [rsp+10h] [rbp-44h]
  float out10; // [rsp+14h] [rbp-40h]
  float out10a; // [rsp+14h] [rbp-40h]
  float out9; // [rsp+18h] [rbp-3Ch]
  float out9a; // [rsp+18h] [rbp-3Ch]
  float out9b; // [rsp+18h] [rbp-3Ch]
  float out8; // [rsp+1Ch] [rbp-38h]
  float out7; // [rsp+20h] [rbp-34h]
  float out7a; // [rsp+20h] [rbp-34h]
  float out6; // [rsp+24h] [rbp-30h]
  float out6a; // [rsp+24h] [rbp-30h]
  float out5; // [rsp+28h] [rbp-2Ch]
  float out5a; // [rsp+28h] [rbp-2Ch]
  float out5b; // [rsp+28h] [rbp-2Ch]
  float out5c; // [rsp+28h] [rbp-2Ch]
  float out4; // [rsp+2Ch] [rbp-28h]
  float out4a; // [rsp+2Ch] [rbp-28h]
  float out3; // [rsp+30h] [rbp-24h]
  float out3a; // [rsp+30h] [rbp-24h]
  float out2; // [rsp+34h] [rbp-20h]
  float out2a; // [rsp+34h] [rbp-20h]
  float out1; // [rsp+38h] [rbp-1Ch]
  float out1a; // [rsp+38h] [rbp-1Ch]
  float out1b; // [rsp+38h] [rbp-1Ch]
  float out0; // [rsp+3Ch] [rbp-18h]
  float out0a; // [rsp+3Ch] [rbp-18h]
  float temp; // [rsp+40h] [rbp-14h]
  float tempa; // [rsp+40h] [rbp-14h]

  out0 = *input + input[8];
  out1 = input[1] + input[9];
  out2 = input[2] + input[10];
  out3 = input[3] + input[11];
  out4 = input[4] + input[12];
  out5 = input[5] + input[13];
  out6 = input[6] + input[14];
  out7 = input[7] + input[15];
  out9 = input[1] - input[9];
  out11 = input[3] - input[11];
  out13 = input[13] - input[5];
  out15 = input[15] - input[7];
  v2 = (float)(out13 - out9) * 0.3826834323650898;
  temp = v2;
  v3 = out9 * 1.306562964876377 + v2;
  out9a = v3;
  v4 = out13 * 0.5411961001461969 + temp;
  out13a = v4;
  v5 = (float)(input[14] - input[6]) * 0.7071067811865475;
  out14 = v5;
  v6 = (float)(input[2] - input[10]) * 0.7071067811865475;
  out14a = out14 - v6;
  out10 = (float)(out14a + v6) + v6;
  v7 = (float)(out15 - out11) * 0.9238795325112867;
  tempa = v7;
  v8 = out11 * 1.306562964876377 + v7;
  out11a = v8;
  v9 = out15 * -0.5411961001461969 + tempa;
  out8 = out10 + (float)(*input - input[8]);
  out10a = (float)(out8 - out10) - out10;
  out12 = out14a + (float)(input[12] - input[4]);
  out14b = (float)(out12 - out14a) - out14a;
  out9b = out11a + out9a;
  out11b = (float)(out9b - out11a) - out11a;
  out13b = v9 + out13a;
  out15a = (float)(out13b - v9) - v9;
  output[1] = out8 + out9b;
  output[7] = out8 - out9b;
  output[9] = out12 + out13b;
  output[15] = out13b - out12;
  output[5] = out10a + out15a;
  output[13] = out14b - out11b;
  output[3] = out10a - out15a;
  output[11] = COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(out14b)) ^ 0x80000000) - out11b;
  out0a = out0 + out4;
  out4a = (float)(out0a - out4) - out4;
  out1a = out1 + out5;
  out5a = (float)(out1a - out5) - out5;
  out2a = out6 + out2;
  out6a = (float)(out2a - out6) - out6;
  out3a = out7 + out3;
  *output = out0a + out2a;
  output[4] = out0a - out2a;
  out1b = out3a + out1a;
  output[12] = (float)(out3a + out3a) - out1b;
  *output = out1b + *output;
  output[8] = (float)(*output - out1b) - out1b;
  v10 = out5a * 0.7071067811865475;
  out5b = v10;
  v11 = (float)((float)(out3a - out7) - out7) * 0.7071067811865475;
  out5c = out5b - v11;
  out7a = (float)(out5c + v11) + v11;
  output[14] = out6a - out7a;
  output[2] = out5c + out4a;
  output[6] = out4a - out5c;
  output[10] = COERCE_FLOAT(_mm_cvtsi128_si32((__m128i)LODWORD(out7a)) ^ 0x80000000) - out6a;
}