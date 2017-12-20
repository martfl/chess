#include <unistd.h>
#include "chessgame.hpp"

GLfloat scalefactor = 0.0;

GLuint Select_Buffer[128];  /* select buffer */

GLint
Win_Width       = 500,
Win_Height      = 500,
Mouse_X         = -1,
Mouse_Y         = -1,
Old_Mouse_X     = -1,
Old_Mouse_Y     = -1,
Move_Mouse_X    = -1,
Move_Mouse_Y    = -1,
Marble          = 0,
Wood            = 0;


GLfloat
X_Rot   = 40.0,
Spin    = 20.0,
Z_Trans = -20.0;

GLboolean
Texturing = GL_TRUE,
Start_Moving = GL_FALSE,
Grabbing  = GL_FALSE;


GLfloat fallht[MAX_STEPS];
int Fall_Steps;
int Turn;
Game *game;

void init()
{
    int cnt;
    GLfloat ht, vc;
    
    glEnable(GL_DEPTH_TEST);
    GLfloat ambient[]  = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat global_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glPolygonMode(GL_FRONT, GL_FILL);
    glSelectBuffer(128, Select_Buffer);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    game->texture();
    Texturing ? glEnable(GL_TEXTURE_2D) : glDisable(GL_TEXTURE_2D);
    
    ht = 1.0;
    vc = 0.0;
    
    for (cnt = 0; cnt < MAX_STEPS; cnt++)
    {
        ht -= vc;
        vc += ACCELERATION;
        if (ht < 0)
        {
            ht = 0;
            vc = (-vc * (1 - ABSORB)) + FRICTION;
            if (vc > 0) break;
        }
        fallht[cnt] = ht;
    }
    fallht[cnt] = 0;
    Fall_Steps = cnt + 1;
    Turn = 1;
    game = new Game();
    game->get_objects();
    
}

void idle()
{
    game->render();
    
}


void display()
{
    //ALL RENDERING IS DONE DURING IDLE
    idle();
}

void reshape(int width, int height)
{
    Win_Width = width;
    Win_Height = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, 1.0, 1.0, 64.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    game->move(key);
}


//USED TO GET MOUSE COORDINATES ON BOARD
/*
     FUNCTION OBTAINED FROM
     https://www.opengl.org/archives/resources/code/samples/glut_examples/demos/demos.html
 */
void selection(int x, int y)
{
    static GLint vp[4];
    int hits;
    
    hits = glRenderMode(GL_SELECT);
    glInitNames();
    glPushName((unsigned)-1);
    
    glPushMatrix();
    {
        /* reset the projection */
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        /* get the current viewport */
        glGetIntegerv(GL_VIEWPORT, vp);
        
        /* set up a picking matrix */
        gluPickMatrix(x, Win_Height-y, 5.0, 5.0, vp);
        
        /* set the viewing frustum */
        gluPerspective(30.0, 1.0, 1.0, 64.0);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        /* default translation - translate in Z because
         * most everything is drawn at or around (0, 0, 0)
         */
        glTranslatef(0.0, 0.0, Z_Trans);
        
        /* rotation around the X axis (tilt toward plane of screen) */
        glRotatef(X_Rot, 1.0, 0.0, 0.0);
        glRotatef(Spin, 0.0, 1.0, 0.0);
        
        glCallList(game->chess->chessboard);
        
    } glPopMatrix();
    
    /* see how many hits we got */
    hits = glRenderMode(GL_RENDER);
    
    /* reset to the correct matrices */
    reshape(Win_Width, Win_Height);
    
    if(hits)
    {
        Mouse_X = (Select_Buffer[3] % 32) / 4;
        Mouse_Y = 7 - ((Select_Buffer[3] % 4) * 2 +
                       (((Select_Buffer[3] % 8) / 4) ^
                        (Select_Buffer[3] / 32)));
    }
    else
    {
        Mouse_X = Old_Mouse_X;
        Mouse_Y = Old_Mouse_Y;
    }
}

void motion(int x, int y)
{
    if(Grabbing)
    {
        selection(x, y);
        glutPostRedisplay();
    }
}

int checkturn(int x, int y, int turn) {
    Piece moving_piece = board[y][x];
    printf("Piece moving: %d", moving_piece);
    if(moving_piece < 0 && turn == -1) {
        return 1;
    } else if ( moving_piece > 0 && turn == 1) {
        return 1;
    } else {
        return 0;
    }
}

void mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_LEFT)
        {
            Grabbing = GL_TRUE;
            selection(x, y);
            Old_Mouse_X = Mouse_X;
            Old_Mouse_Y = Mouse_Y;
        }
        else
            Grabbing = GL_FALSE;
    }
    else if(state == GLUT_UP)
    {
        if (game->validate_move(Mouse_X, Mouse_Y, Old_Mouse_X, Old_Mouse_Y) == 1) {
            printf("FROM x: %d, y: %d\n", Old_Mouse_X, Old_Mouse_Y);
            printf("TO x: %d, y: %d\n", Mouse_X, Mouse_Y);
            printf("TURN: %d\n", Turn);
            if(button == GLUT_LEFT)
            {
                Move_Mouse_X = Mouse_X;
                Move_Mouse_Y = Mouse_Y;
            }
            Turn *= -1;
            Grabbing = GL_FALSE;
            Start_Moving = GL_TRUE;
        }
    }
}

int main(int argc, char* argv[])
{
    glutInitWindowSize(Win_Width, Win_Height);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("garry - a chess game.");
    init();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutMainLoop();
    
    return 0;
}
