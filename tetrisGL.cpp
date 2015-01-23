//=========== Includes ===========
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <sstream> 

#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <png.h>

#include <chrono>
#include <ctime>

#include <GL/glut.h>


//=========== Declarations ===========
class Piece;
class LinkedNode;
int png_load(const char* file_name, 
		     int* width, 
			 int* height, 
			 char** image_data_ptr);
unsigned int make_bitmap_text();
Piece randomPiece();
int draw_center_text(const char* text);
int** allocateArray(int height, int width);
void draw_Border(int d_X, int d_Y, int size_X, int size_Y);
void draw_Triangle(int d_X, int d_Y, int size_X, int size_Y, int orientation);
void freeArray(int** p, int height, int width);
void draw_bitmap_text(const char* text);
void draw_stroke_text(const char* text);
void tetris();
void newPiece();
void movePiece();
void resetTempBoard();
void draw_Ghost_Block();
void draw_square(char c);
void holdPiece();
void cleanup();
void quitGame();
void toggleFullscreen();
void dropPiece();
void calculate_Ghost();
void updateBoard();
void color_Me(char c);
void toggleFPS();
void draw_filled_square();
void toggleTextures();
void initGL();
void restart();
bool collision();
void toggleGhost();
void setRenderASCII();
void setRenderVector();
void setRender3D();
void draw3DMain();
void startGame();
void howTo();
void settingsClick();
void restart();
void incrementEndLevel();
void incrementStartLevel();
void decrementEndLevel();
void decrementStartLevel();
void resume();
void init3D();
void rotateRight();
void rotateLeft();
void moveDown();
void moveLeft();
void moveRight();


//=========== Shorthands ===========
using namespace std;

typedef chrono::high_resolution_clock Clock;
typedef chrono::milliseconds milliseconds;


//=========== Defines ===========
#define BOARD_WIDTH 	10
#define BOARD_HEIGHT 	24

#define INVISIBLE 4

#define SLEEP_TIME 500000 

#define ASCII 	100
#define VECTOR 	200
#define THREE_D 300

#define MAINMENU 1000 
#define HOWTO    2000
#define SETTINGS 3000
#define PLAYING  4000
#define PAUSED   5000
#define GAMEOVER 6000
#define YOUWIN	 7000




//=========== Classes ===========
class LinkedNode 
{
private:
    LinkedNode* n;
    int* l;
    
public:
    LinkedNode* next() { return n; };
    int*        line() { return l; };
    
    void setNext(LinkedNode* next) { n = next; };
    void setLine(int * line)       { l = line; }
    
    
};

class Piece 
{
    
private:
    int h;
    int w;
    int** s;
    char i;
    unsigned int t; // texture handle
    
public:    
    void init(int** s_in,int h_in,int w_in, char i_in, unsigned int t_in) {
	s = s_in;
	w = w_in;
	h = h_in;
	i = i_in;
	t = t_in;
    };
    
    void  setHeight	(int h_in  ) { h = h_in;  };
    void  setWidth 	(int w_in  ) { w = w_in;  };
    void  setIcon  	(char i_in ) { i = i_in;  };
    void  setShape 	(int** s_in) { s = s_in;  };
    
    int   height() { return h;  };
    int   width()  { return w;  };
    int   icon()   { return i;  };
    int   texture(){ return t;  };
    int** shape()  { return s;  }
    
} tetri_O, tetri_L, tetri_J, tetri_T, tetri_I, tetri_S, tetri_Z;

class MenuItem {

private:
    int x;
    int y;
    
    int h;
    int w;
    
    char* name;
    
    bool s;
    
    void (*action)();
    
public:	
    init(char* name_in) {
	name = name_in;
	
	
	for (size_t i=0;i<strlen(name_in);i++) {
	    w += glutStrokeWidth(GLUT_STROKE_ROMAN, name_in[i]);
	}	
	
	h = 60;
	
	s = false;

    }
    
public: //class functions
    bool collision(int check_x, int check_y ) {
	if(check_x > x - w/4 && check_x < x + w/4 ) {
	    if(check_y > y && check_y < y + h) {
		return true;
	    }
	}
	return false;
    }
    
    void runAction() {	action(); }
    
public:	//getters
    int height() { return h; };
    int width()  { return w; };
    
