#include <stdio.h>
#include <stdlib.h>
#include "geo3d.h"

#define XMIN 5
#define XMAX 90
#define YMIN -37
#define YMAX 20
#define ZMIN -52
#define ZMAX 80

#define NX 340
#define NY 220
#define NZ 520

#define MAXD 3

double x[NX];
double y[NY];
double z[NZ];
double u[NX][NY][NZ];

int main(void) {
    FILE *fp = fopen("lucy.stl", "rb");
    Polyhedron *poly = Polyhedron_new();

    for (int i = 0; i < NX; i++)
        x[i] = XMIN + (double)i * (XMAX - XMIN) / (NX - 1);
    for (int j = 0; j < NY; j++)
        y[j] = YMIN + (double)j * (YMAX - YMIN) / (NY - 1);
    for (int k = 0; k < NZ; k++)
        z[k] = ZMIN + (double)k * (ZMAX - ZMIN) / (NZ - 1);

    Polyhedron_read_stl(poly, fp);
    Polyhedron_print_stats(poly);
    Polyhedron_cpt(poly, NX, NY, NZ, x, y, z, u, MAXD);

    FILE *out = fopen("lucy_u", "w");
    fprintf(out, "%d %d %d %d %d %d %d %d %d\n", XMIN, XMAX, YMIN, YMAX, ZMIN, ZMAX, NX, NY, NZ);
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            for (int k = 0; k < NZ; k++) {
                fprintf(out, "%g ", u[i][j][k]);
            }
            fprintf(out, "\n");
        }
    }

    Polyhedron_destroy(poly);
    fclose(fp);
    fclose(out);

    return 0;
}