//
//  main.h
//  TPG4162-2
//
//  Created by Tri M. Nguyen on 10/21/12.
//
//

#include <iostream>
#include <GLUT/glut.h>

#ifndef TPG4162_2_main_h
#define TPG4162_2_main_h


static void redraw(void);          //declarations
int main(int argc, char * argv[]);
static void readFileToMatrix(char* filename);
void keyPressed (unsigned char key, int x, int y);
GLuint createTexture(bool wrap);
void mouseMove (int x, int y);
void reshape(int w, int h);

#endif
