#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "passenger.h"



static void usage(void) {
    printf("Usage: program filename\n");
}

static int readPassenger(Passenger *p) {
    printf("Last name: ");
    scanf("%39s",p->lastName);
    if (getchar()!='\n') goto err;
    printf("Initials: ");
    if(scanf("%c%[^\n]c", &p->initials[0],&p->initials[1]) != 2) goto err;
    if (getchar()!='\n') goto err;
    printf("Amount of items: ");
    scanf("%hhu", &p->amountOfItems);
    if (getchar()!='\n') goto err;
    printf("Total weight of items: ");
    scanf("%hhu", &p->totalWeightOfItems);
    if (getchar()!='\n') goto err;
    printf("Destination: ");
    scanf("%39s",p->destination);
    if (getchar()!='\n') goto err;
    printf("Departure Time (e.g. 01.01.2023 16:30): ");
    char *dt = p->departureTime;
    if (scanf("%c%c.%c%c.%c%c%c%c %c%c:%c%[^\n]c",dt,dt+1,dt+2,dt+3,dt+4,dt+5,dt+6,dt+7,dt+8,dt+9,dt+10,dt+11) != 12) goto err;
    if (getchar()!='\n') goto err;
    /*
    for (size_t i=0; i <= sizeof(p->departureTime);++i) {
        int c = fgetc(stdin);
        if (c != EOF && !(i==2 && c!='.') && !(i==5 && c!='.') && !(i==10 && c!=' ') 
            && !(i==13 && c!=':') && !(i==sizeof(p->departureTime) && c != '\n')) 
            {
            p->departureTime[i] = (char) c;
            }
        else goto err;
    }
    */
    printf("Has transfers? (y/n): ");
    unsigned char ans;
    scanf("%c", &ans);
    if (getchar()!='\n') goto err;
    if (ans == 'y') p->hasTransfers = true;
    else if (ans == 'n') p->hasTransfers = false;
    else goto err;
    printf("Amount of children: ");
    scanf("%hhu", &p->amountOfChildren);
    if (getchar()!='\n') goto err;
    return 0;
    err:
    errno = EINVAL;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage();
        return 1;
    }
    Passenger p;
    FILE *out = fopen(argv[1], "wb");
    if (!out) {
        perror("Can't open file");
        return 1;
    }
    while (readPassenger(&p)==0)
        fwrite(&p, sizeof(p), 1, out);
    return 0;
}
