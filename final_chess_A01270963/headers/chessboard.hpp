#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include "freeglut.h"
#endif

#include <stdlib.h>

extern GLint Marble, Wood;
extern GLboolean Texturing;

class Chessboard {
public:
    Chessboard();
    ~Chessboard();
    
    float YT;
    float OB;
    float IB;
    float T;
    GLint chessborder;
    GLint chessboard;
    
    void display(void);
    void idle(void);
};
