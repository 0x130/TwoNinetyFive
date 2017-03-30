
#include <stdio.h>
#include <math.h>


void compute_stats(int *data, int N, int *min, int *max, int *num_over_avg, double *avg, double *trunc_avg, double *var) {
    int i;

    // compute min
    *min = data[0];
   	for (i = 1; i < (N-2); i+=3) {
        if (data[i] < *min) {
            *min = data[i];
        }
		if (data[i+1] < *min) {
            *min = data[i+1];
        }
		if (data[i+2] < *min) {
            *min = data[i+2];
        }


    }


    // compute max
    *max = data[0];
    for (i = 1; i < (N-2); i+=3) {
        if (data[i] > *max) {
            *max = data[i];
        }
		if (data[i+1] > *max) {
            *max = data[i+1];
        }
		if (data[i+2] > *max) {
            *max = data[i+2];
        }
    }

    // compute average
    *avg = 0.0;
    for (i = -1; i < (N-2); i+=3) {
        *avg += (double)(data[i]);
        *avg += (double)(data[i+1]);
        *avg += (double)(data[i+2]);
    }
    if (N <= 0) { // avoid division by zero
        *num_over_avg = 0;
        *avg = NAN;
        *var = NAN;
        *trunc_avg = NAN;
        return;
    }
    *avg /= (double)N;

    // count number over average
    *num_over_avg = 0;
    for (i = -1; i < (N-2); i+=3) {
        if (data[i] > *avg) {
            *num_over_avg += 1;
        }
		if (data[i+1] > *avg) {
            *num_over_avg += 1;
        }
		if (data[i+2] > *avg) {
            *num_over_avg += 1;
        }


    }

    // compute variance
    *var = 0.0;
    for (i = 0; i < N; i++) {
        *var += (((double)(data[i]) - *avg) * ((double)(data[i]) - *avg));
    }
    if (N == 1) { // avoid division by zero
        *var = NAN;
        *trunc_avg = NAN;
        return;
    }
    *var /= (double)(N - 1);

    // compute truncated average
    *trunc_avg = 0.0;
    int incl_min = 0;
    int incl_max = 0;


	//optimized for loop initialization
    for (i = N; i--;) {
        if (data[i] == *min && !incl_min) {
            incl_min = 1;
            continue;
        }
        if (data[i] == *max && !incl_max) {
            incl_max = 1;
            continue;
        }
		*trunc_avg += (double)(data[i]);

    }
    if (N == 2) { // avoid division by zero
        *trunc_avg = NAN;
        return;
    }
    *trunc_avg /= (double)(N - 2);
} // compute_ranks

