#include "local.h"

static void dsply_hndlr(void);
static void kbd_hndlr(unsigned char key, int x, int y);
static void vw_init(char *title);

/* dsply_hndlr -- dsply (redraw) handler */
static void dsply_hndlr(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    mdl_redraw();
    glFlush();
}

/* kbd_hndlr -- keyboard handler */
static void kbd_hndlr(
    unsigned char key,
    int x,
    int y)
{
    switch (key) {

    case '\033':  /* ESC */
    case 'q':
    case 'Q':
        exit(EXIT_SUCCESS);
        break;
    }
}

/* vw_init -- initialize the view */
static void vw_init(
    char *title)
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WH_WINDOW, WH_WINDOW);
    glutCreateWindow(title);
}

int main(
    int argc,
    char *argv[])
{
    glutInit(&argc, argv);
    vw_init(argv[0]);
    mdl_init(&argv[1]); /* use command line arguments as parameters */
    glutDisplayFunc(dsply_hndlr);
    glutKeyboardFunc(kbd_hndlr);
    glutMainLoop();
    exit(EXIT_SUCCESS); /* not reached, but this stops gcc complaints */
}

