#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define PI 3.14159265358979323846

int compare_asc(const void *a, const void *b) {
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) - (diff < 0);
}

int compare_desc(const void *a, const void *b) {
    double diff = *(double*)b - *(double*)a;
    return (diff > 0) - (diff < 0);
}

double gen_rand_num(FILE *file) {
    unsigned int rand_int;
    if (fread(&rand_int, sizeof(rand_int), 1, file) != 1) {
        return 0.0;
    }
    return (double)rand_int / (double)UINT_MAX;
}

void box_muller(double u1, double u2, double *z0, double *z1) {
    *z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
    *z1 = sqrt(-2.0 * log(u1)) * sin(2.0 * PI * u2);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <quantity> <order: asc|desc>\n", argv[0]);
        return 1;
    }

    long quantity = atol(argv[1]);
    char *order = argv[2];
    
    double *data = malloc(quantity * sizeof(double));
    FILE *entropy_source = fopen("/dev/urandom", "rb");
    
    if (!data || !entropy_source) {
        fprintf(stderr, "Error: Memory allocation or entropy source failed.\n");
        return 1;
    }

    for (long i = 0; i < quantity; i += 2) {
        double u1 = 0.0;
        while (u1 <= 0.0) {
            u1 = gen_rand_num(entropy_source);
        }
        double u2 = gen_rand_num(entropy_source);
        
        double z0, z1;
        box_muller(u1, u2, &z0, &z1);
        
        data[i] = z0;
        if (i + 1 < quantity) {
            data[i + 1] = z1;
        }
    }
    fclose(entropy_source);

    if (strcmp(order, "asc") == 0) {
        qsort(data, quantity, sizeof(double), compare_asc);
    } else if (strcmp(order, "desc") == 0) {
        qsort(data, quantity, sizeof(double), compare_desc);
    } else {
        fprintf(stderr, "Error: Invalid order. Use 'asc' or 'desc'.\n");
        free(data);
        return 1;
    }

    char filename[128];
    snprintf(filename, sizeof(filename), "sorted_%s_%ld.bin", order, quantity);
    FILE *fp_out = fopen(filename, "wb");
    
    if (fp_out) {
        fwrite(data, sizeof(double), quantity, fp_out);
        fclose(fp_out);
        printf("Success: File %s generated.\n", filename);
    } else {
        fprintf(stderr, "Error: Could not create output file.\n");
    }

    free(data);
    return 0;
}
