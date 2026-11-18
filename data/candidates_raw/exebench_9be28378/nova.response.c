void func0(double out[6], const double m[6])
{
	double m11, m12, m13, m21, m22, m23, m31, m32, m33;
	double det;

	m11 = m[0];
	m12 = m[1];
	m13 = m[2];
	m21 = m[3];
	m22 = m[4];
	m23 = m[5];
	m31 = m[6];
	m32 = m[7];
	m33 = m[8];

	det = 1.0 / (m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 -
		m13 * m22 * m31 - m11 * m23 * m32 - m12 * m21 * m33);

	out[0] = (m22 * m33 - m23 * m32) * det;
	out[1] = (m13 * m32 - m12 * m33) * det;
	out[2] = (m12 * m23 - m13 * m22) * det;
	out[3] = (m23 * m31 - m21 * m33) * det;
	out[4] = (m11 * m33 - m13 * m31) * det;
	out[5] = (m13 * m21 - m11 * m32) * det;
	out[6] = (m21 * m32 - m22 * m31) * det;
	out[7] = (m12 * m31 - m11 * m32) * det;
	out[8] = (m11 * m22 - m12 * m21) * det;
}