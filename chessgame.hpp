#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include "freeglut.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#include "typedefs.h"
#include "chessboard.hpp"
#include "chesspiece.hpp"

extern void selection(int x, int y);
extern GLboolean Start_Moving, Grabbing, rising;
extern GLint Old_Mouse_X, Old_Mouse_Y, Move_Mouse_X, Move_Mouse_Y, Mouse_X, Mouse_Y, Marble, Wood;
extern GLfloat X_Rot, Z_Trans, Spin;
extern GLfloat fallht[MAX_STEPS];
extern int Fall_Steps;
class Game {
public:
    Game();
    
    class Chessboard  *chess;
    Chesspiece *pieces[7];
    void render();
    void get_objects();
    void move(unsigned char key);
    void texture();
    int validate_move(int DestinationX, int DestinationY, int OriginX, int OriginY);
    
};
