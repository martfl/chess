#include "chesspiece.hpp"

Chesspiece::Chesspiece(char *filename) {
    file = filename;

}

void Chesspiece::display() {
    object = glmReadOBJ(file);
    if(!object)
        exit(1);
    if(!scalefactor) {
        scalefactor = glmUnitize(object);
    } else {
        glmScale(object, scalefactor);
    }
    glmScale(object, 1.2);
    /* generate normals if this
     * object doesn't have them.
     */
    dlist = glmList(object, GLM_SMOOTH);
    glmDimensions(object, dimensions);
    height = dimensions[1] / 2.0;
    glmDelete(object);
}

void Chesspiece::idle() {
    glCallList(dlist);
}
