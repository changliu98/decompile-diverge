void Mat4_RotateQuaternion( Mat4* out, const Quaternion* q )
{
 float xx, xy, xz, xw, yy, yz, yw, zz, zw;
 float w, x, y, z;
 float m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23;

 w = q->w;
 x = q->x;
 y = q->y;
 z = q->z;

 xx = x * x;
 xy = x * y;
 xz = x * z;
 xw = x * w;

 yy = y * y;
 yz = y * z;
 yw = y * w;

 zz = z * z;
 zw = z * w;

 m00 = 1.0f - 2.0f * (yy + zz);
 m01 = 2.0f * (xy - zw);
 m02 = 2.0f * (xz + yw);
 m03 = 0.0f;

 m10 = 2.0f * (xy + zw);
 m11 = 1.0f - 2.0f * (zz + xx);
 m12 = 2.0f * (yz - xw);
 m13 = 0.0f;

 m20 = 2.0f * (xz - yw);
 m21 = 2.0f * (yz + xw);
 m22 = 1.0f - 2.0f * (yy + xx);
 m23 = 0.0f;

 m03 = 0.0f;
 m13 = 0.0f;
 m23 = 0.0f;
 m33 = 1.0f;

 out->m00 = m00;
 out->m01 = m01;
 out->m02 = m02;
 out->m03 = m03;

 out->m10 = m10;
 out->m11 = m11;
 out->m12 = m12;
 out->m13 = m13;

 out->m20 = m20;
 out->m21 = m21;
 out->m22 = m22;
 out->m23 = m23;

 out->m30 = m30;
 out->m31 = m31;
 out->m32 = m32;
 out->m33 = m33;
}