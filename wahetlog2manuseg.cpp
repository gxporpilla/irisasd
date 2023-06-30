#include "version.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <opencv2/core/core.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

#ifdef __linux__ 
#define DIRDELIM '/'
#elif _WIN32
#define DIRDELIM '\\'
#include "win_getline.h"
#endif

void usage(){
    printVersion();
	printf("+-----------------------------------------------------------------------------+\n");
	printf("| wahetlog2manuseg                                                            |\n");
	printf("|                                                                             |\n");
	printf("| Generates points as required by manuseg from extraction log files as        |\n");
	printf("| output by wahet.                                                            |\n");
	printf("| These files can then be used by manuseg to segment drop in masks to have    |\n");
	printf("| the same normalisation as the iris texture.                                 |\n");
	printf("|                                                                             |\n");
	printf("| Requires two arguments:                                                     |\n");
	printf("|  1) Input file as produced by wahet log option (-l)                         |\n");
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

void writepoints( std::string where, int x, int y, int w, int h, int a, int num=36){
    float delta =360./int(num+0.5);
    std::vector<cv::Point> pts;
    cv::ellipse2Poly(cv::Point(x,y), cv::Size(w,h), a, 0, 360, (int)delta, pts);
    FILE *fh = fopen(where.c_str(), "w");
    if( fh == NULL){
        fprintf(stderr, "EE: Could not open %s for writing.\n",where.c_str());
        exit(2);
    }
    int count=0;
    for( auto p : pts){
        fprintf(fh, "%d %d\n", p.x, p.y);
        count++;
    }
    if (count < 5) printf("EE: less than 5 points written for ellipse at %d,%d with width %d and height %d\n",x,y,w,h);
    if (count < 5 and  pts.size() > 0 ) {//repeat last because likely with or height is 0
        printf("II: assuming a point and continue with point.\n");
        auto p = pts.back();
        while( count++ < 5) fprintf(fh, "%d %d\n", p.x, p.y);
    }
    fclose(fh);
}

void convert_wahet( const char * infile, const std::string &outdir){
    FILE *fh = fopen(infile, "r");
    if( fh == NULL){
        fprintf(stderr, "EE: Could not open %s for reading.\n",infile);
        exit(1);
    }
    char *line = NULL; 
    size_t  linelength = 0;
    char filename[1025];
    float ai,xi,yi,wi,hi;
    float ao,xo,yo,wo,ho;
    while( !feof(fh)){
        getline(&line, &linelength, fh);
        if( line[0] == '#'){
            printf("DISCARD %s", line);
            continue;
        }
        int nm = sscanf(line, "%1024s %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                filename, &xi, &yi, &wi, &hi, &ai, &xo, &yo, &wo, &ho, &ao);
        cleanup(filename);
        // bounding box to axis
        hi /= 2.; wi /= 2.;
        ho /= 2.; wo /= 2.;
        if( nm != 11){
            printf("DISCARD %s", line);
            continue;
        }
        printf("%s", line);
        writepoints(outdir+DIRDELIM+std::string(filename)+".inner.txt", (int)xi,(int)yi,(int)wi, (int)hi, (int)ai);
        writepoints(outdir+DIRDELIM+std::string(filename)+".outer.txt", (int)xo,(int)yo,(int)wo, (int)ho, (int)ao);
    }
    free(line);
    fclose(fh);
}


int main(int argc, char ** argv) {
    if (argc < 3) usage();
    convert_wahet( argv[1], argv[2]);
}
