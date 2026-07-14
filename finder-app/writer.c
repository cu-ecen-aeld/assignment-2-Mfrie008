#include "stdio.h"
#include "string.h"
#include "syslog.h"

int main(int argc, char **argv)
{
	FILE* writefilep; 
	size_t strLen, numWritten;

	// open user log
	openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

	// check num args
	if(argc != 3)
	{
		syslog(LOG_ERR, "Error: number of arguments incorrect");
		return 1;
	}

	// open and write file
	syslog(LOG_DEBUG, "Writing %s to file %s\n", argv[2], argv[1]);
	writefilep = fopen(argv[1], "w+");
	strLen = strlen(argv[2]);
	numWritten = fwrite(argv[2], 1, strLen, writefilep);
	fclose(writefilep);

	// check write success
	if(strLen != numWritten)
	{
		syslog(LOG_ERR, "Did not write the expected number of characters");
		return 1;
	}

	return 0;
}
