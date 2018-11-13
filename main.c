#ifndef __PROGTEST__

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#endif /* __PROGTEST__ */

unsigned long long int hyperloop(unsigned long long int length,
                                 unsigned int s1,
                                 unsigned int s2,
                                 unsigned int bulkhead,
                                 unsigned int *c1,
                                 unsigned int *c2) {
    unsigned int d1, d2;    //dlzka tubusu aj s bulkhead
    unsigned long long int rieseniePocet = 0, max;
    unsigned long int i;
//    printf("\nhyperloop(%llu, %u, %u, %u, %u, %u )=...", length, s1, s2, bulkhead, *c1, *c2);

    d1 = s1 + bulkhead;         //segment musi ma aj bulkhead
    d2 = s2 + bulkhead;         //segment musi ma aj bulkhead
    if (length <0 || (length < d1 && length < d2))
        return 0;

    length = length - bulkhead; //dlzka -prvy bulkhead
    if (length == 0) {          //len samotny bulkhead
        *c1 = 0;
        *c2 = 0;
        return 1;
    }

    if (s1 == 0) {      //ak s1 nemozno pouzit, tak 1 riesenie ak je delitelny d2
        if (s2 != 0 && ((length % d2) == 0)) {
            *c1 = 0;
            *c2 = (unsigned int) (length / d2);
            return 1;
        } else
            return 0;
    }

    if (s2 == 0 || s1 == s2) {    //ak s2 nemozno pouzit, alebo su rovnake, tak 1 riesenie ak je delitelny d2
        if ((length % d1) == 0) {
            *c1 = (unsigned int) (length / d1);
            *c2 = 0;
            return 1;
        } else
            return 0;
    }

    max = length / d1;
    for (i = 1; i <= max; i++) {
        if ((length - (i * d1)) % d2 == 0) {
            *c1 = i;
            *c2 = (unsigned int) (length - (i * d1)) / d2;
            rieseniePocet++;
        }
//        printf("i: %lu, riesenie pocet: %llu ", i, rieseniePocet);
    }
    if (rieseniePocet == 0) {
//        printf("toto nevyslo --------\n");
        return 0;
    } else {
 /*       printf("return %llu; s1:%u x c1:%u + s2:%u x c2:%u + bulkhead %u x %u = %llu  ma byt %llu\n ",
               (unsigned long long int) rieseniePocet, s1, *c1, s2, *c2, bulkhead, *c1 + *c2 + 1,
               (unsigned long long int) (s1 * (*c1) + s2 * (*c2) + ((*c1 + *c2 + 1) * bulkhead)), length + bulkhead);*/
        return rieseniePocet;
    }

}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    unsigned int c1, c2;
/*    hyperloop(100, 4, 7, 0, &c1, &c2);
    hyperloop(123456, 8, 3, 3, &c1, &c2);
    hyperloop(127, 12, 8, 0, &c1, &c2);
    hyperloop(127, 12, 4, 3, &c1, &c2);
    hyperloop(100, 35, 0, 10, &c1, &c2);
    hyperloop(110, 30, 30, 5, &c1, &c2);
    hyperloop(110, 30, 30, 0, &c1, &c2);
    hyperloop(9, 1, 2, 10, &c1, &c2);
    return 0;*/

    assert (hyperloop(100, 4, 7, 0, &c1, &c2) == 4
            && 4 * c1 + 7 * c2 + 0 * (c1 + c2 + 1) == 100);

    assert (hyperloop(123456, 8, 3, 3, &c1, &c2) == 1871
            && 8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1) == 123456);

    assert (hyperloop(127, 12, 8, 0, &c1, &c2) == 0);

    assert (hyperloop(127, 12, 4, 3, &c1, &c2) == 1
            && 12 * c1 + 4 * c2 + 3 * (c1 + c2 + 1) == 127);

    assert (hyperloop(100, 35, 0, 10, &c1, &c2) == 1
            && c2 == 0 && 35 * c1 + 10 * (c1 + 1) == 100);

    assert (hyperloop(110, 30, 30, 5, &c1, &c2) == 1
            && 30 * c1 + 30 * c2 + 5 * (c1 + c2 + 1) == 110);

    c1 = 2;
    c2 = 7;
    assert (hyperloop(110, 30, 30, 0, &c1, &c2) == 0
            && c1 == 2 && c2 == 7);

    c1 = 4;
    c2 = 8;
    assert (hyperloop(9, 1, 2, 10, &c1, &c2) == 0
            && c1 == 4 && c2 == 8);
    return 0;
}

#endif /* __PROGTEST__ */
