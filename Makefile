.PHONY: clean

cpt: source/cpt.c source/geo3d.c include/geo3d.h source/utils.c include/utils.h
	$(CC) $(CFLAGS) source/cpt.c source/geo3d.c source/utils.c -o $@ -Iinclude -I/usr/include/glib-2.0 -lm -lglib-2.0

clean:
	rm -f cpt
