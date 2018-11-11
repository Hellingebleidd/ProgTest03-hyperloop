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
    unsigned int riesenie[100][2];   //najdene riesenia c1, c2
    unsigned long long int rieseniePocet = 0;
    unsigned long int i;
    d1 = s1 + bulkhead;
    d2 = s2 + bulkhead;

    for (i = 0; (i*d1)<= (length - bulkhead); i++) {
        if ((length - bulkhead - (i*d1) ) % d2 == 0) {
            riesenie[rieseniePocet][0] = i;
            riesenie[rieseniePocet++][1] = (unsigned int) (length - (i*d1)) / d2;
        }
    }
    if (rieseniePocet == 0)
        return 0;
    else {
        *c1 = riesenie[0][0];
        *c2 = riesenie[0][1];
        printf("return %llu, %u x %u + %u x %u + bulkhead %u + bulkheadCol(%u) x %u = %llu  ma byt %llu\n ",
                (unsigned long long int)rieseniePocet+1, s1, *c1 , s2, *c2, bulkhead, *c1+*c2, bulkhead,
               (unsigned long long int)( s1*(*c1) + s2*(*c2) + bulkhead + ((*c1 + *c2) * bulkhead)),length );
        return rieseniePocet;
    }

}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    unsigned int c1, c2;
    assert (hyperloop(100, 4, 7, 0, &c1, &c2) == 4
            && 4 * c1 + 7 * c2 + 0 * (c1 + c2 + 1) == 100);
    assert (hyperloop(123456, 8, 3, 3, &c1, &c2) == 1871
            && 8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1) == 123456);
    assert (hyperloop(127, 12, 8, 0, &c1, &c2) == 0);
    assert (hyperloop(127, 12, 4, 3, &c1, &c2) == 1
            && 12 * c1 + 4 * c2 + 3 * (c1 + c2 + 1) == 127);
    assert (hyperloop(100, 35, 0, 10, &c1, &c2) == 1
            && c2 == 0
            && 35 * c1 + 10 * (c1 + 1) == 100);
    assert (hyperloop(110, 30, 30, 5, &c1, &c2) == 1
            && 30 * c1 + 30 * c2 + 5 * (c1 + c2 + 1) == 110);
    c1 = 2;
    c2 = 7;
    assert (hyperloop(110, 30, 30, 0, &c1, &c2) == 0 && c1 == 2 && c2 == 7);
    c1 = 4;
    c2 = 8;
    assert (hyperloop(9, 1, 2, 10, &c1, &c2) == 0 && c1 == 4 && c2 == 8);
    return 0;
}

#endif /* __PROGTEST__ */
