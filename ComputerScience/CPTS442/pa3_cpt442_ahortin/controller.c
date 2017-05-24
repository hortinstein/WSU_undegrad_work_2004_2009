#include "local.h"

void kbd_hndlr(unsigned char key, int x, int y);
void mdl_redraw(void);

static int sxPrev, syPrev;

Quaternion qtnCur;
static Quaternion qtnPrev;

#ifdef USE_MOMENTUM
static int on_idle(XEvent *ev, void *data)
{
    if(!uiMain->main->visible || !uiMain->flobjGlcnvs->visible)
        return 0;

    qtn_add(qtnPrev, qtnCur, qtnCur);
    vw_redraw();
    return 0;
}
#endif

// on_mouseMotion -- called when the mouse is moved while a button is held down
static void on_mouseMotion(
    int sx,
    int sy)
{
    double fx0 = 1.0 - 2.0 * sxPrev / winW;
    double fy0 = 2.0 * syPrev / winH - 1.0;
    double fx1 = 1.0 - 2.0 * sx     / winW;
    double fy1 = 2.0 * sy     / winH - 1.0;

    trackball(qtnPrev, fx0, fy0, fx1, fy1);
    qtn_add(qtnPrev, qtnCur, qtnCur);
    sxPrev = sx;
    syPrev = sy;
    vw_redraw();
}

static void on_mouseClick(
    int btn,
    int state,
    int sx,
    int sy)
{
    switch (btn) {
        
    case GLUT_LEFT_BUTTON:
#ifdef USE_MOMENTUM
        if (state == GLUT_DOWN) {
            sxPrev = sxStart = sx;
            syPrev = syStart = sy;
            fl_set_idle_callback(NULL, 0);
        } else if (sxStart == sx && syStart == sy)
            fl_set_idle_callback(NULL, 0);
        else
            fl_set_idle_callback(on_idle, 0);
#else
        sxPrev = sx;
        syPrev = sy;
#endif
        break;
        
    default:
        /* ignore other buttons (for now) */
        break;
    }
}

/* on_redraw -- dsply (redraw) handler */
void on_redraw(void)
{
    vw_redraw();
}

/* on_keyPress -- keyboard handler */
void on_keyPress(
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

void ctrl_init(void)
{
    /* initialize trackball */
    trackball(qtnCur, 0.0, 0.0, 0.0, 0.0);

	glutDisplayFunc(on_redraw);
	glutMouseFunc(on_mouseClick);
    glutMotionFunc(on_mouseMotion);
    glutKeyboardFunc(on_keyPress); // "normal" (not "special") keys
}
