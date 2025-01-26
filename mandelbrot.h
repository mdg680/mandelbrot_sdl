#ifndef MANDELBROT_H
#define MANDELBROT_H

typedef struct scale_tuple {
    float start;
    float end;
} scale_tuple;

/* 
generates an array of evenly spaced integers between a specified start and end 
value. The function takes three parameters: `start`, `end`, and `n`. The `start` 
parameter specifies the beginning value of the sequence, `end` specifies the 
final value, and `n` indicates the number of elements in the generated array.
*/
float* linspace(float start, float end, int n);
int* linspace_int(int start, int end, int n);
/* Calculate the mandelbrot set */
int* mandelbrot_set(
    int max_iter, 
    scale_tuple *x_scale, scale_tuple *y_scale, 
    int screen_with, int screen_height
);

#endif // MANDELBROT_H