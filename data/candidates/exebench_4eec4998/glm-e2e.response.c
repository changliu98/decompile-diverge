float get_color_value(int code, float3 *color1, float3 *color2, float3 *color3) {
    float result;
    int index = (code & 0x3f) - 9;

    if ((unsigned int)index > 27) {
        result = 0.0f;
    } else {
        switch (index) {
            case 0:
                result = color1->v[0];
                break;
            case 1:
                result = color1->v[1];
                break;
            case 2:
                result = color1->v[2];
                break;
            case 9:
                result = color2->v[0];
                break;
            case 10:
                result = color2->v[1];
                break;
            case 11:
                result = color2->v[2];
                break;
            case 18:
                result = color3->v[0];
                break;
            case 19:
                result = color3->v[1];
                break;
            case 20:
                result = color3->v[2];
                break;
            default:
                result = 0.0f;
                break;
        }
    }
    
    return result;
}