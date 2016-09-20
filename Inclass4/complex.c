/* complex.c: Demonstrating the use of structures
 Passing structure pointers to a function
 You cannot return a pointer to a structure.
 because it will be deallocated when the function exits */
#include <stdio.h>

//defining the new struct type Complex with typedef here
typedef struct _complex {  //
  float re;
  float im;
} COMPLEX;  // name the data type

// mult() function prototype here
COMPLEX mult(COMPLEX* a, COMPLEX* b);

int main(void)
{

    float re,im;
    COMPLEX a, b, c;// declare a, b, c of the type complex; c is the product of a and b

    printf("Please enter the first complex number (re, im): ");
    scanf("%f%f", &re, &im);
    // assign values to the struct a here
    a.re = re;  // a, b, c are of type complex so they have the structure components
    a.im = im;
    printf("Please enter the second complex number (re, im): ");
    scanf("%f%f", &re, &im);
    // assign values to the struct b here
    b.re = re;
    b.im = im;

    // call the mult() function here
    c = mult(&a, &b);

    // display the product here
    printf("Their product is %.2f + %.2fi \n",c.re  ,c.im);
    return 0;
}

// mult() function definition
COMPLEX mult(COMPLEX* a, COMPLEX* b) {
  COMPLEX c;
  // when dealng with pointer to structure
  // use -> to dereference and get the value  in the struct
  // or (*a).re will also work
  // (*<struct>).<member>
  c.re = a->re*b->re - a->im*b->im;
  c.im = a->re*b->im + a->im*b->re;
  return c;
}
