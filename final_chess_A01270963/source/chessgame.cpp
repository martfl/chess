//
//  chessgame.cpp
//  chess
//
//  Created by Martín Fernández on 10/26/17.
//  Copyright © 2017 Martín Fernández. All rights reserved.
//

#include "chessgame.hpp"

Game::Game(){
    chess = new Chessboard();
    
    pieces[1] = new Chesspiece("data/king.obj");
    pieces[2] = new Chesspiece("data/queen.obj");
    pieces[3] = new Chesspiece("data/bishop.obj");
    pieces[4] = new Chesspiece("data/knight.obj");
    pieces[5] = new Chesspiece("data/rook.obj");
    pieces[6] = new Chesspiece("data/pawn.obj");
    
}

void Game::get_objects() {
    chess->display();
    
    for(int i = 1; i <= 6; i++)
    {
        pieces[i]->display();
    }
}

void Game::texture()
{
    char * Marble_File   = "data/marble.rgb";
    char * Wood_File     = "data/woodgrain.rgb";
    GLTXimage *image;
    
    image = gltxReadRGB(Marble_File);
    Marble = glGenLists(1);
    glNewList(Marble, GL_COMPILE_AND_EXECUTE);
    {
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->width, image->height,GL_RGB, GL_UNSIGNED_BYTE, image->data);
        
    } glEndList();
    gltxDelete(image);
    
    image = gltxReadRGB(Wood_File);
    Wood = glGenLists(1);
    glNewList(Wood, GL_COMPILE_AND_EXECUTE);
    {
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->width, image->height,GL_RGB, GL_UNSIGNED_BYTE, image->data);
        
    } glEndList();
    gltxDelete(image);
}

void Game::render() {
    #define STEP 20.0
    static Piece piece = (Piece) 0, signed_piece, moving_piece = (Piece) 0;
    static GLboolean rising, falling, moving = GL_FALSE;
    static int steps, fallstep;
    static float dx, dy, dh, start_x, start_y, end_x, end_y;
    GLfloat light_position0[] = {  1.0, 1.0, 1.0, 0.0 };
    
    if(Start_Moving && Old_Mouse_Y != -1 && Old_Mouse_X != -1)
    {
        moving_piece = board[Old_Mouse_Y][Old_Mouse_X];
        board[Old_Mouse_Y][Old_Mouse_X] = NONE;
        
        start_x = Old_Mouse_X;
        start_y = Old_Mouse_Y;
        end_x = Move_Mouse_X;
        end_y = Move_Mouse_Y;
        
        dx = dy = dh = 0.0;
        steps = 1;
        
        rising = GL_TRUE;
        moving = GL_TRUE;
        Start_Moving = GL_FALSE;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glPushMatrix();
    {
        glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
        glTranslatef(0.0, 0.0, Z_Trans);
        glRotatef(X_Rot, 1.0, 0.0, 0.0);
        glRotatef(Spin, 0.0, 1.0, 0.0);
        
        chess->idle();
        
        glPushMatrix();
        {
            if(Grabbing)
            {
                glLineWidth(4.0);
            
                if(Grabbing && Old_Mouse_X != -1)
                {
                    /* draws yellow square on selection */
                    set_material(Yellow);
                    glPushMatrix();
                    {
                        glTranslatef((float)Old_Mouse_X, 0.01, (float)-Old_Mouse_Y);
                        glBegin(GL_LINE_LOOP);
                        {
                            glVertex3f(-0.5, 0.0, -0.5);
                            glVertex3f(-0.5, 0.0,  0.5);
                            glVertex3f( 0.5, 0.0,  0.5);
                            glVertex3f( 0.5, 0.0, -0.5);
                        } glEnd();
                        
                    } glPopMatrix();
                }
                
                /* draws red square on selection depending on mouse */
                set_material(Red);
                
                glTranslatef((float)Mouse_X, 0.01, (float)-Mouse_Y);
                
                glBegin(GL_LINE_LOOP);
                {
                    glVertex3f(-0.5, 0.0, -0.5);
                    glVertex3f(-0.5, 0.0,  0.5);
                    glVertex3f( 0.5, 0.0,  0.5);
                    glVertex3f( 0.5, 0.0, -0.5);
                } glEnd();
                
                glLineWidth(1.0);
            }
        } glPopMatrix();
        
        //MOVES PIECE TO NEW COORDINATES
        glPushMatrix();
        {
            if(moving)
            {
                /* calculate rising delta, if we are rising */
                if(rising)
                {
                    dh += 0.1;
                    if(dh > 1.0)
                        rising = GL_FALSE;  /* done rising */
                }
                else if(falling)  /* calculate falling delta, if falling */
                {
                    dh = fallht[fallstep];
                    fallstep++;
                    if(fallstep == Fall_Steps)
                    {
                        falling = GL_FALSE;  /* done falling */
                        moving = GL_FALSE;   /* we are done moving as well */
                        board[Move_Mouse_Y][Move_Mouse_X] = moving_piece;
                    }
                }
                else  /* must be moving over to the new tile */
                {
                    dx += (end_x - start_x) / STEP;
                    dy += (end_y - start_y) / STEP;
                    steps++;
                    if(steps > STEP)
                    {
                        falling = GL_TRUE;  /* done moving over, so fall now */
                        fallstep = 0;
                    }
                }
                
                if(moving_piece < 0)  /* -piece = piece is a black one */
                {
                    /* send a color for the piece */
                    glMaterialfv(GL_FRONT, GL_DIFFUSE,
                                 Black.diffuse);
                    glMaterialfv(GL_FRONT, GL_AMBIENT,
                                 Black.ambient);
                    glMaterialfv(GL_FRONT, GL_SPECULAR,
                                 Black.specular);
                    glMaterialf(GL_FRONT, GL_SHININESS,
                                Black.shininess);
                }
                else  /* +piece = piece is a white one */
                {
                    /* send a color for the piece */
                    glMaterialfv(GL_FRONT, GL_DIFFUSE,
                                 White.diffuse);
                    glMaterialfv(GL_FRONT, GL_AMBIENT,
                                 White.ambient);
                    glMaterialfv(GL_FRONT, GL_SPECULAR,
                                 White.specular);
                    glMaterialf(GL_FRONT, GL_SHININESS,
                                White.shininess);
                }
                
                /* set the actual piece (not negative) to
                 * index the Pieces array
                 */
                piece = moving_piece < 0 ? (Piece)-moving_piece : moving_piece;
                
                /* translate to the start tile & height */
                glTranslatef(start_x + dx,
                             pieces[piece]->height + dh,
                             -start_y - dy);
                
                /* rotate the knight if it is on the
                 * white side -- it only matches if
                 * the piece is a white KNIGHT (+KNIGHT)
                 */
                if(moving_piece == KNIGHT)
                    glRotatef(180.0, 0.0, 1.0, 0.0);
                
                /* draw the piece */
                glCallList(pieces[piece]->dlist);
            }
            
        } glPopMatrix();
        
        //LOOP THROUGH BOARD AND RENDER EACH PIECE
        glPushMatrix();
        {
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    glPushMatrix();
                    {
                        if (board[i][j] != 0)
                        {
                            signed_piece = board[i][j];
                            piece = signed_piece < 0 ? (Piece)-signed_piece : signed_piece;
                            
                            if(signed_piece < 0)  /* piece is black */
                            {
                                set_material(Black);
                            }
                            else  /* piece is white */
                            {
                                set_material(White);
                            }
                            
                            glTranslatef(j, pieces[piece]->height, -i);
                            
                            if(signed_piece == KNIGHT)
                                glRotatef(180.0, 0.0, 1.0, 0.0);
                            
                            glCallList(pieces[piece]->dlist);
                        }
                    } glPopMatrix();
                }
            }
        } glPopMatrix();
    } glPopMatrix();
    glutSwapBuffers();
}

