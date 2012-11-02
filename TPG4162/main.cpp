#include "main.h"

char** mat;

int windowHeight;
int windowWidth;
int traces;

bool leftButtonClicked;
int currentMousePositionX;
int currentMousePositionY;
int newMousePositionX;
int newMousePositionY;


float originalTranslate;


GLuint *texts;

int main(int argc, char * argv[])
{
    currentMousePositionX = 0;
    currentMousePositionY = 0;
    newMousePositionX = 0;
    newMousePositionY = 0;
    originalTranslate = 0.6;
    
    leftButtonClicked = false;
    
    
    traces = 13483; // as defined in the task
    
    // read data file into a matrix
    // readFileToMatrix("/Users/tmn/NVGT-88-06.sgy");
    readFileToMatrix("./NVGT-88-06.sgy");
    
    // create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1280, 800);
    glutCreateWindow("Mipmipmap");
    
    glEnable( GL_TEXTURE_2D );
    
    texts = new GLuint[traces/1024 + 1];
    glGenTextures(traces/1024 + 1, texts);

    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    
    // interactions
    glutKeyboardFunc(keyPressed);
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
            
    glutMainLoop();
    
    delete texts;
    return 0;
}

void setCurrentXPosition(int x) {
    currentMousePositionX = x;
}

void createTexture(bool wrap, int texture_num)
{
    // GLuint texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    
    char * texturedata = (char *)malloc(sizeof(char)*1024*1750);
    
    for (int x=0; x<1024; x++) {
        for (int y=0; y<1750; y++) {
            texturedata[y*1024+x] = (mat[(texture_num*1024)+x][y])+127;
        }
    }
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, wrap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, wrap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, 1024, 1024, GL_RED, GL_UNSIGNED_BYTE, texturedata);

    free(texturedata);
    
    // return texture;
}


void redraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
    double dMouse = (newMousePositionX - currentMousePositionX)/1000.0;
    setCurrentXPosition(newMousePositionX);
    // std::cout << "Current: " << currentMousePositionX << " - new: " << newMousePositionX << " - delta: " << dMouse << "\n";
    
    originalTranslate += dMouse;
    glTranslatef(originalTranslate, 0, 0);
    
    // std::cout << "test: " << originalTranslate << "\n";

    for (int i = 0; i < sizeof(texts); i++) {
        
        glBindTexture(GL_TEXTURE_2D, texts[i]);
        createTexture(true, i);
        
        glPushMatrix();
        glTranslated(i+(i*0.6)+originalTranslate, 0, 0);
        
        glBegin( GL_QUADS );
            glTexCoord2d(0.0,0.0); glVertex2d(-.8,-.5);
            glTexCoord2d(1.0,0.0); glVertex2d(.8,-.5);
            glTexCoord2d(1.0,1.0); glVertex2d(.8,.8);
            glTexCoord2d(0.0,1.0); glVertex2d(-.8,.8);
        glEnd();
        
        glPopMatrix();
    }
    
    glPopMatrix();
    
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


void keyPressed (unsigned char key, int x, int y)
{
    switch (key) {
        case 'w':
            std::cout << "U PRESSED THE WWWW";
            break;
        default:
            std::cout << "asdf";
            redraw();
            break;
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