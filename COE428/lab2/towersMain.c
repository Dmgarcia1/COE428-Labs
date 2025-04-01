#include <stdlib.h>
#include <stdio.h>
#include "towers.h"

int main(int argc, char **argv)
{
    int n = 3;
    int from = 1;
    int dest = 2;
    if (argc > 1) {
		if(argc == 2){
		n = atoi(argv[1]);
		
		}
		else{
        n = atoi(argv[1]);
		from = atoi(argv[2]);
		dest = atoi(argv[3]);
		}	
    }

	if(n <= 0){
		fprintf(stderr, "Invalid number of disks");
		exit(1);
	}


	else if(from == dest){
		fprintf(stderr, "cannot move disk to its own tower");
		exit(1);
	}
	else if(from <1 || from > 3 || dest<1 || dest>3){
		fprintf(stderr, "Invalid tower number was inputted");
		exit(1);
	}
	
	
    towers(n, from, dest);
    exit(0);

}


	
	

