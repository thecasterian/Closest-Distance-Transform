Closest Distance Transform
==========================

Prerequisites
-------------

* GLib
* Python packages for plotting:
  * NumPy
  * Matplotlib
  * numpy-stl
  * Mayavi

Build
-----

In the root directory:

```bash
make cpt
```

Usage
-----

```
cpt <options>

    --input=<file>      Input file (STL)
    --output=<file>     Output file (text)
    --xmin=<xmin>       Mesh minimum x coordinate
    --xmax=<xmax>       Mesh maximum x coordinate
    --ymin=<ymin>       Mesh minimum y coordinate
    --ymax=<ymax>       Mesh maximum y coordinate
    --zmin=<zmin>       Mesh minimum z coordinate
    --zmax=<zmax>       Mesh maximum z coordinate
    --nx=<nx>           Number of mesh points in x direction
    --ny=<ny>           Number of mesh points in y direction
    --nz=<nz>           Number of mesh points in z direction
    --d=<d>             Maximum distance
```

* Python script for plotting the result:

```
python plot.py <STL file> <result file>
```

References
----------

* S. Mauch, A Fast Algorithm for Computing the Closest Point and Distance Transform (2000)
* A. Roosing et al., Fast Distance Fields for Fluid Dynamics Mesh Generation on Graphics Hardware (2019)
