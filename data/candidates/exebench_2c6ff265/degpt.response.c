void babl_matrix_mul_vector(double *mat,double *v_in,double *v_out)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double m_2_2;
  double m_2_1;
  double m_2_0;
  double m_1_2;
  double m_1_1;
  double m_1_0;
  double m_0_2;
  double m_0_1;
  double m_0_0;
  double c;
  double b;
  double a;
  double *v_out_local;
  double *v_in_local;
  double *mat_local;
  
  dVar1 = *v_in;
  dVar2 = v_in[1];
  dVar3 = v_in[2];
  dVar4 = mat[3];
  dVar5 = mat[4];
  dVar6 = mat[5];
  dVar7 = mat[6];
  dVar8 = mat[7];
  dVar9 = mat[8];
  *v_out = mat[2] * dVar3 + *mat * dVar1 + mat[1] * dVar2;
  v_out[1] = dVar6 * dVar3 + dVar4 * dVar1 + dVar5 * dVar2;
  v_out[2] = dVar9 * dVar3 + dVar7 * dVar1 + dVar8 * dVar2;
  return;
}