    int posX() { return x; };
    int posY() { return y; };
    
    bool selected() { return s; }
    
    char* text() { return name; };
    
public:	//setters
    void setHeight(int h_in) { h = h_in; };
    void setWidth (int w_in) { w = w_in; };
    
    void setX (int x_in) { x = x_in; };
    void setY (int y_in) { y = y_in; };
    
    void setSelect(bool s_in) { s = s_in; };
    
    void setAction( void (*a_in)(void) ) { action = a_in; };
    
    
    
};

//=========== Globals ===========
LinkedNode* board;
char temp[BOARD_HEIGHT][BOARD_WIDTH];

int WORLD_X;
int WORLD_Y;

int WINDOW_X;
int WINDOW_Y;

int gameState;

int speed[21];
int linesCleared;
int score;
int level;

int startLevel;
int endLevel;

int pieceX;
int pieceY;

int cursorX;
int cursorY;

int graphics;


int frames;
int fps;
int FPSdisplay;

bool fullscreen;
bool texture;
bool ghost;
bool swapped;
bool holdInit;
bool FPS;
bool gameRunning;

int menuOption;

long int elapsed;

int blockSize;

int aux_Box_S;

unsigned int howto; 
unsigned int border;

int eyeX;
int eyeY;
int eyeZ;

int rotateZ;

Clock::time_point start;
Clock::time_point lastMove;

MenuItem mainMenu[4];
MenuItem paused[5]; 
MenuItem settings[8];
MenuItem radioButtons[11];
MenuItem render[4];

MenuItem* currentMenu;


Piece current;
Piece hold;
Piece following;


#include "util.h"
#include "input.h"
#include "control.h"
#include "draw.h"
#include "game.h"




//===================== Callbacks =====================

void display() 
{
    glLoadIdentity();                 // Reset the model-view matrix
    
    frames++;
    
    glClear(GL_COLOR_BUFFER_BIT);	//clears to current background colour
    
    initGL();
    switch(gameState) {
	
	case MAINMENU:
	    drawMenu();
	    break;
	case HOWTO:
	    drawHowTo();
	    break;  
	case SETTINGS:
	    drawSettings();
	    break;
	
	case PLAYING:
	    switch(graphics) {
		case VECTOR:    
		    draw_Score();
		    draw_Level();
	    
		    draw_Next();
		    draw_Hold();
		    
		    draw_Board();
		    
		     if (FPS) displayFPS();
		    break;
		case ASCII:
			
		    draw_Score();
		    draw_Level();
		    
		    draw_ASCII_Next();
		    draw_ASCII_Hold();
		    
		    draw_ASCII_Board();
		    
		    if (FPS) displayFPS();
		    break;
		case THREE_D:
		    draw3DMain();
		    break;
	    }
	    break;

	case YOUWIN:
	    drawEnd("You Win!");
	    break;
	case GAMEOVER:
	    drawEnd("Game Over!");
	    break;
	case PAUSED:
	    drawPause();
	    break;
	    
	    
	default:
	    drawMenu();
	    break;
		  
    }
    
   
      
    
    glutSwapBuffers(); 
}

void idle() 
{

    Clock::time_point now = Clock::now();
    
    milliseconds ms = chrono::duration_cast<milliseconds>(now - start);
    
    elapsed = ms.count();
    
    if( elapsed >= FPSdisplay) {
	    //cout<<frames/elapsed<<"\n";
	    fps = frames;
	    frames = 0;
	    start = Clock::now();
	    glutPostRedisplay();
	    return;
    }
    
    
    
    if(gameState == PLAYING) {
	ms = chrono::duration_cast<milliseconds>(now - lastMove);
	int elapsed = ms.count();
	    
	if(elapsed > speed[level]) {
	    lastMove = Clock::now();
	    
	    pieceY++;
	    movePiece();
	    
	    glutPostRedisplay();
	    return;
		
	}
	
	glutPostRedisplay();
    }
    
    
}

void reshape(int w, int h)
{
	/*
	// save the new window dimensions when window is resized
	WINDOW_X = w;
	WINDOW_Y = h;

  	//glViewport(0, 0, w, h);

  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	gluOrtho2D(0, w, 0, h);
  	glutPostRedisplay();
	*/
	
	/*
	 // Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);
	
	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
	*/
	
	
}

