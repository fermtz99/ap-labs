// Fernando Martinez
// A01630401

#include <stdio.h>
#include <ftw.h>
#include <sys/inotify.h>
#include <unistd.h>
#include "logger.h"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

struct inotify_event *event;

void displayEvent(struct inotify_event* event) {
	if (event->mask & IN_ACCESS)
		infof("File or directory was accesed\n");
	if (event->mask & IN_MODIFY)
		infof("File was modified\n");
	if (event->mask & IN_ATTRIB)
		infof("Metadata was modified\n");
	if (event->mask & IN_CREATE)
		infof("File or directory was created\n");
	if (event->mask & IN_DELETE)
		infof("File or directory was deleted\n");
	if (event->mask & IN_MOVE)
		infof("File renamed\n");
	if (event->mask & IN_OPEN)
		infof("File or directory was opened\n");
	if (event->mask & IN_CLOSE)
		infof("File opened was closed\n");
	if (event->mask & IN_MODIFY)
		infof("File or directory was modified");
}

int main(int argc, char** argv){
	int inotifyFileD;
	int watch;
	int rd;
	char *p;
	char buffer[EVENT_BUF_LEN];
	if(argc == 2) {
		infof("ready to read\n");
		inotifyFileD = inotify_init();
		if(inotifyFileD == -1)
			errorf("iNotify not created\n");
		watch = inotify_add_watch(inotifyFileD, argv[1], IN_ALL_EVENTS);
		if(watch == -1)
			errorf("Watch not created\n");
		while(1) {
			rd = read(inotifyFileD, buffer, EVENT_BUF_LEN);
			for (p = buffer; p < buffer + rd; ) {
				event = (struct inotify_event * ) p;
				displayEvent(event);
				p += EVENT_SIZE + event->len;
			}
		}
		inotify_rm_watch(inotifyFileD, watch);
		close(inotifyFileD);
	}
	else
		infof("Usage: ./monitor 'path'");

    // Place your magic here
    return 0;
}
