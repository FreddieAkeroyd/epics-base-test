/* $Id$
 *      archive logMsg() from several IOC's to a common rotating file   
 *
 *
 *      Author:         Jeffrey O. Hill 
 *      Date:           080791 
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
 *      NOTES:
 *
 * Modification Log:
 * -----------------
 * .00 joh 080791  	Created
 * .01 joh 081591	Added epics env config
 * .02 joh 011995	Allow stdio also	
 */

#include <string.h>
#include <stdio.h>

#include <vxWorks.h>
#include <ioLib.h>
#include <taskLib.h>

#include <socket.h>
#include <in.h>

#include <inetLib.h>
#include <errnoLib.h>
#include <logLib.h>
#include <sockLib.h>


#include <envDefs.h>


FILE	*iocLogFile = NULL;
int 	iocLogFD = ERROR;
int 	iocLogDisable;

static long 		ioc_log_port;
static struct in_addr 	ioc_log_addr;

int 	iocLogInit();
static int	getConfig();
static void	failureNoptify();


/*
 *
 *	iocLogInit()
 *
 *
 */
int
iocLogInit()
{
	int            		sock;
        struct sockaddr_in      addr;
	int			status;

	if(iocLogDisable){
		return OK;
	}

	status = getConfig();
	if(status<0){
		logMsg (
			"iocLogClient: EPICS environment under specified\n",
			0,0,0,0,0,0);
		logMsg (
			"iocLogClient: failed to initialize\n",
			0,0,0,0,0,0);
		return ERROR;
	}

	/* allocate a socket       */
	sock = socket(AF_INET,		/* domain       */
		      SOCK_STREAM,	/* type         */
		      0);		/* deflt proto  */
	if (sock < 0){
		logMsg(	"iocLogClient: no socket errno %d\n", 
			errnoGet(),
			0,0,0,0,0);
		return ERROR;
	}

        /*      set socket domain       */
        addr.sin_family = AF_INET;

        /*      set the port    */
        addr.sin_port = htons(ioc_log_port);

        /*      set the port    */
        addr.sin_addr.s_addr = ioc_log_addr.s_addr;

	/* connect */
	status = connect(
			 sock,
			 (struct sockaddr *)&addr,
			 sizeof(addr));
	if (status < 0) {
		char name[INET_ADDR_LEN];

		inet_ntoa_b(addr.sin_addr, name);
		logMsg(
	"iocLogClient: unable to connect to %s port %d because \"%s\"\n", 
			(int) name,
			addr.sin_port,
			(int) strerror(errnoGet()),
			0,0,0);
		close(sock);
		return ERROR;
	}

	logFdAdd (sock);

	iocLogFile = fdopen (sock, "a");

	iocLogFD = sock;

	return OK;
}



/*
 *
 *	getConfig()
 *	Get Server Configuration
 *
 *
 */
static int
getConfig()
{
	long	status;

	status = envGetLongConfigParam(
			&EPICS_IOC_LOG_PORT, 
			&ioc_log_port);
	if(status<0){
		failureNoptify(&EPICS_IOC_LOG_PORT);
		return ERROR;
	}

	status = envGetInetAddrConfigParam(
			&EPICS_IOC_LOG_INET, 
			&ioc_log_addr);
	if(status<0){
		failureNoptify(&EPICS_IOC_LOG_INET);
		return ERROR;
	}

	return OK;
}



/*
 *
 *	failureNotify()
 *
 *
 */
static void
failureNoptify(pparam)
ENV_PARAM       *pparam;
{
	logMsg(	"IocLogClient: EPICS environment variable \"%s\" undefined\n",
		(int) pparam->name,
		0,0,0,0,0);
}




/*
 *
 *	unused
 *
 *
 */
#ifdef JUNKYARD
	ioTaskStdSet(taskIdSelf(), 1, sock);

	while (1) {
		date();
/*
		memShow(0);
		i(0);
		checkStack(0);
*/
		/*
		 * 60 min
		 */
		taskDelay(sysClkRateGet() * 60 * 60);
	}
#endif
