#include <stdio.h>
#include <massv.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv)
{
    int i, n = 4;
    vector float x_coords, y_coords, mag, theta;
    x_coords = (vector float){5.0, -7.0, -4.0, 8.0};
    y_coords = (vector float){9.0, 4.0, -4.0, -2.0};

    /* Calculate the angles of the four points */
    vsatan2((float *)&theta, (float *)&y_coords, (float *)&x_coords, &n);

    /* Compute x^2 for each coordinate */
    x_coords = spu_mul(x_coords, x_coords);

    /* Compute y^2 + x^2 for each coordinate */
    mag = spu_madd(y_coords, y_coords, x_coords);

    /* Compute sqrt(y^2 + x^2) for each coordinate */
    vssqrt((float *)&mag, (float *)&mag, &n);

    for (i = 0; i < 4; i++)
        printf("Point %d: (%f, %f)\n", i, spu_extract(mag, i), spu_extract(theta, i));
    return 0;
}

