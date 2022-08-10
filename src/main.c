#include "explode.h"


int
main()
{	
	Explode *explode = explode_initialize();
	while (explode_run(explode)) {}
	explode_deinitialize(explode);
	return 0;
}