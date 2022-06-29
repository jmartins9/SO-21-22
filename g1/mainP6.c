#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p6.h"

int main (int argc,char *argv[]) {
    

    if (argc==4) {
        if (strcmp(argv[1],"-i")==0) {
            new_person(argv[2],atoi(argv[3]));
        }

        if (strcmp(argv[1],"-u")==0) {
            person_change_age(argv[2],atoi(argv[3]));
        }

        if (strcmp(argv[1],"-o")==0) {
            person_change_age_v2(atoi(argv[2]),atoi(argv[3]));
        }
    }

}