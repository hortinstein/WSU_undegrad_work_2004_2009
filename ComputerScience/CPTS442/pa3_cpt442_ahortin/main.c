#include "local.h"


static void usage(void);

static char *progname = NULL;   /* set in main() */

int main(
    int argc,
    char *argv[])
{
    int ch;
    static int useDbuf = 1;      /* default: double buffering */

    progname = argv[0];
	glutInit(&argc, argv);

    while ((ch = getopt(argc, argv, "s?")) != -1) {
        switch (ch) {

        case 's':
            useDbuf = 0;
            break;

        case '?':
            usage();
            exit(0);
        }
    }

    mdl_init("Skeleton/body.ply",0);
	mdl_init("Skeleton/arm.ply",1);
	mdl_init("Skeleton/arm.ply",2);
	mdl_init("Skeleton/leg.ply",3);
	mdl_init("Skeleton/leg.ply",4);
    /*
     * Note that we must enable the viewer before we enable the
     * controller because otherwise GLUT has no "current window"
     * (i.e. viewer) to set the handlers for.
     */
    vw_init(progname, useDbuf);
    ctrl_init();

    glutMainLoop();
    fprintf(stderr, "*** unexpected return from glutMainLoop() -- exiting\n");
    exit(EXIT_FAILURE);
}

/* usage: issue a usage error message */
static void usage(void)
{
    (void) fprintf(stderr,
            "usage: %s [{args}] [{data file name}]\n", progname);
    (void) fprintf(stderr, "%s\n",
            " {args} are:");
    (void) fprintf(stderr, "%s\n",
            "  -s  use single buffering (default: double)");
    (void) fprintf(stderr, "%s\n",
            "  -?  this help message");
    return;
}
