void getTransf (const SCE_TMatrix4 m, SCE_TMatrix4 ortho,
                       SCE_TMatrix4 proj)
{
    proj[0] = m[2]; proj[1] = m[3]; proj[2] = 0.0; proj[3] = 0.0;
    proj[4] = 0.0; proj[5] = m[4]; proj[6] = 0.0; proj[7] = 0.0;
    proj[8] = m[0]; proj[9] = m[1]; proj[10] = 1.0; proj[11] = 0.0;

    ortho[0] = 1.0 / m[7]; ortho[1] = -m[8] / m[7] / m[9]; ortho[2] = 0.0;
    ortho[3] = 0.0; ortho[4] = 0.0; ortho[5] = 1.0 / m[9]; ortho[6] = 0.0;
    ortho[7] = -m[5] / m[7]; ortho[8] = (m[8] * m[6] + m[5] * m[7]) /
        m[7] / m[9]; ortho[9] = 1.0;
}