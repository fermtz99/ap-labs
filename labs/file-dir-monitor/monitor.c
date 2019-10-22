#include <stdio.h>
#include <ftw.h>
#include <sys/inotify.h>
#include "logger.h"

int main(int argc, char** argv){
	int inotifyFileD;
	int watch;
	ssize_t numRead;
	if(argc == 2) {
		inotifyFileD = inotify_init();
		if(inotifyFileD == -1)
			errorf("iNotify not created\n");
		watcher = inotify_add_watch(inotifyFileD, argv[1], IN_ALL_EVENTS);
		if(watch == -1)
			errorf("Watch not created");
	}
	else
		infof("Usage: ./monitor 'path'");

    // Place your magic here
    return 0;
}
