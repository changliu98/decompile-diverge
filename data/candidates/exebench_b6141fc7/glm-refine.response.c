void __cdecl R16SRFFT(float *input, float *output)
{
  // Stage 1: Initial Sums and Differences
  float out0 = input[0] + input[8];
  float out1 = input[1] + input[9];
  float out2 = input[2] + input[10];
  float out3 = input[3] + input[11];
  float out4 = input[4] + input[12];
  float out5 = input[5] + input[13];
  float out6 = input[6] + input[14];
  float out7 = input[7] + input[15];

  float out9  = input[1] - input[9];
  float out11 = input[3] - input[11];
  float out13 = input[13] - input[5];
  float out15 = input[15] - input[7];

  // Stage 2: Twiddle Factor Multiplications
  float temp = (out13 - out9) * 0.3826834323650898f;
  float out9a  = out9 * 1.306562964876377f + temp;
  float out13a = out13 * 0.5411961001461969f + temp;

  float out14 = (input[14] - input[6]) * 0.7071067811865475f;
  float out10 = (input[2] - input[10]) * 0.7071067811865475f;
  float out14a = out14 - out10;
  out10 = out14a + out10 + out10; // Equivalent to out14 + out10

  float tempa = (out15 - out11) * 0.9238795325112867f;
  float out11a = out11 * 1.306562964876377f + tempa;
  float out8  = out15 * -0.5411961001461969f + tempa;

  // Stage 3: Butterfly Operations (Odd Indices)
  float out10a = out8 - out10 - out10; // Equivalent to out8 - 2*out10
  float out12  = out14a + (input[12] - input[4]);
  float out14b = out12 - out14a - out14a; // Equivalent to out12 - 2*out14a

  float out9b  = out11a + out9a;
  float out11b = out9b - out11a - out11a; // Equivalent to out9b - 2*out11a

  float out13b = out8 + out13a;
  float out15a = out13b - out8 - out8; // Equivalent to out13b - 2*out8

  output[1]  = out8 + out9b;
  output[7]  = out8 - out9b;
  output[9]  = out12 + out13b;
  output[15] = out13b - out12;
  output[5]  = out10a + out15a;
  output[13] = out14b - out11b;
  output[3]  = out10a - out15a;
  output[11] = -out14b - out11b;

  // Stage 4: Butterfly Operations (Even Indices)
  float out0a = out0 + out4;
  float out4a = out0a - out4 - out4; // Equivalent to out0a - 2*out4

  float out1a = out1 + out5;
  float out5a = out1a - out5 - out5; // Equivalent to out1a - 2*out5

  float out2a = out6 + out2;
  float out6a = out2a - out6 - out6; // Equivalent to out2a - 2*out6

  float out3a = out7 + out3;

  float out0b = out0a + out2a;
  output[4] = out0a - out2a;

  float out1b = out3a + out1a;
  output[12] = 2 * out3a - out1b;

  output[0] = out1b + out0b;
  output[8] = output[0] - out1b - out1b; // Equivalent to output[0] - 2*out1b

  float out5b = out5a * 0.7071067811865475f;
  float out5c = out5b - (2 * out7 - out3a) * 0.7071067811865475f; // (out3a - 2*out7) * 0.707...
  float out7a = out5c + 2 * ((2 * out7 - out3a) * 0.7071067811865475f); // out5c + 2*v11

  output[14] = out6a - out7a;
  output[2]  = out5c + out4a;
  output[6]  = out4a - out5c;
  output[10] = -out7a - out6a;
}