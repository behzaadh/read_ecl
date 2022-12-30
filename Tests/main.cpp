#include "read_ecl.h"

int main(void)
{
    READ_ECL slb("../Examples/2D.S0001");
    slb.printVector("PARAMS");

    return 0;
}
