/*  
 *  $Id$
 *
 *                              
 *                    L O S  A L A M O S
 *              Los Alamos National Laboratory
 *               Los Alamos, New Mexico 87545
 *                                  
 *  Copyright, 1986, The Regents of the University of California.
 *                                  
 *           
 *	Author Jeffrey O. Hill
 *	johill@lanl.gov
 *	505 665 1831
 */

#include "iocinf.h"

#define epicsExportSharedSymbols
#include "cacIO.h"
#undef epicsExportSharedSymbols

cacChannelNotify::~cacChannelNotify () 
{
}

bool cacChannelNotify::includeFirstConnectInCountOfOutstandingIO () const
{
    return false;
}
