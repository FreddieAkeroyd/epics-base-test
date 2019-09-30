/*************************************************************************\
* Copyright (c) 2006 UChicago Argonne LLC, as Operator of Argonne
*     National Laboratory.
* Copyright (c) 2002 The Regents of the University of California, as
*     Operator of Los Alamos National Laboratory.
* EPICS BASE is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution.
\*************************************************************************/
/* epicsMathTest.c
 *
 *      Author  Marty Kraimer
 */

#include "epicsUnitTest.h"
#include "epicsMath.h"
#include "testMain.h"

MAIN(epicsMathTest)
{
    double huge = 1e300;
    double tiny = 1e-300;
    double c;
    /*
     * we need to create these to avoid issues with "NaN + -NaN" etc and
     * compiler optimisation. In the real world we would
     * see a + -b rather than a + -a
     */
    float epicsINF_ = epicsINF;
    float epicsNAN_ = epicsNAN;
    
    testPlan(38);
    
    testOk1(!isnan(0.0));
    testOk1(!isinf(0.0));
    
    testOk1(!isnan(epicsINF));
    testOk1(isinf(epicsINF));
    testOk1(isinf(-epicsINF));

    testOk1(epicsINF == epicsINF_);
    testOk1(epicsINF > 0.0);
    testOk1(epicsINF - epicsINF_ != 0.0);

    testOk1(epicsINF + -epicsINF_ != 0.0);
    testOk1(-epicsINF + epicsINF_ != 0.0);

    testOk1(isnan(epicsINF - epicsINF));
    testOk1(isnan(0.0 * epicsINF));
    testOk1(isnan(epicsINF /epicsINF));

    testOk1(isnan(epicsINF + -epicsINF_));
    testOk1(isnan(-epicsINF + epicsINF_));
    
    testOk1(isnan(epicsNAN));
    testOk1(!isinf(epicsNAN));
    testOk1(epicsNAN != epicsNAN);
    testOk1(!(epicsNAN < epicsNAN));
    testOk1(!(epicsNAN <= epicsNAN));
    testOk1(!(epicsNAN == epicsNAN));
    testOk1(!(epicsNAN >= epicsNAN));
    testOk1(!(epicsNAN > epicsNAN));
    testOk1(isnan(epicsNAN - epicsNAN));

    testOk1(isnan(epicsNAN + -epicsNAN_));
    testOk1(isnan(-epicsNAN + epicsNAN_));
    
    c = huge / tiny;
    testOk(!isnan(c), "!isnan(1e300 / 1e-300)");
    testOk(isinf(c), "isinf(1e300 / 1e-300)");
    testOk(c > 0.0, "1e300 / 1e-300 > 0.0");
    
    c = (-huge) / tiny;
    testOk(!isnan(c), "!isnan(-1e300 / 1e-300)");
    testOk(isinf(c), "isinf(-1e300 / 1e-300)");
    testOk(c < 0.0, "-1e300 / 1e-300 < 0.0");
    
    c = huge / huge;
    testOk(!isnan(c), "!isnan(1e300 / 1e300)");
    testOk(!isinf(c), "!isinf(1e300 / 1e300)");
    testOk(c == 1.0, "1e300 / 1e300 == 1.0");
    
    c = tiny / tiny;
    testOk(!isnan(c), "!isnan(1e-300 / 1e-300)");
    testOk(!isinf(c), "!isinf(1e-300 / 1e-300)");
    testOk(c == 1.0, "1e300 / 1e-300 == 1.0");
    
    return testDone();
}
