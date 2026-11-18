int get_high_speed_hz(int speed) {
    return (speed * 125 + 512) >> 10;
}