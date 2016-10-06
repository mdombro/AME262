/* breakdur.c from The Audio Programming Book DVD
 Reading breakpoints and report the maximum value 
 using get_breakpoints()and maxpoint() 
 modified by Ming-Lun Lee */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NPOINTS (64)
#define LINELENGTH (80)

typedef struct breakpoint {
		double time;
		double value;
} BREAKPOINT;

BREAKPOINT * get_breakpoints(FILE * fp, long * psize);
BREAKPOINT maxpoint(const BREAKPOINT* points,long npoints);

int main(int argc, char * argv[])
{	
	long	size; // number of breakpoints
	double	dur;  // duration
	BREAKPOINT point, *points;
	FILE * fp;

	printf("breakdur: find duration of breakpoint file\n");
	if(argc < 2){
		printf("usage: breakdur infile.txt \n");
		return 0;
	}
	fp = fopen(argv[1],"r"); // get the breakpoint file address
	if(fp == NULL){		
		return 0;
	}
	size = 0;
	points = get_breakpoints(fp, &size); // call get_breakpoints()
	if(points == NULL){
		printf("No breakpoints read.\n");
		fclose(fp);
		return 1;
	}
	if(size < 2){
		printf("Error: at least two breakpoints required\n");		
		free(points);
		fclose(fp);
		return 1;
	}	
	// we require breakpoints to start from 0
	if(points[0].time != 0.0){
		printf("Error in breakpoint data: first time must be 0.0\n");		
		free(points);
		fclose(fp);
		return 1;
	}	
	printf("read %ld breakpoints\n", size);
	dur = points[size-1].time; // time of the last breakpoint
	printf("duration: %f seconds\n", dur);
	point = maxpoint(points, size);

	printf("maximum value: %f at %f secs\n",point.value,point.time);
	free(points);
	fclose(fp);
	return 0;
}

BREAKPOINT * get_breakpoints(FILE * fp, long * psize)
{
    int got; //return value from sscanf
    // npoints: No. of breakpoints; size: starting array size
    long npoints = 0, size = NPOINTS;
    double lasttime    = 0.0; // track the time of each new breakpoint
    BREAKPOINT * points = NULL; // points: array of breakpoints
    char line[LINELENGTH];
    
    if(fp == NULL)
        return NULL;
    points = (BREAKPOINT *) malloc(sizeof(BREAKPOINT) * size);
    if(points == NULL)
        return NULL;
    
    while(fgets(line,80,fp)){ // get a line of string
        if((got = sscanf(line, "%lf%lf", &points[npoints].time, &points[npoints].value) )<0)
            continue;			  // empty line
        if(got==0){
            printf("Line %ld has non-numeric data\n", npoints+1);
            break;
        }
        if(got==1){
            printf("Incomplete breakpoint found at point %ld\n", npoints+1);
            break;
        }
        if(points[npoints].time < lasttime){
            printf("error in breakpoint data at point %ld: time not increasing\n", npoints+1);
            break;
        }
        // track the time of each new breakpoint
        lasttime = points[npoints].time;
        if(++npoints == size){ // the buffer is full
            BREAKPOINT * tmp;
            size += NPOINTS;// increase size, then reallocate memory
            tmp = (BREAKPOINT *) realloc(points, sizeof(BREAKPOINT) * size);
            if(tmp == NULL)	{	// too bad!
                // have to release the memory, and return NULL to caller
                npoints = 0;
                free(points);
                points = NULL;
                break;		 
            }
            points = tmp; // assign the updated pointer to points
        }			
    }
    if(npoints)							
        *psize = npoints;	
    return points;
}

BREAKPOINT maxpoint(const BREAKPOINT* points,long npoints)
{
    int i;
    BREAKPOINT point; // return the pointer to the array of breakpoints
    
    point.time = 0.0;
    point.value = 0.0;
    
    for(i=0; i < npoints; i++){ // return the maximum breakpoint
        if(point.value < points[i].value){
            point.value = points[i].value;
            point.time = points[i].time;
        }
    }
    return point;
}

