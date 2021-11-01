cpt: cpt.c geo3d.c geo3d.h utils.c utils.h
	$(CC) $(CFLAGS) cpt.c geo3d.c utils.c -o $@ -I/usr/include/glib-2.0 -lm -lglib-2.0
