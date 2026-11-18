
void ComputeAndOrientation(float heading, float euler[3], float* result) {
    float pitch, roll;

    result[0] = heading;

    pitch = euler[0];
    roll = euler[1];


    if(pitch < 0.0f) {
        pitch += 360.0f;
    }

    if(roll < 0.0f) {
        roll += 360.0f;
    }


    if(roll > 90.0f && roll < 270.0f) {
        pitch -=180.0f;
        if(pitch < 0.0f) {
            pitch += 360.0f;
        }
    }

    if(pitch <= 180.0f) {
        result[1] = -pitch;
    }
    if(pitch > 180.0f) {
        result[1] = 360-pitch;
    }
    if(roll >= 0.0f && roll <= 90.0f) {
        result[2] = roll;
    } else if(roll > 90.0f && roll < 270.0f) {
        result[2] = 180.0f - roll;
    } else {
        result[2] = roll - 360.0f;
    }

}
