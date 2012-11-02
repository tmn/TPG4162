#include "main.h"

char** mat;

int posx;
int posy;




void mouseMove (int x, int y)
{
    std::cout << "asdf";
}

void reshape(int w, int h)
{
    
}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        std::cout << "LEFT BUTTON CLICKD " << x;
    }
}


GLuint createTexture(bool wrap)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    char * texturedata = (char *)malloc(sizeof(char)*1024*1024);
    
    for (int x=0; x<1024; x++) {
        for (int y=0; y<1024; y++) {
            texturedata[y*1024+x] = (mat[x][y])+127;
        }
    }
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 1024, 1024, GL_RED, GL_UNSIGNED_BYTE, texturedata);
    
    free(texturedata);
    
    return texture;
}


static void redraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin( GL_QUADS );
    
        glTexCoord2d(0.0,0.0);
        glVertex2d(0.0,0.0);
    
        glTexCoord2d(1.0,0.0);
        glVertex2d(1.0,0.0);
    
        glTexCoord2d(1.0,1.0);
        glVertex2d(1.0,1.0);
    
        glTexCoord2d(0.0,1.0);
        glVertex2d(0.0,1.0);
    
    glEnd();
    
    glutSwapBuffers();      //swaps the front and back buffers
}


void keyPressed (unsigned char key, int x, int y)
{
    switch (key) {
        case 'w':
            std::cout << "U PRESSED THE WWWW";
            break;
        default:
            std::cout << "asdf";
            break;
    }
}


// Method to read the given SGY file and fill the matrix
static void readFileToMatrix(char* filename)
{
    FILE *pFile = fopen(filename, "rb");
    
    if (pFile == NULL)
        perror("Failed to open file");
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



int main(int argc, char * argv[])
{
    posx = 0;
    posy = 0;
    
    // read data file into a matrix
    readFileToMatrix("/Users/tmn/Dropbox/TPG4162-2/NVGT-88-06.sgy");
    
    // create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("MipMip");
    
    glEnable( GL_TEXTURE_2D );
    
    // call drawings woop
    createTexture(true);
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    
    glutReshapeWindow( 1280, 800);
    glutPostRedisplay();
    
    glutKeyboardFunc(keyPressed);
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    // glOrtho(<#GLdouble left#>, <#GLdouble right#>, <#GLdouble bottom#>, <#GLdouble top#>, <#GLdouble zNear#>, <#GLdouble zFar#>)
    
    glutMainLoop();
    
    return 0;
}
