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

void paint(bool, int);
void redraw(void);
void mouseMove (int, int);
void reshape(int, int);
void mouseClick(int, int, int, int);
void readFileToMatrix(char*);
void init(void);
int main(int, char* argv[]);

#endif
