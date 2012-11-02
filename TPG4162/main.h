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

int main(int argc, char * argv[]);

void redraw(void);          //declarations
void readFileToMatrix(char* filename);

void createTexture(bool wrap, int texture_num);

void cleanup();
void keyPressed (unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void mouseMove (int x, int y);
void reshape(int w, int h);


#endif
