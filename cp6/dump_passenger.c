#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "passenger.h"

void usage(void) {
    printf("Usage: program filename\n");
}

int readPassenger(Passenger *p) {
    printf("Last name: ");
    if(scanf("%39s",p->lastName) != 1 ) goto err;
    if (getchar()!='\n') goto err;
    printf("Initials: ");
    if(scanf("%c%c", &p->initials[0],&p->initials[1]) != 2 ) goto err;
    if (p->initials[1] != '\n' && getchar()!='\n') goto err;
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
    if (scanf("%c%c.%c%c.%c%c%c%c %c%c:%c%c",dt,dt+1,dt+2,dt+3,dt+4,dt+5,dt+6,dt+7,dt+8,dt+9,dt+10,dt+11) != 12) goto err;
    if (dt[11] != '\n' && getchar()!='\n') goto err;
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
    FILE *out = fopen(argv[1], "ab");
    if (!out) {
        perror("fopen");
        return 1;
    }
    if (readPassenger(&p)==0)
        fwrite(&p, sizeof(p), 1, out);
    else
        perror("readPassenger");
    return 0;
}
