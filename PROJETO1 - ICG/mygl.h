#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************


void putPixel(tPixel ponto,tColor cor){
     int pos = 0;
     if (ponto.posx >= 0 && ponto.posx <=IMAGE_WIDTH &&ponto.posy >=0 && ponto.posy <= IMAGE_HEIGHT){

    		pos = (IMAGE_WIDTH*ponto.posy + ponto.posx)*4;
    		FBptr[pos]   = cor.R;
    		FBptr[pos+1] = cor.B;
    		FBptr[pos+2] = cor.G;
    		FBptr[pos+3] = cor.A;
    }
}
//Retorna a cor do pixel a ser pintado
tColor interpolColor(float p,tColor cor1, tColor cor2){
    tColor color;
    color.R = cor1.R*p + (1-p)*cor2.R;
    color.G = cor1.G*p + (1-p)*cor2.G;
    color.B = cor1.B*p + (1-p)*cor2.B;
    color.A = cor1.A*p + (1-p)*cor2.A;
    return color;
}
float dist(tPixel pixel1, tPixel pixel2){ // Calcula a distância entre dois pontos
    return sqrt((pixel2.posx-pixel1.posx)*(pixel2.posx-pixel1.posx)+(pixel2.posy-pixel1.posy)*(pixel2.posy-pixel1.posy)); // sqrt é uma função da biblioteca <math.h>  que calcula raiz quadrada
}

void drawLine(tPixel pixel1,tPixel pixel2,tColor cor1,tColor cor2){
    int oct;
    int dX = (pixel2.posx - pixel1.posx);
    int dY = (pixel2.posy - pixel1.posy);
    float distP;//distancia parcial do pixel inicial até o pixel final
    float distT = dist(pixel1,pixel2);//comprimento da reta
    int inclinacao;//da reta
    //Algoritmo de Braseham pra todos os octantes
    //
    if(dX<0)
    {
        drawLine(pixel2,pixel1,cor2,cor1);
        return;
    }
    if(dY<0)
        inclinacao = -1;
    else
        inclinacao = 1;

    int incE, incNE, d;//constantes de Braseham's
    tPixel pixel = pixel1;
    tColor cor = cor1;

    putPixel(pixel1,cor1);

    if(dX >= inclinacao*dY){//m<=1
        if(dY<0){
            d = 2*dY+dX;
            while(pixel.posx<pixel2.posx){
                if(d<0){
                    d += 2*(dY+dX);
                    pixel.posx++;
                    pixel.posy--;
                }
                else{
                    d+=2*dY;
                    pixel.posx++;
                }
                distP = dist(pixel,pixel2);
                cor = interpolColor(distP/distT,cor1,cor2);
                putPixel(pixel,cor);
            }
        }
        else{
            d=2*dY-dX;
            while(pixel.posx<pixel2.posx){
                if(d<0){
                    d+=2*dY;
                    pixel.posx++;
                }
                else{
                    d+=2*(dY-dX);
                    pixel.posx++;
                    pixel.posy++;
                }distP = dist(pixel,pixel2);
                cor = interpolColor(distP/distT,cor1,cor2);
                putPixel(pixel,cor);
            }
        }
    } else{ //m>1
        if(dY<0){
            d=dY+2*dX;
            while(pixel.posy > pixel2.posy){
                if(d<0){
                    d += 2*dX;
                    pixel.posy--;
                }
                else{
                    d+=2*(dY+dX);
                    pixel.posx++;
                    pixel.posy--;
                }
                distP = dist(pixel,pixel2);
                cor = interpolColor(distP/distT,cor1,cor2);
                putPixel(pixel,cor);
            } }
        else{
            d=dY-2*dX;
            while(pixel.posy<pixel2.posy){
                if(d<0){
                    d+=2*(dY-dX);
                    pixel.posx++;
                    pixel.posy++;
                }
                else{
                    d+=-2*dX;
                    pixel.posy++;
                }
                distP = dist(pixel,pixel2);
                cor = interpolColor(distP/distT,cor1,cor2);
                putPixel(pixel,cor); }
            }
        }
    putPixel(pixel2,cor2);
}

void drawTriangle(tPixel p1,tPixel p2,tPixel p3,tColor c1,tColor c2,tColor c3){
    drawLine(p1,p2,c1,c2);
    drawLine(p2,p3,c2,c3);
    drawLine(p3,p1,c3,c1);

}
    #endif // _MYGL_H_

