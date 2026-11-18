void convertscreenvertex(camCamera *cam, int resx, int resy)
{
 cam->x = (cam->x - (resx >> 1)) / (float)(resx >> 1);
 cam->y = ((resy >> 1) - cam->y) / (float)(resx >> 1);
 cam->z = -1.0f;
}