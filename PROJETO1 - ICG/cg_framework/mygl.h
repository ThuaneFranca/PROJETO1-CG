#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
typedef struct {
    int r;
    int g;
    int b;
} tipoCor;

typedef struct {
    tipoCor c;
    int x;
    int y;
} tipoPixel;

void PutPixel(int x, int y, int r, int g, int b)
{
        FBptr[(x*4) + (y*IMAGE_WIDTH*4) + 0] = r;
        FBptr[(x*4) + (y*IMAGE_WIDTH*4) + 1] = g;
        FBptr[(x*4) + (y*IMAGE_WIDTH*4) + 2] = b;
        FBptr[(x*4) + (y*IMAGE_WIDTH*4) + 3] = 255;

}

void DrawLine(int x0, int y0, int x1, int y1, tipoCor c1[], tipoCor c2[])
{
    int dx = x1 - x0; //Delta X
    int dy = y1 - y0; //Delta y
    int inclinacao = 0;

    if(dx < 0) // caso ponto final < ponto inicial
    {
        DrawLine(x1, y1, x0, y0, c2, c1);
        return;
    }


    int variacaoR = (c2->r) - (c1->r); //se a variacao for 0, vai incrementar 0
    int variacaoG = (c2->g) - (c1->g);
    int variacaoB = (c2->b) - (c1->b);

    unsigned int vdx = dx; //variacao de x e y a cada incremento na forma de inteiro sem sinal
    unsigned int vdy = dy;

    float tamLinha = sqrt((vdx*vdx) + (vdy*vdy)); //tamanho da linha a ser desenhada

    float addR = (float) variacaoR / tamLinha;
    float addG = (float) variacaoG / tamLinha;
    float addB = (float) variacaoB / tamLinha;

    float r0 = c1->r; //valores iniciais de RGB
    float g0 = c1->g;
    float b0 = c1->b;

    if(dy < 0)
    {
        inclinacao = -1;
    }
    else
    {
        inclinacao = 1;
    }

    if(dx == 0) //caso retas verticais (onde x não varia)
    {
        if(y0 < y1) //varia o y inicial ate o final
        {
            PutPixel(x0, y0, r0, g0, b0);
            while(y0++ < y1)
            {
                PutPixel(x0, y0, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }
        else //varia o y final ate o inicial
        {
            PutPixel(x0, y0, r0, g0, b0);
            while(y1++ < y0)
            {
                PutPixel(x0, y1, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }

        return;
    }

    int incr_e, incr_ne, d;
    int x = x0;
    int y = y0;

    PutPixel(x, y, r0, g0, b0);

    if(dx >= inclinacao * dy) // caso m <= 1
    {
        if(dy < 0) // caso y1 < y0
        {
            d = 2 * dy + dx;
            incr_e = 2 * dy;
            incr_ne = 2 * (dy + dx);
            while(x < x1)
            {
                if(d < 0)
                {
                    d += incr_ne;
                    x++;
                    y--;
                }
                else{
                    d += incr_e;
                    x++;
                }
                PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }
        else // caso y0 < y1
        {
            d = 2 * dy - dx;
            incr_e = 2 * dy;
            incr_ne = 2 * (dy - dx);

            if(dy == 0)
            {
                while(x < (x1 - 1))
                {
                    if(d < 0)
                    {
                        d += incr_e;
                        x++;
                    }
                    else
                    {
                        d += incr_ne;
                        x++;
                        y++;
                    }
                    PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                }
            }
            else
            {
                while(x < x1)
                {
                    if(d < 0)
                    {
                        d += incr_e;
                        x++;
                    }
                    else
                    {
                        d += incr_ne;
                        x++;
                        y++;
                    }
                    PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
                }
            }
        }
    }
    else // caso |m|>1
    {
        if(dy < 0) // caso y1 < y0
        {
            d = dy + 2 * dx;
            incr_e = 2 * dx;
            incr_ne = 2 * (dy + dx);
            while(y > y1)
            {
                if(d < 0)
                {
                    d += incr_e;
                    y--;
                }
                else
                {
                    d += incr_ne;
                    x++;
                    y--;
                }
                PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }
        else // caso y0 < y1
        {
            d = dy - 2 * dx;
            incr_e = -2 * dx;
            incr_ne = 2 * (dy - dx);
            while(y < y1)
            {
                if(d < 0)
                {
                    d += incr_ne;
                    x++;
                    y++;
                }
                else
                {
                    d += incr_e;
                    y++;
                }
                PutPixel(x, y, round(r0 += addR), round(g0 += addG), round(b0 += addB));
            }
        }
    }

}

void DrawTriangle(tipoPixel p1[], tipoPixel p2[], tipoPixel p3[])
{
    DrawLine(p1->x, p1->y, p2->x, p2->y, &p1->c, &p2->c);
    DrawLine(p2->x, p2->y, p3->x, p3->y, &p2->c, &p3->c);
    DrawLine(p3->x, p3->y, p1->x, p1->y, &p3->c, &p1->c);
}


#endif // _MYGL_H_

