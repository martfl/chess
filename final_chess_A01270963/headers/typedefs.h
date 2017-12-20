#pragma once
//EASIER THAN SETTING UP WHOLE CLASS

typedef struct _Material
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} Material;

static Material White =
{
    { 0.5, 0.5, 0.5, 1.0 },
    { 0.8, 0.8, 0.8, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 },
    100.0
};

static Material Black =
{
    { 0.1, 0.1, 0.1, 1.0 },
    { 0.1, 0.1, 0.1, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 },
    100.0
};

static Material Red =
{
    { 1.0, 0.0, 0.0, 1.0 },
    { 1.0, 0.0, 0.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 },
    100.0
};

static Material Yellow =
{
    { 1.0, 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 },
    { 1.0, 1.0, 1.0, 1.0 },
    100.0
};

typedef enum
{
    NONE = 0,
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK,
    PAWN
} Piece;

static Piece board[8][8] =
{
    {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK},
    {PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN},
    {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
    {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
    {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
    {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
    {(Piece)-PAWN, (Piece)-PAWN, (Piece)-PAWN, (Piece)-PAWN, (Piece)-PAWN, (Piece)-PAWN, (Piece)-PAWN, (Piece)-PAWN},
    {(Piece)-ROOK, (Piece)-KNIGHT, (Piece)-BISHOP, (Piece)-QUEEN, (Piece)-KING, (Piece)-BISHOP, (Piece)-KNIGHT, (Piece)-ROOK}
};

#define MAX_STEPS 32
#define ACCELERATION 0.1
#define FRICTION 0.1
#define ABSORB 0.6
#define PI 3.1415927

void static set_material(Material material) {
    glMaterialfv(GL_FRONT, GL_DIFFUSE,material.diffuse);
    glMaterialfv(GL_FRONT, GL_AMBIENT,material.ambient);
    glMaterialfv(GL_FRONT, GL_SPECULAR,material.specular);
    glMaterialf(GL_FRONT, GL_SHININESS,material.shininess);
}
