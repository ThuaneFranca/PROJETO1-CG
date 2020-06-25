#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define IMAGE_WIDTH  300 // número de colunas da imagem. 512
#define IMAGE_HEIGHT 300 // número de linhas da imagem.

unsigned char * FBptr;

typedef struct{
int R;
int G;
int B;
int A;
} tCorPonto;

typedef struct{
int posicaox;
int posicaoy;
} tPosicaoPonto;

struct RGBA{
          int Red;
          int Green;
          int Blue;
          int Alpha;
      }typedef RGBA;


      struct Vertex{
      int x;
      int y;
   }typedef Vertex;

/*typedef struct{
    int x;
    int y;
    int r;
    int g;
    int b;
}tPonto;*/
#endif // _DEFINITIONS_H_

