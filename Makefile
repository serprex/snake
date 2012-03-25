sn:sn.c
	gcc -std=gnu99 -Os -march=native -s -ffast-math -fwhole-program -o snake sn.c ${CFLAGS} -lGL -lglfw