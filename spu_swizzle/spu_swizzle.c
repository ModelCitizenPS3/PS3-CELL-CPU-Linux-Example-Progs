#include <stdio.h>
#include <spu_intrinsics.h>

typedef struct {
    float x;
    float y;
    float z;
    float t;
} motion;

/* The array of structures */
motion p_motion[4] __attribute__((aligned(16)));

int main(int argc, char **argv)
{
    int i;
    vector float x_vec, y_vec, z_vec, t_vec, *hold, tmp[2];

    /* Initialize array of structures */
    for (i = 0; i < 4; i++) {
        p_motion[i].x = 0;
        p_motion[i].y = 1;
        p_motion[i].z = 2;
        p_motion[i].t = 3;
    }

    /* Create index vectors for spu_shuffle */
    vector unsigned char tmpindex = {0, 1, 2, 3, 4, 5, 6, 7, 16, 17, 18, 19, 20, 21, 22, 23};
    vector unsigned char gather = {0, 1, 2, 3, 8, 9, 10, 11, 16, 17, 18, 19, 24, 25, 26, 27};
    vector unsigned short tmp_add = spu_splats((unsigned short)0x0808);
    vector unsigned short gather_add = spu_splats((unsigned short)0x0404);

    /* Access AOS as a vector float array */
    hold = (vector float *)&p_motion;

    /* Intermediate stage for x_vec, y_vec */
    tmp[0] = spu_shuffle(hold[0], hold[1], tmpindex);
    tmp[1] = spu_shuffle(hold[2], hold[3], tmpindex);

    /* Final stage for x_vec, y_vec */
    x_vec = spu_shuffle(tmp[0], tmp[1], gather);
    y_vec = spu_shuffle(tmp[0], tmp[1], (vector unsigned char)spu_add((vector unsigned short)gather, gather_add));

    /* Intermediate stage for z_vec, t_vec */
    tmpindex = (vector unsigned char)spu_add((vector unsigned short)tmpindex, tmp_add);
    tmp[0] = spu_shuffle(hold[0], hold[1], tmpindex);
    tmp[1] = spu_shuffle(hold[2], hold[3], tmpindex);

    /* Final stage for z_vec, t_vec */
    z_vec = spu_shuffle(tmp[0], tmp[1], gather);
    t_vec = spu_shuffle(tmp[0], tmp[1], (vector unsigned char)spu_add((vector unsigned short)gather, gather_add));

    /* Display results */
    printf("x-vector: %f %f %f %f\n", spu_extract(x_vec, 0), spu_extract(x_vec, 1), spu_extract(x_vec, 2), spu_extract(x_vec, 3));
    printf("y-vector: %f %f %f %f\n", spu_extract(y_vec, 0), spu_extract(y_vec, 1), spu_extract(y_vec, 2), spu_extract(y_vec, 3));
    printf("z-vector: %f %f %f %f\n", spu_extract(z_vec, 0), spu_extract(z_vec, 1), spu_extract(z_vec, 2), spu_extract(z_vec, 3));
    printf("t-vector: %f %f %f %f\n", spu_extract(t_vec, 0), spu_extract(t_vec, 1), spu_extract(t_vec, 2), spu_extract(t_vec, 3));
    return 0;
}

