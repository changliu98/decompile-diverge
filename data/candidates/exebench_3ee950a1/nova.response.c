float hpluck(float dt, struct pendulum * p) {
    float t;
    p->theta += dt * p->dtheta;
    if (p->theta >= PI) {
        t = PI;
        p->dtheta = -p->dtheta;
    } else {
        t = 20;
        p->dtheta = p->dtheta + dt * (p->g / t) * sin(p->theta);
    }
    p->dtheta = p->dtheta + dt * (p->g / t) * sin(p->theta);
    p->dtheta = p->dtheta + dt * (p->g / t) * sin(p->theta);
    p->theta = p->theta + dt * p->dtheta;
    p->dtheta = p->dtheta + dt * (p->g / t) * sin(p->theta);
    return p->theta;
}