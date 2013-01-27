
//
//  main.cpp
//  TPG4162-2
//
//  Created by Tri M. Nguyen on 10/21/12.
//
//

#include "main.h"

char** mat;

int traces;

bool leftButtonClicked;
int currentMousePositionX;
int currentMousePositionY;
int newMousePositionX;
int newMousePositionY;

float originalTranslate;

GLuint *textures;

void paint(bool wrap, int texture_num)
{

    char * texturedata = (char *)malloc(sizeof(char)*1024*1750*3);    
    int color;
    

    for (int x=0; x<1024; x++) {
        for (int y=0; y<1750; y++) {
            color = (mat[(texture_num*1024)+x][y]);
            
            if (color <= -96) {
                texturedata[y*1024*3+(3*x)] = 255;
                texturedata[y*1024*3+(3*x+1)] = 0;
                texturedata[y*1024*3+(3*x+2)] = 0;
            }
            else if (color <= -64) {
                texturedata[y*1024*3+(3*x)] = 255;
                texturedata[y*1024*3+(3*x+1)] = 100;
                texturedata[y*1024*3+(3*x+2)] = 0;
            }
            else if (color <= -32) {
                texturedata[y*1024*3+(3*x)] = 255;
                texturedata[y*1024*3+(3*x+1)] = 150;
                texturedata[y*1024*3+(3*x+2)] = 0;
            }
            else if (color <= 0) {
                texturedata[y*1024*3+(3*x)] = 255;
                texturedata[y*1024*3+(3*x+1)] = 200;
                texturedata[y*1024*3+(3*x+2)] = 0;
            }
            else if (color <= 32) {
                texturedata[y*1024*3+(3*x)] = 200;
                texturedata[y*1024*3+(3*x+1)] = 255;
                texturedata[y*1024*3+(3*x+2)] = 0;
            }
            else if (color <= 64) {
                texturedata[y*1024*3+(3*x)] = 210;
                texturedata[y*1024*3+(3*x+1)] = 255;
                texturedata[y*1024*3+(3*x+2)] = 0;
            }
            else if (color <= 96) {
                texturedata[y*1024*3+(3*x)] = 180;
                texturedata[y*1024*3+(3*x+1)] = 255;
                texturedata[y*1024*3+(3*x+2)] = 0;
            }
            else {
                texturedata[y*1024*3+(3*x)] = 0;
                texturedata[y*1024*3+(3*x+1)] = 255;
                texturedata[y*1024*3+(3*x+2)] = 0;
            }
            
        }
    }
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, wrap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, wrap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 1024, 1024, GL_RGB, GL_UNSIGNED_BYTE, texturedata);
    free(texturedata);
    
    // return texture;
}



void redraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    // semi-harry mouse dragging functionality
    double dMouse = (newMousePositionX - currentMousePositionX)/1000.0;
    currentMousePositionX = newMousePositionX;
    originalTranslate += dMouse;
    
    glTranslatef(originalTranslate, 0, 0);
    
    for (int i = 0; i < sizeof(textures); i++) {
        
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        paint(true, i);
        
        glPushMatrix();
        glTranslated(i+(i*0.6)+originalTranslate, 0, 0);
        
        glBegin( GL_QUADS );
        glTexCoord2d(0.0,0.0); glVertex2d(-.8,-.8);
        glTexCoord2d(1.0,0.0); glVertex2d(.8,-.8);
        glTexCoord2d(1.0,1.0); glVertex2d(.8,.8);
        glTexCoord2d(0.0,1.0); glVertex2d(-.8,.8);
        glEnd();
        
        glPopMatrix();
    }
    
    glutSwapBuffers();      //swaps the front and back buffers
}


void mouseMove (int x, int y)
{
    if (leftButtonClicked) {
        newMousePositionX = x;
        newMousePositionY = y;
        glutPostRedisplay();
    }
}


void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glOrtho (0, (GLfloat)w/(GLfloat)h, -1, 1, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            leftButtonClicked = true;
            currentMousePositionX = x;
            currentMousePositionY = y;

        }
        else
            leftButtonClicked = false;
    }
}


// Method to read the given SGY file and fill the matrix
void readFileToMatrix(char* filename)
{
    FILE *pFile = fopen(filename, "rb");
    
    if (pFile == NULL)
        perror("Failed to open file");
    else {
        // skip the headers
        fseek(pFile, 3600, SEEK_SET);
        
        mat = (char**)malloc(sizeof(char*)*traces);
        
        for (int i = 0; i < traces; i++) {
            mat[i] = (char *)malloc(sizeof(char) * 1750);
            fseek(pFile, 240, SEEK_CUR);
            fread(mat[i], 1, 1750, pFile);
        }
    }
    
    // close file reader
    fclose(pFile);

}


void init(void)
{
    currentMousePositionX = 0;
    currentMousePositionY = 0;
    newMousePositionX = 0;
    newMousePositionY = 0;
    originalTranslate = 0.6;
    
    leftButtonClicked = false;
    traces = 13483; // as defined in the task
    
    readFileToMatrix("/Users/tmn/Downloads/NVGT-88-06.sgy");
    
    glEnable( GL_TEXTURE_2D );
    
    textures = new GLuint[traces/1024 + 1];
    glGenTextures(traces/1024 + 1, textures);
}


int main(int argc, char * argv[])
{
    // create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1280, 800);
    glutCreateWindow("Mipmipmap");
    
    init();
    
    // draw and reshape
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    
    // interactions
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    
    glutMainLoop();
    
    delete textures;
    return 0;
}