//===================== Init =====================
void initGL() 
{
    
    // select viewing transformation matrix to modify
    glMatrixMode(GL_PROJECTION); 

    // set identity on matrix
    glLoadIdentity();

    
    // specify bottom-left and top-right corners
    // of window in world coordinates
    // takes LEFT, RIGHT, BOTTOM, TOP
    gluOrtho2D(0, WORLD_X, 0, WORLD_Y);

    // set background colour and transparency
    // takes RGBA values
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    
   
    glClearDepth(1.0f);                   // Set background depth to farthest
    glDisable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
    

    
}

void init3D()
{
	// set orthographic viewing

	glEnable(GL_DEPTH_TEST);
    
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();

	// specify a projection with 
	//    this view volume, centred on origin 
	// takes LEFT, RIGHT, BOTTOM, TOP, NEAR and FAR
	//glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
	
	
	// for perspective projection use the GLU helper
	// take FOV, ASPECT RATIO, NEAR, FAR 
	gluPerspective(60.0, 1.6f, 1.0, 60.0);
	



	// draw stuff as wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
}

void textureInit() 
{
    howto = load_and_bind_texture("howto.png");
    border = load_and_bind_texture("square/gray.png");
    
}

void pieceInit() 
{
    int height;
    int width;    
    
	height = 2;
	width = 2;
	
	int** shape_O = allocateArray(height, width);
	
	
	shape_O[0][0] = 1; shape_O[0][1] = 1;
	shape_O[1][0] = 1; shape_O[1][1] = 1;
		

    tetri_O.init(shape_O, height, width, 'O', load_and_bind_texture("square/yellow.png"));
    
		
	height = 4;
	width = 4;
	
	int** shape_I = allocateArray(height, width);
	
	shape_I[0][0] = 0; shape_I[0][1] = 1; shape_I[0][2] = 0;  shape_I[0][3] = 0;
	shape_I[1][0] = 0; shape_I[1][1] = 1; shape_I[1][2] = 0;  shape_I[1][3] = 0;
	shape_I[2][0] = 0; shape_I[2][1] = 1; shape_I[2][2] = 0;  shape_I[2][3] = 0;
	shape_I[3][0] = 0; shape_I[3][1] = 1; shape_I[3][2] = 0;  shape_I[3][3] = 0;
    
    tetri_I.init(shape_I, height, width, 'I', load_and_bind_texture("square/lightblue.png"));
    
    
	height = 3;
	width = 3;
	
	int** shape_L = allocateArray(height, width);
	
	shape_L[0][0] = 0; shape_L[0][1] = 1; shape_L[0][2] = 0;
	shape_L[1][0] = 0; shape_L[1][1] = 1; shape_L[1][2] = 0;
	shape_L[2][0] = 0; shape_L[2][1] = 1; shape_L[2][2] = 1;
	
    
    tetri_L.init(shape_L, height, width, 'L', load_and_bind_texture("square/blue.png"));
    
    
	height = 3;
	width = 3;
	
	int** shape_J = allocateArray(height, width);
	
	shape_J[0][0] = 0; shape_J[0][1] = 1; shape_J[0][2] = 0;
	shape_J[1][0] = 0; shape_J[1][1] = 1; shape_J[1][2] = 0;
	shape_J[2][0] = 1; shape_J[2][1] = 1; shape_J[2][2] = 0;
	
    
    tetri_J.init(shape_J, height, width, 'J', load_and_bind_texture("square/orange.png"));
        
    	height = 3;
	width = 3;
	
	int** shape_T = allocateArray(height, width);
	
	shape_T[0][0] = 0; shape_T[0][1] = 1; shape_T[0][2] = 0; 
	shape_T[1][0] = 1; shape_T[1][1] = 1; shape_T[1][2] = 1;
	shape_T[2][0] = 0; shape_T[2][1] = 0; shape_T[2][2] = 0;		


    tetri_T.init(shape_T, height, width, 'T', load_and_bind_texture("square/purple.png"));
      
    
    	height = 3;
	width = 3;
	
	int** shape_Z = allocateArray(height, width);
	
	shape_Z[0][0] = 1; shape_Z[0][1] = 1; shape_Z[0][2] = 0;
	shape_Z[1][0] = 0; shape_Z[1][1] = 1; shape_Z[1][2] = 1;

    
    tetri_Z.init(shape_Z, height, width, 'Z', load_and_bind_texture("square/red.png"));
    
    
    	height = 3;
	width = 3;
	
	int** shape_S = allocateArray(height, width);
	
	shape_S[0][0] = 0; shape_S[0][1] = 0; shape_S[0][2] = 0;
	shape_S[1][0] = 0; shape_S[1][1] = 1; shape_S[1][2] = 1;
	shape_S[2][0] = 1; shape_S[2][1] = 1; shape_S[2][2] = 0;
    
    tetri_S.init(shape_S, height, width, 'S', load_and_bind_texture("square/green.png"));
    
}

