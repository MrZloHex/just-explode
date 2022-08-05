#include "explode.h"


int
main(int argc, char **argv)
{	
	Explode *explode = explode_initialize();
	while (explode_run(explode)) {}
	explode_deinitialize(explode);
	return 0;
}