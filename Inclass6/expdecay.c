/* expdecay.c (Listing 1.8.1 on p.150)*/
/* implement formula y[x] = a * exp(-x/T)
 (not x[t] = a * exp(-k/T) --> A mistake in your textbook) */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(int argc, char *argv[])
{
    int i,nsteps;
    double time,value,T,step;
    double decay_ratio;
    double dur;
    
    if(argc != 4){        /* error in p. 150. Replace 'ARG_NARGS' with '4'.*/
        printf("usage: expdecay dur T nsteps\n");
        return 1;
    }
    
    dur    = atof(argv[1]);       /* duration of decay */
    T      = atof(argv[2]);       /* time constant or mean lifetime */
    nsteps = atoi(argv[3]);       /* number of steps  */
    
    step = dur/nsteps;            /* the constant time increment */
    decay_ratio = exp(-step/T);   /* calculating the constant ratio value. */
    value = 1.0;               /* giving y the starting value for the decay */
    time = 0.0;                /* giving x the starting time for the decay */
    fprintf(stderr,"duration = %.4f, each step = %.4f\n",dur,step);
    /*stderr: directed to the screen */
    
    for(i=0;i < nsteps;i++){
        printf("%.4f\t%.8f\n",time,value);       /* print out breakpoints */
        value *= decay_ratio;              /* value = value * decay_ratio */
        time += step;                      /* time = time + step */
    }
    return 0;
}

    

    

