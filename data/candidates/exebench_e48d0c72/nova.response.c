static int setLoopIters(struct MPContext *mpctx, double speed,
                               double new_pts, double pts)
{
    double cur_pts = mpctx->video_pts * speed * mpctx->play_dir;
    if (cur_pts > new_pts) {
        mpctx->play_dir = new_pts * mpctx->play_dir / cur_pts;
        if (mpctx->play_dir < 2)
            mpctx->play_dir = 2;
    }
    return 0;
}