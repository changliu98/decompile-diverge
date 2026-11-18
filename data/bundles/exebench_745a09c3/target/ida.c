void __cdecl ml_multiply_mat4_mat4(float *mat_a, float *mat_b, float *out)
{
  float temp_4; // [rsp+4h] [rbp-5Ch]
  float temp_8; // [rsp+8h] [rbp-58h]
  float temp_12; // [rsp+Ch] [rbp-54h]
  float temp_16; // [rsp+10h] [rbp-50h]
  float temp_20; // [rsp+14h] [rbp-4Ch]
  float temp_24; // [rsp+18h] [rbp-48h]
  float temp_28; // [rsp+1Ch] [rbp-44h]
  float temp_32; // [rsp+20h] [rbp-40h]
  float temp_36; // [rsp+24h] [rbp-3Ch]
  float temp_40; // [rsp+28h] [rbp-38h]
  float temp_44; // [rsp+2Ch] [rbp-34h]
  float temp_48; // [rsp+30h] [rbp-30h]
  float temp_52; // [rsp+34h] [rbp-2Ch]
  float temp_56; // [rsp+38h] [rbp-28h]
  float temp_60; // [rsp+3Ch] [rbp-24h]

  temp_4 = (float)(mat_a[3] * mat_b[13])
         + (float)((float)(mat_a[2] * mat_b[9]) + (float)((float)(*mat_a * mat_b[1]) + (float)(mat_a[1] * mat_b[5])));
  temp_8 = (float)(mat_a[3] * mat_b[14])
         + (float)((float)(mat_a[2] * mat_b[10]) + (float)((float)(*mat_a * mat_b[2]) + (float)(mat_a[1] * mat_b[6])));
  temp_12 = (float)(mat_a[3] * mat_b[15])
          + (float)((float)(mat_a[2] * mat_b[11]) + (float)((float)(*mat_a * mat_b[3]) + (float)(mat_a[1] * mat_b[7])));
  temp_16 = (float)(mat_a[7] * mat_b[12])
          + (float)((float)(mat_a[6] * mat_b[8]) + (float)((float)(mat_a[4] * *mat_b) + (float)(mat_a[5] * mat_b[4])));
  temp_20 = (float)(mat_a[7] * mat_b[13])
          + (float)((float)(mat_a[6] * mat_b[9]) + (float)((float)(mat_a[4] * mat_b[1]) + (float)(mat_a[5] * mat_b[5])));
  temp_24 = (float)(mat_a[7] * mat_b[14])
          + (float)((float)(mat_a[6] * mat_b[10]) + (float)((float)(mat_a[4] * mat_b[2]) + (float)(mat_a[5] * mat_b[6])));
  temp_28 = (float)(mat_a[7] * mat_b[15])
          + (float)((float)(mat_a[6] * mat_b[11]) + (float)((float)(mat_a[4] * mat_b[3]) + (float)(mat_a[5] * mat_b[7])));
  temp_32 = (float)(mat_a[11] * mat_b[12])
          + (float)((float)(mat_a[10] * mat_b[8]) + (float)((float)(mat_a[8] * *mat_b) + (float)(mat_a[9] * mat_b[4])));
  temp_36 = (float)(mat_a[11] * mat_b[13])
          + (float)((float)(mat_a[10] * mat_b[9]) + (float)((float)(mat_a[8] * mat_b[1]) + (float)(mat_a[9] * mat_b[5])));
  temp_40 = (float)(mat_a[11] * mat_b[14])
          + (float)((float)(mat_a[10] * mat_b[10]) + (float)((float)(mat_a[8] * mat_b[2]) + (float)(mat_a[9] * mat_b[6])));
  temp_44 = (float)(mat_a[11] * mat_b[15])
          + (float)((float)(mat_a[10] * mat_b[11]) + (float)((float)(mat_a[8] * mat_b[3]) + (float)(mat_a[9] * mat_b[7])));
  temp_48 = (float)(mat_a[15] * mat_b[12])
          + (float)((float)(mat_a[14] * mat_b[8]) + (float)((float)(mat_a[12] * *mat_b) + (float)(mat_a[13] * mat_b[4])));
  temp_52 = (float)(mat_a[15] * mat_b[13])
          + (float)((float)(mat_a[14] * mat_b[9])
                  + (float)((float)(mat_a[12] * mat_b[1]) + (float)(mat_a[13] * mat_b[5])));
  temp_56 = (float)(mat_a[15] * mat_b[14])
          + (float)((float)(mat_a[14] * mat_b[10])
                  + (float)((float)(mat_a[12] * mat_b[2]) + (float)(mat_a[13] * mat_b[6])));
  temp_60 = (float)(mat_a[15] * mat_b[15])
          + (float)((float)(mat_a[14] * mat_b[11])
                  + (float)((float)(mat_a[12] * mat_b[3]) + (float)(mat_a[13] * mat_b[7])));
  *out = (float)(mat_a[3] * mat_b[12])
       + (float)((float)(mat_a[2] * mat_b[8]) + (float)((float)(*mat_a * *mat_b) + (float)(mat_a[1] * mat_b[4])));
  out[1] = temp_4;
  out[2] = temp_8;
  out[3] = temp_12;
  out[4] = temp_16;
  out[5] = temp_20;
  out[6] = temp_24;
  out[7] = temp_28;
  out[8] = temp_32;
  out[9] = temp_36;
  out[10] = temp_40;
  out[11] = temp_44;
  out[12] = temp_48;
  out[13] = temp_52;
  out[14] = temp_56;
  out[15] = temp_60;
}