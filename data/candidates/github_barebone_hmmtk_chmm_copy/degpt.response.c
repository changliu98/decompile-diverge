void chmm_copy(CHMM *source_hmm, CHMM *dest_hmm)
{
    int idx_state, idx_state, idx_dim;

    // Copy the number of states from hmm1 to hmm2
    dest_hmm->N = source_hmm->N;
    // Allocate memory for the number of observations per state and copy values
    dest_hmm->nN = cvector(1, dest_hmm->N);
    for (idx_state = 1; idx_state <= dest_hmm->N; idx_state++) {
        dest_hmm->nN[idx_state] = source_hmm->nN[idx_state];
    }

    // Copy the dimensionality of the observation vectors
    dest_hmm->D = source_hmm->D;
    // Allocate memory for the dimensionality of observations and copy values
    dest_hmm->nD = cvector(1, dest_hmm->D);
    for (idx_state = 1; idx_state <= dest_hmm->D; idx_state++) {
        dest_hmm->nD[idx_state] = source_hmm->nD[idx_state];
    }

    // Allocate memory for the state transition matrix and copy values
    dest_hmm->A = dmatrix(1, dest_hmm->N, 1, dest_hmm->N);
    for (idx_state = 1; idx_state <= dest_hmm->N; idx_state++) {
        for (idx_state = 1; idx_state <= dest_hmm->N; idx_state++) {
            dest_hmm->A[idx_state][idx_state] = source_hmm->A[idx_state][idx_state];
        }
    }

    // Allocate memory for the emission parameters (mean, covariance, inverse covariance)
    (dest_hmm->B).miu = dmatrix(1, dest_hmm->N, 1, dest_hmm->D);
    (dest_hmm->B).cov = dmatrix(1, dest_hmm->N, 1, dest_hmm->D);
    (dest_hmm->B).cov_inv = dmatrix(1, dest_hmm->N, 1, dest_hmm->D);
    // Copy emission parameter values
    for (idx_state = 1; idx_state <= dest_hmm->N; idx_state++) {
        for (idx_dim = 1; idx_dim <= dest_hmm->D; idx_dim++) {
            (dest_hmm->B).miu[idx_state][idx_dim] = (source_hmm->B).miu[idx_state][idx_dim];
            (dest_hmm->B).cov[idx_state][idx_dim] = (source_hmm->B).cov[idx_state][idx_dim];
            (dest_hmm->B).cov_inv[idx_state][idx_dim] = (source_hmm->B).cov_inv[idx_state][idx_dim];
        }
    }

    // Allocate memory for the initial state distribution and copy values
    dest_hmm->pi = dvector(1, dest_hmm->N);
    for (idx_state = 1; idx_state <= dest_hmm->N; idx_state++) {
        dest_hmm->pi[idx_state] = source_hmm->pi[idx_state];
    }
}