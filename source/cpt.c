#include <getopt.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo3d.h"

char in[PATH_MAX], out[PATH_MAX];
double xmin, xmax, ymin, ymax, zmin, zmax;
int nx, ny, nz;
double d;

void parse_arg(int argc, char *argv[]);
void usage(void);

int main(int argc, char *argv[]) {
    parse_arg(argc, argv);

    FILE *f_in = fopen(in, "rb");
    double *x = malloc(nx * sizeof(double));
    double *y = malloc(ny * sizeof(double));
    double *z = malloc(nz * sizeof(double));
    double (*u)[ny][nz] = malloc(nx * ny * nz * sizeof(double));
    Polyhedron *poly = Polyhedron_new();

    for (int i = 0; i < nx; i++)
        x[i] = xmin + (double)i * (xmax - xmin) / (nx - 1);
    for (int j = 0; j < ny; j++)
        y[j] = ymin + (double)j * (ymax - ymin) / (ny - 1);
    for (int k = 0; k < nz; k++)
        z[k] = zmin + (double)k * (zmax - zmin) / (nz - 1);

    Polyhedron_read_stl(poly, f_in);
    Polyhedron_print_stats(poly);
    Polyhedron_cpt(poly, nx, ny, nz, x, y, z, u, d);

    FILE *f_out = fopen(out, "w");
    fprintf(f_out, "%d %d %d %d %d %d %d %d %d\n", xmin, xmax, ymin, ymax, zmin, zmax, nx, ny, nz);
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                fprintf(f_out, "%g ", u[i][j][k]);
            }
            fprintf(f_out, "\n");
        }
    }

    Polyhedron_destroy(poly);
    free(x);
    free(y);
    free(z);
    free(u);
    fclose(f_in);
    fclose(f_out);

    return EXIT_SUCCESS;
}

void parse_arg(int argc, char *argv[]) {
    int flag_xmin = 0, flag_xmax = 0, flag_ymin = 0, flag_ymax = 0, flag_zmin = 0, flag_zmax = 0;
    int flag_nx = 0, flag_ny = 0, flag_nz = 0, flag_d = 0, flag_in = 0, flag_out = 0;
    const struct option options[] = {
        {"xmin", required_argument, &flag_xmin, 1},
        {"xmax", required_argument, &flag_xmax, 1},
        {"ymin", required_argument, &flag_ymin, 1},
        {"ymax", required_argument, &flag_ymax, 1},
        {"zmin", required_argument, &flag_zmin, 1},
        {"zmax", required_argument, &flag_zmax, 1},
        {"nx", required_argument, &flag_nx, 1},
        {"ny", required_argument, &flag_ny, 1},
        {"nz", required_argument, &flag_nz, 1},
        {"d", required_argument, &flag_d, 1},
        {"input", required_argument, &flag_in, 1},
        {"output", required_argument, &flag_out, 1},
        {NULL, 0, NULL, 0},
    };
    int opt, index;

    while (1) {
        opt = getopt_long_only(argc, argv, "", options, &index);
        if (opt == -1)
            break;

        switch (index) {
        case 0:
            xmin = atof(optarg);
            break;
        case 1:
            xmax = atof(optarg);
            break;
        case 2:
            ymin = atof(optarg);
            break;
        case 3:
            ymax = atof(optarg);
            break;
        case 4:
            zmin = atof(optarg);
            break;
        case 5:
            zmax = atof(optarg);
            break;
        case 6:
            nx = atoi(optarg);
            break;
        case 7:
            ny = atoi(optarg);
            break;
        case 8:
            nz = atoi(optarg);
            break;
        case 9:
            d = atof(optarg);
            break;
        case 10:
            strcpy(in, optarg);
            break;
        case 11:
            strcpy(out, optarg);
            break;
        default:
            usage();
            exit(EXIT_FAILURE);
        }
    }

    if (!flag_xmin || !flag_xmax || !flag_ymin || !flag_ymax || !flag_zmin || !flag_zmax || !flag_nx || !flag_ny ||
        !flag_nz || !flag_d || !flag_in || !flag_out) {
        usage();
        exit(EXIT_FAILURE);
    }
}

void usage(void) {
    fprintf(stderr, "usage: cpt <options>\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "options:\n");
    fprintf(stderr, "    --input=<file>      Input file (STL)\n");
    fprintf(stderr, "    --output=<file>     Output file (text)\n");
    fprintf(stderr, "    --xmin=<xmin>       Mesh minimum x coordinate\n");
    fprintf(stderr, "    --xmax=<xmax>       Mesh maximum x coordinate\n");
    fprintf(stderr, "    --ymin=<ymin>       Mesh minimum y coordinate\n");
    fprintf(stderr, "    --ymax=<ymax>       Mesh maximum y coordinate\n");
    fprintf(stderr, "    --zmin=<zmin>       Mesh minimum z coordinate\n");
    fprintf(stderr, "    --zmax=<zmax>       Mesh maximum z coordinate\n");
    fprintf(stderr, "    --nx=<nx>           Number of mesh points in x direction\n");
    fprintf(stderr, "    --ny=<ny>           Number of mesh points in y direction\n");
    fprintf(stderr, "    --nz=<nz>           Number of mesh points in z direction\n");
    fprintf(stderr, "    --d=<d>             Maximum distance\n");

}
