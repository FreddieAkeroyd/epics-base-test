/*
 *      $Id$
 *
 *      Author  Jeffrey O. Hill
 *              johill@lanl.gov
 *              505 665 1831
 *
 *      Experimental Physics and Industrial Control System (EPICS)
 *
 *      Copyright 1991, the Regents of the University of California,
 *      and the University of Chicago Board of Governors.
 *
 *      This software was produced under  U.S. Government contracts:
 *      (W-7405-ENG-36) at the Los Alamos National Laboratory,
 *      and (W-31-109-ENG-38) at Argonne National Laboratory.
 *
 *      Initial development by:
 *              The Controls and Automation Group (AT-8)
 *              Ground Test Accelerator
 *              Accelerator Technology Division
 *              Los Alamos National Laboratory
 *
 *      Co-developed with
 *              The Controls and Computing Group
 *              Accelerator Systems Division
 *              Advanced Photon Source
 *              Argonne National Laboratory
 *
 *
 * History
 * $Log$
 * Revision 1.1.1.1  1996/06/20 00:28:16  jhill
 * ca server installation
 *
 *
 */


#ifndef casMonEventIL_h
#define casMonEventIL_h

//
// All functions here moved to casMonEvent.cc until
// I can determine what is causing them to end up 
// undefined
//

//
// casMonEvent::casMonEvent()
//
inline casMonEvent::casMonEvent () : 
	pValue(NULL), id(0u) {}

//
// casMonEvent::casMonEvent()
//
inline casMonEvent::casMonEvent (casMonitor &monitor, gdd &newValue) :
        pValue(&newValue),
        id(monitor.casRes::getId())
{
        int gddStatus;
        gddStatus = this->pValue->reference();
        assert (!gddStatus);
}

//
// casMonEvent::casMonEvent()
//
inline casMonEvent::casMonEvent (casMonEvent &initValue) :
        pValue(initValue.pValue),
        id(initValue.id)
{
        int gddStatus;
        if (this->pValue) {
                gddStatus = this->pValue->reference();
                assert (!gddStatus);
        }
}

//
// casMonEvent::operator =  ()
//
inline void casMonEvent::operator = (class casMonEvent &monEventIn)
{
	int gddStatus;
	if (this->pValue) {
		gddStatus = this->pValue->unreference();
		assert (!gddStatus);
	}
	if (monEventIn.pValue) {
		gddStatus = monEventIn.pValue->reference();
		assert (!gddStatus);
	}
	this->pValue = monEventIn.pValue;
	this->id = monEventIn.id;
}

//
//  casMonEvent::clear()
//
inline void casMonEvent::clear()
{
	int gddStatus;
	if (this->pValue) {
		gddStatus = this->pValue->unreference();
		assert (!gddStatus);
		this->pValue = NULL;
	}
	this->id = 0u;
}

//
// ~casMonEvent ()
//
inline casMonEvent::~casMonEvent ()
{
        this->clear();
}

//
// casMonEvent::getValue()
//
inline gdd *casMonEvent::getValue() const
{
	return this->pValue;
}

#endif // casMonEventIL_h

