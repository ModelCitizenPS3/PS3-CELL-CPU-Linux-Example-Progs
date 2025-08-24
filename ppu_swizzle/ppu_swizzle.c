#include <altivec.h>

typedef struct {
    float x;
    float y;
    float z;
    float t;
} motion;

/* The array of structures */
motion p_motion[4] __attribute__((aligned(16)));

/* Placce the content of the array of structures in vectors x_vec, y_vec, z_vec, and t_vec */
int main(int argc, char **argv)
{
    vector float x_vec, y_vec, z_vec, t_vec, hold[4], tmp[4];

    /* Load structures into vectors */
    hold[0] = vec_ld(0, (float *)p_motion);
    hold[1] = vec_ld(0, (float *)&p_motion[1]);
    hold[2] = vec_ld(0, (float *)&p_motion[2]);
    hold[3] = vec_ld(0, (float *)&p_motion[3]);

    /* Perform first step of the swizzle */
    tmp[0] = vec_mergeh(hold[0], hold[2]);
    tmp[1] = vec_mergeh(hold[1], hold[3]);
    tmp[2] = vec_mergel(hold[0], hold[2]);
    tmp[3] = vec_mergel(hold[1], hold[3]);

    /* Perform second step of the swizzle */
    x_vec = vec_mergeh(tmp[0], tmp[1]);
    y_vec = vec_mergel(tmp[0], tmp[1]);
    z_vec = vec_mergeh(tmp[2], tmp[3]);
    t_vec = vec_mergel(tmp[2], tmp[3]);

    return 0;
}

