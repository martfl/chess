#include "glm.h"
#include "gltx.h"
#include <stdlib.h>

extern GLfloat scalefactor;

class Chesspiece {
public:
    Chesspiece(char *filename);
    ~Chesspiece();
    
    char* file;
    float YT;
    float OB;
    float IB;
    float T;
    GLMmodel *object;
    GLfloat dimensions[3];
    int i;
    float height;
    int dlist;
    
    void display(void);
    void idle(void);
};