void Game::move(unsigned char key) {
    switch(key)
    {
        case 27:                /* esc to exit */
            exit(1);
            break;
            
        case 'Z':                /* zoom in */
            Z_Trans += 0.25;
            break;
            
        case 'z':                /* zoom out */
            Z_Trans -= 0.25;
            break;
            
        case 'X':                /* up */
            X_Rot -= 2.0;
            break;
            
        case 'x':                /* down */
            X_Rot += 2.0;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int Game::validate_move(int DestinationX, int DestinationY, int OriginX, int OriginY)
{
    int Temp;
    Piece moving_piece = board[OriginY][OriginX];
    Piece dest_square = board[DestinationY][DestinationX];
    
    if (moving_piece == NONE) return 0;
    
    /* If attacking a piece of the same color */
    if (dest_square != NONE) {
        if (moving_piece > 0 && dest_square > 0) {
            return 0;
        } else if (moving_piece < 0 && dest_square < 0) {
            return 0;
        }
    }
    /* Check move validity for pawns of color white */
    Piece blackpiece = moving_piece < 0 ? (Piece)-moving_piece : moving_piece;
    if(moving_piece == PAWN)
    {
        if((OriginY == DestinationY -1) && DestinationX == OriginX && dest_square == NONE)
            return 1;
        else if((OriginY == DestinationY -2) && DestinationX == OriginX && dest_square == NONE && OriginY == 1 && board[OriginY + 1][OriginX] == NONE)
            return 1;
        else if ((OriginY == DestinationY -1) && abs(DestinationX - OriginX) == 1 && dest_square != NONE)
            return 1;
        else return 0;
    }
    /* Check move validity for pawns of color black */
    if( moving_piece < 0 && blackpiece == PAWN)
    {
        if((OriginY == DestinationY +1) && DestinationX == OriginX && dest_square == NONE)
            return 1;
        else if((OriginY == DestinationY  +2) && DestinationX == OriginX && dest_square == NONE && OriginY == 6 && board[OriginY - 1][OriginX] == NONE)
            return 1;
        else if ((OriginY == DestinationY +1) && abs(DestinationX - OriginX) == 1 && dest_square != NONE)
            return 1;
        else return 0;
    }
    /* Move validity for a Rook */
    if(moving_piece == ROOK || blackpiece == ROOK)
    {
        if((OriginY - DestinationY) * (OriginX - DestinationX) != 0)
            return 0;
        else if(OriginY - DestinationY == 0 )
        {
            if(DestinationX - OriginX > 0)
            {
                for(Temp = OriginX + 1; Temp < DestinationX; Temp++ )
                    if(board[OriginY][Temp] != NONE)
                        return 0;
            }
            else
            {
                for(Temp = OriginX - 1; Temp > DestinationX; Temp-- )
                    if(board[OriginY][Temp] != NONE)
                        return 0;
            }
        }
        else if(OriginX - DestinationX == 0 )
        {
            if(DestinationY - OriginY > 0 )
            {
                for(Temp = OriginY + 1; Temp < DestinationY; Temp++ )
                    if(board[Temp][OriginX] != NONE)
                        return 0;
            }
            else
            {
                for(Temp = DestinationY - 1; Temp > OriginY; Temp--)
                    if(board[Temp][OriginX] != NONE)
                        return 0;
            }
        }
    else return 1;
    }
    /* Move validity for a Knight */
    if( moving_piece == KNIGHT || blackpiece == KNIGHT)
    {
        if((DestinationY - OriginY) * (DestinationX - OriginX) != 0 && abs(DestinationY - OriginY) + abs(DestinationX - OriginX) == 3)
            return 1;
        else return 0;
    }
    /* Move validity for a Bishop */
    if(moving_piece == BISHOP || blackpiece == BISHOP)
    {
        if( abs(DestinationY - OriginY) == abs(DestinationX - OriginX))
        {
            int TempX;
            int TempY;
            int DeltaX;
            int DeltaY;

            if(DestinationY - OriginY > 0 ) { TempX =  OriginY + 1; DeltaX = 1; }
            else { TempX = OriginY -1 ; DeltaX = -1; }
            if(DestinationX - OriginX > 0 ) { TempY = OriginX + 1; DeltaY = 1; }
            else { TempY = TempY = OriginX - 1; DeltaY = -1; }
            
            for ( ; abs(TempX - DestinationY) > 0 && abs(TempY - DestinationX) > 0 ; TempX = TempX + DeltaX, TempY = TempY + DeltaY )
                if(board[TempX][TempY] != NONE)
                    return 0;
            return 1;
        }
        else return 0;
    }
    /* Move validity for a King */
    if( moving_piece == KING || blackpiece == KING )
    {
        if(abs(DestinationY - OriginY) + abs(DestinationX - OriginX) == 1)
            return 1;
        if(abs(DestinationY - OriginY) + abs(DestinationX - OriginX) == 2 && abs(DestinationY -OriginY) * abs(DestinationX - OriginX) != 0 )
            return 1;
        
        return 0;
    }
    /* Move validity for a Queen */
    if( moving_piece == QUEEN || blackpiece == QUEEN)
    {
        if( abs(DestinationY - OriginY) * abs(DestinationX - OriginX) == 0 )
        {
            if(DestinationY - OriginY == 0 )
            {
                if(DestinationX - OriginX > 0 )
                {
                    for(Temp = OriginX + 1; Temp < DestinationX; Temp++ )
                        if(board[OriginY][Temp] != NONE)
                            return 0;
                }
                else
                {
                    for(Temp = OriginX - 1; Temp > DestinationX; Temp-- )
                        if(board[OriginY][Temp] != NONE)
                            return 0;
                }
            }
            else if(DestinationX - OriginX == 0 )
            {
                if(DestinationY - OriginY > 0 )
                {
                    for(Temp = OriginY + 1; Temp < DestinationY; Temp++ )
                        if(board[Temp][OriginX] != NONE)
                            return 0;
                }
                
                else
                {
                    for(Temp = OriginY -1 ; Temp > DestinationY; Temp-- )
                    {
                        if(board[Temp][OriginX] != NONE)
                            return 0;
                    }
                }
            }
            return 1;
        }
        else if(abs(DestinationY - OriginY) == abs(DestinationX - OriginX))
        {
            int TempX;
            int TempY;
            int DeltaX;
            int DeltaY;
            
            if(DestinationY - OriginY > 0 ) { TempX =  OriginY + 1; DeltaX = 1; }
            else { TempX = OriginY -1 ; DeltaX = -1; }
            if( DestinationX - OriginX > 0 ) { TempY = OriginX + 1; DeltaY = 1; }
            else { TempY = TempY = OriginX - 1; DeltaY = -1; }
            
            for ( ; abs(TempX - DestinationY) > 0 && abs(TempY - DestinationX) > 0 ; TempX = TempX + DeltaX, TempY = TempY + DeltaY )
                if(board[TempX][TempY] != NONE)
                    return 0;
            
            return 1;
        }
        return 0;
    }
return 1;
}


