#include "version.h"
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifdef __linux__ 
#define DIRDELIM '/'
#elif _WIN32
#define DIRDELIM '\\'
#include "win_getline.h"
#endif

void usage(){
    printVersion();
	printf("+-----------------------------------------------------------------------------+\n");
	printf("| cahtlog2manuseg                                                             |\n");
	printf("|                                                                             |\n");
	printf("| Generates points as required by manuseg from extraction log files as        |\n");
	printf("| output by caht.                                                             |\n");
	printf("| These files can then be used by manuseg to segment drop in masks to have    |\n");
	printf("| the same normalisation as the iris texture.                                 |\n");
	printf("|                                                                             |\n");
	printf("| Requires two arguments:                                                     |\n");
	printf("|  1) Input file as produced by caht log option (-l)                          |\n");
	printf("|  2) Output directory to write the manuseg inner and outer files to.         |\n");
    printf("|                                                                             |\n");
    printf("| AUTHOR                                                                      |\n");
    printf("|   Heinz Hofbauer (hhofbaue@cosy.sbg.ac.at)                                  |\n");
    printf("|                                                                             |\n");
    printf("| COPYRIGHT                                                                   |\n");
    printf("| (C) 2017 All rights reserved. Do not distribute without written permission. |\n");
	printf("+-----------------------------------------------------------------------------+\n");
    exit(0);
}

void cleanup(char *filename){
    char buffer[1024];
    int start = strlen(filename);
    for(; start >=0; start--)
        if( filename[start] == '.'){
            filename[start] = '\0';
            break;
        }
    //if no file ending was supplied:
    if( start == -1 ) start = strlen(filename);
    for( ; start > 0; start--) 
        if( filename[start-1] == DIRDELIM)
            break;
    strcpy(buffer, &filename[start]);
    strcpy(filename, buffer);
}

void writepoints( std::string where, int x, int y, int r, int num=36){
    FILE *fh = fopen(where.c_str(), "w");
    if( fh == NULL){
        fprintf(stderr, "EE: Could not open %s for writing.\n",where.c_str());
        exit(2);
    }
    float as = 2*M_PI/num;
    for( int i =0 ; i < num; i++){
        fprintf(fh, "%d %d\n", 
                (int)round(x+cos( i*as)*r),
                (int)round(y+sin( i*as)*r)
               );
    }
    fclose(fh);
}

void convert_caht( const char * infile, const std::string &outdir){
    FILE *fh = fopen(infile, "r");
    if( fh == NULL){
        fprintf(stderr, "EE: Could not open %s for reading.\n",infile);
        exit(1);
    }
    char *line = NULL; 
    size_t  linelength = 0;
    char filename[1025];
    int ri,xi,yi;
    int ro,xo,yo;
    while( !feof(fh)){
	getline(&line, &linelength, fh);
        if( line[0] == '#'){
            printf("DISCARD %s", line);
            continue;
        }
        int nm = sscanf(line, "%1024s %d, %d, %d, %d, %d, %d\n",
                filename, &xo, &yo, &ro, &xi, &yi, &ri);
        cleanup(filename);
        if( nm != 7){
            printf("DISCARD %s", line);
            continue;
        }
        printf("%s", line);
        writepoints(outdir+DIRDELIM+std::string(filename)+".inner.txt", xi,yi,ri);
        writepoints(outdir+DIRDELIM+std::string(filename)+".outer.txt", xo,yo,ro);

    }
    free(line);
    fclose(fh);
}


int main(int argc, char ** argv) {
    if (argc < 3) usage();
    convert_caht( argv[1], argv[2]);
}