void menuInit() 
{
    
    mainMenu[0].init(" Start Game ");
    mainMenu[0].setAction(startGame);
    
    mainMenu[1].init(" How to Play ");
    mainMenu[1].setAction(howTo);
    
    mainMenu[2].init(" Settings ");
    mainMenu[2].setAction(settingsClick);
    
    mainMenu[3].init(" Exit ");
    mainMenu[3].setAction(quitGame);
    
    int x = WORLD_X / 2;
    int y = WORLD_Y / 2;
    
    for(int i = 0; i < 4; i++) {
	mainMenu[i].setX(x);
	mainMenu[i].setY(y - 60 * i);
	
    }
    
    
    paused[0].init(" Resume ");
    paused[0].setAction(resume);
    
    paused[1].init(" Restart ");
    paused[1].setAction(restart);
    
    paused[2].init(" How to Play ");
    paused[2].setAction(howTo);
    
    paused[3].init(" Settings ");
    paused[3].setAction(settingsClick);
    
    paused[4].init(" Exit Program ");
    paused[4].setAction(quitGame);
    
    x = WORLD_X / 2;
    y = WORLD_Y / 2;
    
    for(int i = 0; i < 5; i++) {
	paused[i].setX(x);
	paused[i].setY(y - 60 * i);
	
    }
    
    
    
    
    settings[0].init(" Render ");
    //settings[1].init("  ");
    
    settings[1].init(" Textures ");
    settings[2].init(" Fullscreen ");
    settings[3].init(" FPS Display ");
   
    settings[4].init(" Ghost Piece ");
    settings[5].init(" Start Level ");
    settings[6].init(" End Level ");
    settings[7].init("  "); //Lookahead
    
    
    
    
    x = WORLD_X / 3;
    y = WORLD_Y - WORLD_Y/10;
    
    settings[0].setX(x);
    settings[0].setY(y);
    
     for(int i = 1; i < 4; i++) {
	settings[i].setX(x);
	settings[i].setY(y - 60 * (i + 3));
	
    }
    
    y -= 200 + 3 * 60;
    
    for(int i = 4; i < 8; i++) {
	settings[i].setX(x);
	settings[i].setY(y - 60 * i);
	
    }
    
    
    for(int i = 0; i < 11; i++ ){
	radioButtons[i].setWidth(80);
	radioButtons[i].setHeight(40);
    }
    

    radioButtons[0].setAction(setRenderASCII);
    radioButtons[1].setAction(setRenderVector);
    radioButtons[2].setAction(setRender3D);
    radioButtons[3].setAction(toggleTextures);
    radioButtons[4].setAction(toggleFullscreen);
    radioButtons[5].setAction(toggleFPS);
    radioButtons[6].setAction(toggleGhost);
    radioButtons[7].setAction(incrementStartLevel);
    radioButtons[8].setAction(incrementEndLevel);
    radioButtons[9].setAction(decrementStartLevel);
    radioButtons[10].setAction(decrementEndLevel);
    
    
    
    
    
    x = (WORLD_X * 2) / 3;
    y = WORLD_Y - (WORLD_Y/10);
    
    for(int i = 0; i < 3; i++) {
	radioButtons[i].setX(x);
	radioButtons[i].setY(y - 60 * i);
    }
    
    y -= 60;
    
    for(int i = 3; i < 6; i++) {
	radioButtons[i].setX(x);
	radioButtons[i].setY(y - 60 * i);
    }
    
    
    y -=  200;
    
    for(int i = 6; i < 9; i++) {
	radioButtons[i].setX(x);
	radioButtons[i].setY(y - 60 * i);
	
    }
    
    for(int i = 9; i < 11; i++) {
	radioButtons[i].setX(x + 60);
	radioButtons[i].setY(y - 60 * (i - 2));
	
    }
    
    
    
    
    render[0].init(" ASCII ");
    render[1].init(" Vector ");
    render[2].init(" 3D ");
    
    
    
    x = WORLD_X / 2;
    y = WORLD_Y - WORLD_Y / 10;
    
    
    for(int i = 0; i < 3; i++) {
	render[i].setX(x);
	render[i].setY(y - 60 * i);
    }
    
}

