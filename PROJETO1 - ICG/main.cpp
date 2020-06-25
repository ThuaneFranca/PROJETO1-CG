#include "main.h"

//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	tColor cor1 =  { .R = 255, .G = 0, .B = 0, .A = 100}; //RED
    tColor cor2 =  { .R = 0, .G = 0, .B = 255, .A = 100}; // GREY
    tColor cor3 =  { .R = 255, .G = 0, .B = 0, .A = 100}; // BLUE
    tColor cor4 =  { .R = 0, .G = 255, .B = 0, .A = 255}; // WHITE
    tColor cor5 =  { .R = 0, .G = 0, .B = 255, .A = 100};

// PONTOS X e Y  NA TELA
    tPixel p1 = {100, 30};
    tPixel p2 = {400, 50};
    tPixel p3 = {100, 100};
    tPixel p4 = {400, 100};
    tPixel p5 = {100, 150};
    tPixel p6 = {400, 200};
    tPixel p7 = {100, 200};
    tPixel p8 = {400, 250};
    tPixel p9 = {100, 350};
    tPixel p10 = {400, 300};
    tPixel p11 = {100, 400};
    tPixel p12 = {250, 350};


    drawTriangle(p1,p2,p3,cor1,cor2,cor3);
    putPixel(p12,cor5);
    //putPixel(p2,cor2);
    //putPixel(p3,cor3);
    //drawLine(p1,p2,cor1,cor2);
    //drawLine(p3,p4,cor3,cor4);
    drawLine(p5,p6,cor1,cor2);
    drawLine(p7,p8,cor4,cor5);
    //drawLine(p9,p10,cor1,cor2);
    //drawLine(p11,p12,cor5,cor3);

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

