#include <unistd.h> 
#include <fcntl.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "p6.h"

int new_person (char *name, int age) {
    Person p;
    p.age = age;
    strcpy(p.name,name);
    int pos=0;

    int fd = open (FILENAME , O_WRONLY | O_APPEND | O_CREAT, 0600);
    if (fd < 0) return -1;    
    
    int res = write(fd,&p,sizeof(Person));
    if (res < 0) return -1;
    

    char buf[64];
    if ((pos = lseek(fd,-sizeof(Person),SEEK_END)) < 0 ) return -1;
    int bw = snprintf(buf,64,"registos %d\n",pos);
    write(1,buf,bw);

    // pos/sizeof(Person) --> registo x
    
    close(fd);
    return pos;
}

int person_change_age(char *name, int age) {
    int fd = open (FILENAME ,O_RDONLY, O_WRONLY);
    if (fd < 0) return -1;    
    
    int right_person = 0;
    int bytes_read = 0;
    int res;
    Person p;
      
    while (!right_person && (bytes_read = read(fd,&p,sizeof(Person))) > 0) {
        if (strcmp(p.name,name)==0) right_person = 1;
    }
    
    if (right_person == 1) {
        if (lseek(fd,-sizeof(Person),SEEK_CUR) < 0 ) return -1;
        p.age = age;
        res = write(fd,&p,sizeof(Person));
        if (res < 0) return -1;
    }
    
    return 0;

}

int person_change_age_v2(long pos,int age) {
    int fd = open (FILENAME ,O_RDONLY, O_WRONLY);
    if (fd < 0) return -1;    
    if (lseek(fd,pos,SEEK_SET) < 0 ) return -1;
 
    Person p;
    read(fd,&p,sizeof(Person));
    p.age=age;
    write(fd,&p,sizeof(Person));
    
    return 0;
}