void speedInit() 
{
    speed[0] = 53 / 60.0 * 1000;
    speed[1] = 49 / 60.0 * 1000;
    speed[2] = 45 / 60.0 * 1000;
    speed[3] = 41 / 60.0 * 1000;
    speed[4] = 37 / 60.0 * 1000;
    speed[5] = 33 / 60.0 * 1000;
    speed[6] = 28 / 60.0 * 1000;
    speed[7] = 22 / 60.0 * 1000;
    speed[8] = 17 / 60.0 * 1000;
    speed[9] = 11 / 60.0 * 1000;
    speed[10] = 10 / 60.0 * 1000;
    speed[11] = 9 / 60.0 * 1000;
    speed[12] = 8 / 60.0 * 1000;
    speed[13] = 7 / 60.0 * 1000;
    speed[14] = 6 / 60.0 * 1000;
    speed[15] = 6 / 60.0 * 1000;
    speed[16] = 5 / 60.0 * 1000;
    speed[17] = 5 / 60.0 * 1000;
    speed[18] = 4 / 60.0 * 1000;
    speed[19] = 4 / 60.0 * 1000;
    speed[20] = 3 / 60.0 * 1000;
    
}

void boardInit() 
{
    LinkedNode* node = new LinkedNode;
    board = node;
    
    for(int i = 0; i < BOARD_HEIGHT; i++) {
	
	int* line = (int*) malloc(BOARD_WIDTH * sizeof(int));
	
	for(int j = 0; j < BOARD_WIDTH; j++) {
	    line[j] = ' ';
	    temp[i][j] = ' ';
	}
	
	node->setLine(line);
	node->setNext(new LinkedNode);
	
	node = node->next();
	
    }   
}

void init() 
{
    gameState = MAINMENU;
    graphics = THREE_D;  
  
    
    startLevel = 0;
    endLevel = 20;
    
    WORLD_X = 1920;
    WORLD_Y = 1080;


    WINDOW_X = 1280;
    WINDOW_Y = 720;
    
    initGL();
    
    
    frames = 0;
    fps = 0;
    FPSdisplay = 1000;

    fullscreen = false;
    texture = true;
    ghost = true;

    
    FPS = false;
    holdInit = false;
    
    gameRunning = false;
    
    blockSize = WORLD_X / 5 / 10;

    aux_Box_S = 5 * blockSize;
    
    
    level = startLevel;
    
    eyeX = 0;
    eyeY = 12;
    eyeZ = 28;

    rotateZ = 0;
    
    
    linesCleared = 0;
    
    menuOption = -1;
    
    lastMove = Clock::now();
    
    srand (time(NULL));
    
    following = randomPiece();
    
    textureInit();
    pieceInit();
    menuInit();
    speedInit();
    boardInit();
    
    
    newPiece();
    
    
    //SOMEHOW THIS WORKS
    restart();
    gameState = MAINMENU;
}






//=================== Main ===================
int main (int argc, char* argv[]) 
{
  
    //initialise glut
    glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); // flags bitwise OR'd together
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH); // flags bitwise OR'd together
     
   
    
    // display window size is in pixels on screen
    glutInitWindowSize(1280, 720); 
    glutInitWindowPosition(50, 50); 
    glutCreateWindow("I am glut");
    
    //callback functions
    glutDisplayFunc(display);
    //glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
    glutKeyboardFunc(keyboard); 
    glutSpecialFunc(special);
    
    glutMouseFunc(mouse_click); 
    glutPassiveMotionFunc(mouse_motion); 
    
    //initialise program
    init();
    
    //enter infinite loop
    glutMainLoop();
    
    return 0;
  
}
