#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define PI 3.141592653589793238462643383279502

double gen_rand_num(FILE *file) {
    unsigned int rand_int;

    if (fread(&rand_int, sizeof(rand_int), 1, file) != 1) {
        fprintf(stderr, "Error: Failed to read entropy!\n");
        exit(1);
    };

    double result = (double)rand_int / (double)UINT_MAX;
    return result;
}

void box_muller_transformatition(const double n1, const double n2, double *z0, double *z1) {
    *z0 = sqrt(-2.0 * log(n1)) * cos(2.0 * PI * n2);
    *z1 = sqrt(-2.0 * log(n1)) * sin(2.0 * PI * n2);
}

int main(int argc, char *argv[]){
    double u1, u2, z0, z1;
    int range;
    FILE *fp = fopen("/dev/urandom", "rb");

    if (fp == NULL) return 1;
    if (argc < 2) return 1;

    long int qtt = atol(argv[1]);

    char filename[64];
    snprintf(filename, sizeof(filename),"random_data_%ld.bin", qtt);

    FILE *fp2 = fopen(filename, "wb");

    if (fp2 == NULL) return 1;

    if (qtt % 2 == 0) {
        range = (qtt / 2);
    } else {
        range = (qtt / 2) + 1;
    }

    for (int i = 0; i < range; i++) {
        u1 = 0.0;

        while (u1 <= 0.0) {
            u1 = gen_rand_num(fp);
        }
        u2 = gen_rand_num(fp);

        box_muller_transformatition(u1, u2, &z0, &z1);
        
        if (qtt % 2 != 0 && i == range - 1) {
            fwrite(&z0, sizeof(double), 1, fp2);
            break;
        }

        fwrite(&z0, sizeof(double), 1, fp2);
        fwrite(&z1, sizeof(double), 1, fp2);
    }

    fclose(fp);
    fclose(fp2);
    return 0;
}