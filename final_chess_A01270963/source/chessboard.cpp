#include "chessboard.hpp"

#define rnd ((float)rand() / ((float)RAND_MAX * 1.7))

Chessboard::Chessboard() {
    chessborder = 0;
    chessboard = 0;
    YT = -1.0;
    OB =  5.0;
    IB =  4.0;
    T = (YT - 0.75);
    
}

void Chessboard::display() {
    GLfloat x, z;
    GLfloat specular[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat brown[]    = { 0.857, 0.147, 0.000, 1.0 };
    GLfloat white[]    = { 1, 1, 1, 1.0 };
    GLfloat black[]     = { 0, 0, 0, 1.0 };
    int i, name;
    chessborder = glGenLists(1);
    glNewList(chessborder, GL_COMPILE);
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, brown);
        glMaterialfv(GL_FRONT, GL_AMBIENT, brown);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
        glBegin(GL_QUADS);
        {
            /* back */
            glTexCoord2f(0.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-OB, YT, -OB);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-IB, YT, -IB);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f( IB, YT, -IB);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f( OB, YT, -OB);
            
            /* right */
            glTexCoord2f(0.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f( OB, YT, -OB);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f( IB, YT, -IB);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f( IB, YT,  IB);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f( OB, YT,  OB);
            
            /* front */
            glTexCoord2f(0.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f( OB, YT,  OB);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f( IB, YT,  IB);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-IB, YT,  IB);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-OB, YT,  OB);
            
            /* left */
            glTexCoord2f(0.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-OB, YT,  OB);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-IB, YT,  IB);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-IB, YT, -IB);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(0.0, 1.0, 0.0);
            glVertex3f(-OB, YT, -OB);
        } glEnd();
        
        glBegin(GL_QUADS);
        {
            /* back */
            glTexCoord2f(0.0, 0.0);
            glNormal3f(0.0, 0.0, -1.0);
            glVertex3f(-OB, T, -OB);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(0.0, 0.0, -1.0);
            glVertex3f(-OB, YT, -OB);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(0.0, 0.0, -1.0);
            glVertex3f( OB, YT, -OB);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(0.0, 0.0, -1.0);
            glVertex3f( OB, T, -OB);
            
            /* right */
            glTexCoord2f(0.0, 0.0);
            glNormal3f(1.0, 0.0, 0.0);
            glVertex3f( OB, T, -OB);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(1.0, 0.0, 0.0);
            glVertex3f( OB, YT, -OB);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(1.0, 0.0, 0.0);
            glVertex3f( OB, YT,  OB);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(1.0, 0.0, 0.0);
            glVertex3f( OB, T,  OB);
            
            /* front */
            glTexCoord2f(0.0, 0.0);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f( OB, T,  OB);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f( OB, YT,  OB);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(-OB, YT,  OB);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(-OB, T,  OB);
            
            /* left */
            glTexCoord2f(0.0, 0.0);
            glNormal3f(-1.0, 0.0, 0.0);
            glVertex3f(-OB, T, OB);
            glTexCoord2f(0.0, 1.0);
            glNormal3f(-1.0, 0.0, 0.0);
            glVertex3f(-OB, YT,  OB);
            glTexCoord2f(1.0, 0.0);
            glNormal3f(-1.0, 0.0, 0.0);
            glVertex3f(-OB, YT, -OB);
            glTexCoord2f(1.0, 1.0);
            glNormal3f(-1.0, 0.0, 0.0);
            glVertex3f(-OB, T, -OB);
        } glEnd();
    }
    glEndList();
    chessboard = glGenLists(1);
    glNewList(chessboard, GL_COMPILE);
    {
        glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
        glMaterialfv(GL_FRONT, GL_AMBIENT, white);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
        
        i = name = 0;
        for(x = -4.0; x < 4.0; x += 1.0)
        {
            for(z = -4.0; z < 4.0; z += 1.0)
            {
                i++;
                if(i % 2)
                {
                    glLoadName(name++);
                    glBegin(GL_QUADS);
                    {
                        glTexCoord2f(0.0 + rnd, 1.0 + rnd);
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(x, YT, z);
                        glTexCoord2f(0.0 + rnd, 0.0 + rnd);
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(x, YT, z + 1.0);
                        glTexCoord2f(1.0 - rnd, 0.0 + rnd);
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(x + 1.0, YT, z + 1.0);
                        glTexCoord2f(1.0 - rnd, 1.0 - rnd);
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(x + 1.0, YT, z);
                    } glEnd();
                }
            }
            i++;
        }
        i = 1;
        
        glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glMaterialfv(GL_FRONT, GL_AMBIENT, black);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
        
        for(x = -4.0; x < 4.0; x += 1.0)
        {
            for(z = -4.0; z < 4.0; z += 1.0)
            {
                i++;
                if(i % 2)
                {
                    glLoadName(name++);
                    glBegin(GL_QUADS);
                    {
                        glTexCoord2f(0.0 + rnd, 1.0 + rnd);
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(x, YT, z);
                        glTexCoord2f(0.0 + rnd, 0.0 + rnd);
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(x, YT, z + 1.0);
                        glTexCoord2f(1.0 - rnd, 0.0 + rnd);
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(x + 1.0, YT, z + 1.0);
                        glTexCoord2f(1.0 - rnd, 1.0 - rnd);
                        glNormal3f(0.0, 1.0, 0.0);
                        glVertex3f(x + 1.0, YT, z);
                    } glEnd();
                }
            }
            i++;
        }
        
    } glEndList();
}

void Chessboard::idle() {
    glPushMatrix();
    {
        if(Texturing)
        {
            glEnable(GL_TEXTURE_2D);
            glCallList(Wood);
            glCallList(chessborder);
            glCallList(Marble);
            glCallList(chessboard);
            glDisable(GL_TEXTURE_2D);
        }
        else
        {
            glCallList(chessborder);
            glCallList(chessboard);
        }
    } glPopMatrix();
glTranslatef(-IB + 0.5, YT, IB - 0.5);
}
