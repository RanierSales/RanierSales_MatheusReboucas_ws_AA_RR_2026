#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    double time;
    unsigned long long inspections;
    size_t memory_bytes;
    int n;
} Metrics;

unsigned long long verificaAlgo(double target, double list[], int list_size) {
    unsigned long long count = 0;
    for (int l = 0; l < 10000; l++) {
        for (int i = 0; i <= list_size - 6; i++) { 
            for (int j = i + 2; j <= list_size / 2; j++) { 
                for (int k = 0; k < list_size; k++) { 
                    if (list[k] == target) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

unsigned long long linearSearch(double target, double list[], int list_size) {
    unsigned long long count = 0;
    for (int i = 0; i < list_size; i++) {
        if (list[i] == target) {
            count++;
        }
    }
    return count;
}

Metrics runExperiment(unsigned long long (*search_func)(double, double[], int), double target, double list[], int n) {
    struct timespec start, end;
    Metrics m;
    
    m.n = n;
    m.memory_bytes = n * sizeof(double); 

    clock_gettime(CLOCK_MONOTONIC, &start);
    m.inspections = search_func(target, list, n);
    clock_gettime(CLOCK_MONOTONIC, &end);

    m.time = (end.tv_sec - start.tv_sec) + 
             (end.tv_nsec - start.tv_nsec) / 1e9;
    
    return m;
}

int main() {
    srand(time(NULL));

    FILE *csv_file = fopen("experiment_results.csv", "a");
    if (!csv_file) return 1;

    fprintf(csv_file, "algorithm,data_type,n,run_id,time_sec,inspections\n");

    int sizes[] = {100, 300, 500, 700, 1000, 1500, 2000}; 
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    char *data_types[] = {"random", "asc", "desc"};
    int num_types = 3;
    int iterations = 13; 

    for (int t = 0; t < num_types; t++) {
        for (int s = 0; s < num_sizes; s++) {
            int n = sizes[s];
            char filename[128];
            
            if (strcmp(data_types[t], "random") == 0)
                snprintf(filename, sizeof(filename), "random_data_%d.bin", n);
            else
                snprintf(filename, sizeof(filename), "sorted_%s_%d.bin", data_types[t], n);

            FILE *bin_fp = fopen(filename, "rb");
            if (!bin_fp) {
                printf("Warning: Could not open %s, skipping...\n", filename);
                continue;
            }

            double *buffer = malloc(n * sizeof(double));
            if (fread(buffer, sizeof(double), n, bin_fp) != (size_t)n) {
                fprintf(stderr, "Error: Failed to read expected data from %s\n", filename);
                free(buffer);
                fclose(bin_fp);
                continue; 
            }
            fclose(bin_fp);

            printf("Running experiment: %s (n=%d)\n", filename, n);

            for (int run = 1; run <= iterations; run++) {
                int random_index = rand() % n;
                double target = buffer[random_index]; 

                Metrics m1 = runExperiment(verificaAlgo, target, buffer, n);
                fprintf(csv_file, "verificaAlgo,%s,%d,%d,%.8f,%llu\n", 
                        data_types[t], n, run, m1.time, m1.inspections);

                Metrics m2 = runExperiment(linearSearch, target, buffer, n);
                fprintf(csv_file, "linearSearch,%s,%d,%d,%.8f,%llu\n", 
                        data_types[t], n, run, m2.time, m2.inspections);
            }

            free(buffer); 
        }
    }

    fclose(csv_file);
    printf("Experiment complete! Results saved to experiment_results.csv\n");
    return 0;
}