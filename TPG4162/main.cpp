//
//  main.cpp
//  TPG4162
//
//  Created by Tri M. Nguyen on 10/21/12.
//
//

#include "main.h"

char** mat;


int main(int argc, char * argv[])
{
    // read data file into a matrix
    readFileToMatrix("/Volumes/Macintosh HD/Dropbox/TPG4162-2/NVGT-88-06.sgy");
    
    char * texturedata = (char *)malloc(sizeof(char)*1024*1024);

    
    for (int x=0; x<1024; x++)
    {
        for (int y=0; y<1024; y++)
        {
            texturedata[y*1024+x] = (char)((float)x/1024.0f*255.0f);
        }
    }
    
    
     
    // GLuint test;
    
    // print the data from the matrix
    // for (int i = 0; i < 13483; i++) {
        for (int j = 0; j < 1750; j++) {
            printf("%03d ", mat[0][j]);
        }
        
    // }
    
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("My first GLUT program");
    
    
    
    glEnable( GL_TEXTURE_2D );
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 1024, 1024, 0, GL_RED, GL_UNSIGNED_BYTE, texturedata);
   
    // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    
    // when texture area is large, bilinear filter the first mipmap
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    bool wrap = true;
    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
    
    
    // glEnableClientState(<#GLenum array#>)
    
    glutDisplayFunc(redraw);
    
    glutReshapeWindow( 800, 600);
    glutPostRedisplay();
    
    
    glutMainLoop();
    
    free(texturedata);
    
    return 0;
}

static void redraw(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin( GL_QUADS );
    glTexCoord2d(0.0,0.0); glVertex2d(0.0,0.0);
    glTexCoord2d(1.0,0.0); glVertex2d(1.0,0.0);
    glTexCoord2d(1.0,1.0); glVertex2d(1.0,1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(0.0,1.0);
    glEnd();
    
    glutSwapBuffers();      //swaps the front and back buffers
}


// Method to read the given SGY file and fill the matrix
static void readFileToMatrix(char* filename)
{
    FILE *pFile = fopen(filename, "rb");
    
    if (pFile == NULL) {
        perror("Failed to open file");
    }
    else {
        // skip the headers
        fseek(pFile, 3600, SEEK_SET);
        
        
        mat = (char**)malloc(sizeof(char*)*13483);
        
        for (int i = 0; i < 13483; i++) {
            mat[i] = (char *)malloc(sizeof(char) * 1750);
            fseek(pFile, 240, SEEK_CUR);
            fread(mat[i], 1, 1750, pFile);
        }
    }
    
    // close file reader
    fclose(pFile);
}

