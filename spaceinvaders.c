#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <gl/gl.h>
#include "SOIL.h"
#include "spaceinvaders.h"

#define TAM 0.1f
#define MAT2X(j) ((j)*0.1f-1)
#define MAT2Y(i) (0.9-(i)*0.1f)

struct TNave {
    int xInicial,yInicial,x,y;
    int passo;
    int vivo;
};

struct TMonstro {
    int xInicial,yInicial,x,y;
    int vivo;
    int tipo;
};

struct TTiro {
    int xInicial,yInicial,x,y;
    int status;
};

GLuint naveTex2d;
GLuint monstroTex2d[3];
GLuint morteTex2d[3];
GLuint tiroTex2d;

static void desenhaSprite(float coluna,float linha, GLuint tex);
static GLuint carregaArqTextura(char *str);

void carregaTexturas(){
    int i;
    char str[50];
    for(i=0; i<3; i++){
        sprintf(str,".//Sprites//monstro%d.png",i);
        monstroTex2d[i] = carregaArqTextura(str);
    }

    /*for(i=0; i<3; i++){
        sprintf(str,".//Sprites//morte%d.png",i);
        morteTex2d[i] = carregaArqTextura(str);
    } */

    sprintf(str, ".//Sprites//nave.png");
    naveTex2d = carregaArqTextura(str);

    sprintf(str, ".//Sprites//tiro.png");
    tiroTex2d = carregaArqTextura(str);
}

Nave* nave_cria(int x, int y) {
    Nave *nave = malloc(sizeof(Nave));
    if(nave!=NULL) {
        nave->xInicial = x;
        nave->yInicial = y;
        nave->x = x;
        nave->y = y;
        nave->passo = 4;
        nave->vivo = 1;
    }
    return nave;

}

void nave_desenha(Nave *nave) {
    desenhaSprite(MAT2X(nave->x),MAT2Y(nave->y),naveTex2d);
}

void nave_movimenta(Nave *nave, int direcao) {
    nave->x += direcao;
}

Monstro* monstro_cria(int x, int y) {
    Monstro* monstro = malloc(sizeof(Monstro));
    if (monstro != NULL) {
        monstro->xInicial = x;
        monstro->yInicial = y;
        monstro->x = x;
        monstro->y = y;
        monstro->vivo = 1;
    }

    return monstro;
}

void monstro_desenha(Monstro* monstro, int tipo) {
    desenhaSprite(MAT2X(monstro->x),MAT2Y(monstro->y),monstroTex2d[tipo]);
}

void monstro_movimenta(Monstro* monstro, int direcao) {
    monstro->x += 1;
}

Tiro* tiro_cria(int x, int y) {
    Tiro* tiro = malloc(sizeof(Tiro));
    if (tiro != NULL) {
        tiro->xInicial = x;
        tiro->yInicial = y;
        tiro->x = x;
        tiro->y = y;
        tiro->status = 0;
    }

    return tiro;
}

void tiro_desenha(Tiro *tiro) {
    if (tiro->status == 1) {
        desenhaSprite(MAT2X(tiro->x),MAT2Y(tiro->y),tiroTex2d);
        tiro_movimenta(tiro);
    }
}

void tiro_movimenta(Tiro *tiro) {
    tiro->y -= 1;
}

void tiro_dispara(Tiro *tiro) {
    tiro->status = 1;
}

static GLuint carregaArqTextura(char *str){
    // http://www.lonesock.net/soil.html
    GLuint tex = SOIL_load_OGL_texture
        (
            str,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
            SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );

    /* check for an error during the load process */
    if(0 == tex){
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    return tex;
}

void desenhaSprite(float coluna,float linha, GLuint tex){
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f); glVertex2f(coluna, linha);
        glTexCoord2f(1.0f,0.0f); glVertex2f(coluna+TAM, linha);
        glTexCoord2f(1.0f,1.0f); glVertex2f(coluna+TAM, linha+TAM);
        glTexCoord2f(0.0f,1.0f); glVertex2f(coluna, linha+TAM);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

}
