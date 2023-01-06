import numpy as np
from stl.mesh import Mesh
from mayavi import mlab
import sys

STL_FILE = sys.argv[1]
SDF_FILE = sys.argv[2]

# Read STL
m = Mesh.from_file(STL_FILE)
verts_dict = {}
verts = []
tris = []
for v0, v1, v2 in zip(m.v0, m.v1, m.v2):
    v0 = tuple(v0)
    v1 = tuple(v1)
    v2 = tuple(v2)

    if v0 not in verts_dict:
        verts_dict[v0] = len(verts_dict)
        verts.append(v0)
    if v1 not in verts_dict:
        verts_dict[v1] = len(verts_dict)
        verts.append(v1)
    if v2 not in verts_dict:
        verts_dict[v2] = len(verts_dict)
        verts.append(v2)

    tris.append([verts_dict[v0], verts_dict[v1], verts_dict[v2]])

verts = np.array(verts)
tris = np.array(tris)

# Construct mesh
with open(SDF_FILE, "r") as f:
    XMIN, XMAX, YMIN, YMAX, ZMIN, ZMAX, NX, NY, NZ = [int(x) for x in f.readline().split()]

x = np.linspace(XMIN, XMAX, NX)
y = np.linspace(YMIN, YMAX, NY)
z = np.linspace(ZMIN, ZMAX, NZ)

X, Y, Z = np.meshgrid(x, y, z, indexing="ij")

# Read SDF
u = np.loadtxt(SDF_FILE, skiprows=1).reshape(NX, NY, NZ)
u[u < 0] = 0
u[u > 2.7] = 2.7

# Plot
mlab.triangular_mesh(verts[:, 0], verts[:, 1], verts[:, 2], tris, color=(0.7, 0.7, 0.7))

s = mlab.pipeline.scalar_field(X, Y, Z, u)

sx = mlab.volume_slice(X, Y, Z, u, plane_orientation="z_axes")
sx.module_manager.scalar_lut_manager.lut.nan_color = 0, 0, 0, 0
sx.update_pipeline()

mlab.show()
