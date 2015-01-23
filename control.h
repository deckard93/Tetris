 
//===================== Control =====================
void restart() 
{
	/* Restarts the game by resetting all
	 * variables to their default values
	 * can be called by clicking a menu item
	 * or by a keystroke
	 */
    
    level = startLevel;
    score = 0;
    
    linesCleared = 0;
    
    holdInit = false;    
    
    LinkedNode* node = board;

    
     
   for(int i = 0; i < BOARD_HEIGHT; i++) {
	for(int j = 0; j < BOARD_WIDTH; j++) {
	   
		temp[i][j] = ' ';
		node->line()[j] = ' ';

	}
	
	node = node->next();
    }   
    
    current = randomPiece();
    
    following = randomPiece();
    
    pieceY = 0;
    pieceX = BOARD_WIDTH / 2;
    
    swapped = false;
    
    gameState = PLAYING;
}

void resume() 
{
	/*Resumes game by changing the
	 *State to PLAYING, thi siwll be recognized
	 */
    gameState = PLAYING;
}

void toggleTextures() 
{    
	/* Checks if textures are activated
	 * If they are then disable them 
	 * Otherwise activate them
	 * Only applicable to 2D view
	 */
    if(!texture){
	
	texture = true;
    } else if(texture){
	texture = false;
	
    }       
}

void toggleFPS() 
{   
	/* FPS variable used to determine if FPS will be displayed
	 * Changes state to true if false and viceversa
	 */
    if(!FPS){
	FPS = true;
    } else if(FPS){
	FPS = false;
    }       
}

void toggleFullscreen() 
{  
	/*
	 */
    if(!fullscreen){
	glutFullScreen();
	fullscreen = true;

    } else {
	glutReshapeWindow(WINDOW_X, WINDOW_Y);
	glutPositionWindow(100,100);
	fullscreen = false;
    }       
}

void toggleGhost() 
{
 
    if(ghost) {
	ghost = false;
    } else {
	ghost = true;
    }
    
}

void setRenderASCII() 
{
     graphics = ASCII;
}

void setRenderVector() 
{
     graphics = VECTOR;
}

void setRender3D() 
{
     graphics = THREE_D;
}

void startGame() 
{
    restart();
    gameState = PLAYING;
    gameRunning = true;
}

void howTo() 
{
    gameState = HOWTO;
}

void quitGame()
{
   //are you sure?
   //glutDestroyWindow ( Win.id );
   cleanup();
   exit(0); // quit! 
}

void settingsClick() 
{
    gameState = SETTINGS;
}

void incrementEndLevel() 
{
    if(endLevel + 1 <= 20) {
	endLevel++;
    }
}

void decrementEndLevel() 
{
    if(endLevel - 1 >= 0) {
	if(endLevel - 1 > startLevel) {
	    endLevel--;
	}
    }
}

void incrementStartLevel() 
{
    if(startLevel + 1 <= 20) {
	if(startLevel + 1 < endLevel) {
	    startLevel++;
	}
    }
}

void decrementStartLevel() 
{
    if(startLevel - 1 >= 0) {
	startLevel--;
	
    }
}