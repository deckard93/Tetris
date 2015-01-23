//===================== Input =====================




void keyboard(unsigned char key, int x, int y) 
{
	
	switch (key)
	{
		case 'q':
		    quitGame();
		    break;
		case 27:  //ESC
		    switch(gameState) 
		    {
			case PAUSED:
			    gameState = PLAYING;   
			    break;
			case PLAYING:
			    if(menuOption >= 0) paused[menuOption].setSelect(false);
			    menuOption= -1;
			    gameState = PAUSED;
			    break;
			default:
			    if(gameRunning) {
				if(menuOption >= 0) paused[menuOption].setSelect(false);
				menuOption= -1;
				gameState = PAUSED;
			    } else {
				if(menuOption >= 0) mainMenu[menuOption].setSelect(false);
				menuOption= -1;
				gameState = MAINMENU;
			    }
		    }
		    break;
		    
		
		    
		case 'r': 
		    if(gameState == PLAYING) 
		    {
			restart();
		    }
		    break;
		    
		case '\r': //ENTER is pressed
		    switch(gameState) {
			case MAINMENU:
			   
			    if(menuOption >= 0) mainMenu[menuOption].runAction();
			    else startGame();
			     
			    return;
			    
			case PAUSED:
			    
			    if(menuOption >= 0) paused[menuOption].runAction();
			    else startGame();
			    
			    return;
			    
			case PLAYING:
			    return;
			    
			default:
			    if(gameRunning) {
				if(menuOption >= 0 && menuOption < 5) paused[menuOption].setSelect(false);
				menuOption= -1;
				gameState = PAUSED;
			    } else {
				if(menuOption >= 0 && menuOption < 4) mainMenu[menuOption].setSelect(false);
				menuOption= -1;
				gameState = MAINMENU;
			    }
			
		    }
		    break;
		
		    
		case 'f': 
		    if(gameState == PLAYING) 
		    {
			toggleFullscreen();
		    }
		    break;
		case 's':
		    if(render != THREE_D) 
		    {
			toggleFPS();
		    }
		    break;
		case 't':
		    if(gameState == PLAYING) 
		    {
			toggleTextures();
		    }	
		    break;     
		case 'g':
		    if(gameState == PLAYING) 
		    {
			toggleGhost();
		    }
		    break; 
		   
		    
		
		case 'z': 
		    if(gameState == PLAYING) 
		    {
			holdPiece();
		    }
		    break;
		case 'x': 
		    if(gameState == PLAYING) 
		    {
			rotateRight();
		    }
		    break;
		case 'c': 
		    if(gameState == PLAYING) 
		    {
			rotateLeft();
		    }
		    break;
		    
		
		case ' ': 
		    if(gameState == PLAYING) 
		    {
			dropPiece();
		    }
		    break;
		    
		    
		case 'i': 
		    if(gameState == PLAYING) 
		    {
			setRenderASCII();
		    }
		    break;
		case 'o': 
		    if(gameState == PLAYING) 
		    {
			setRenderVector();
		    }
		    break;    
		case 'p': 
		    if(gameState == PLAYING) 
		    {
			setRender3D();
		    }
		    break;
		    
		    
		    
		    
		case '8':
		    if(gameState == PLAYING) 
		    {
			eyeY++;
		    }
		    break;
		case '2':
		    if(gameState == PLAYING) 
		    {
			eyeY--;
		    }
		    break;
		    
		case '4':
		    if(gameState == PLAYING) 
		    {
			eyeX--;
		    }
		    break;
		case '6':
		    if(gameState == PLAYING) 
		    {
			eyeX++;
		    }
		    break;
		    
		case '5':
		    if(gameState == PLAYING) 
		    {
			eyeZ++;
		    }
		    break;
		case '0':
		    if(gameState == PLAYING) 
		    {
			eyeZ--;
		    }
		    break;
		    
		    
		case '7':
		    if(gameState == PLAYING) 
		    {
			rotateZ--;
		    }
		    break;
		case '9':
		    if(gameState == PLAYING) 
		    {
			rotateZ++;
		    }
		    break;
		    
	}

	movePiece();
	
	glutPostRedisplay();
}

void special(int key, int, int) 
{ //keys such as arrow keys
	
    
	
	switch (key)
	{
	  
	    case GLUT_KEY_RIGHT: 
		if(gameState == PLAYING) 
		{
		    moveRight();
		}
		break;
		
	    case GLUT_KEY_LEFT:
		if(gameState == PLAYING) 
		{
		    moveLeft();
		}
		break;
		
	    case GLUT_KEY_DOWN: 
		
		switch(gameState) {
		    case PLAYING:
		    
			moveDown();
			break;
			
		    case PAUSED:
			
			paused[menuOption].setSelect(false);
			
			menuOption++;
		
			if(menuOption > 4) {
			    menuOption = 0;
			}   
			
			paused[menuOption].setSelect(true);
			
			break;
			
		    case MAINMENU:
			
			mainMenu[menuOption].setSelect(false);
		
			menuOption++;
		
			if(menuOption > 3) {
			    menuOption = 0;
			}   
			
			mainMenu[menuOption].setSelect(true);
			
			break;
		
		 
		    
		}
		break;
		
	    case GLUT_KEY_UP: 
		
		switch(gameState) {
		    case PLAYING:
		    
			rotateRight();
			break;
			
		   case PAUSED:
			
			paused[menuOption].setSelect(false);
			
			menuOption--;
			
			if(menuOption < 0) {
			    menuOption = 4;
			}   
			
			paused[menuOption].setSelect(true);
			break;
			
		    case MAINMENU:
			
			mainMenu[menuOption].setSelect(false);
			
			menuOption--;
			
			if(menuOption < 0) {
			    menuOption = 3;
			}   
			
			mainMenu[menuOption].setSelect(true);
			
			break;
		    
		}
		break;
		
	    case GLUT_KEY_HOME: 
		if( gameState == PLAYING) 
		{
		    holdPiece();
		}
		break;
		
		
	}
	if(gameState == PLAYING) {
	    movePiece();
	}
	glutPostRedisplay(); // force a redraw
	
}

void mouse_click(int button, int state, int x, int y) 
{
    
    
	if (button==GLUT_LEFT_BUTTON) {
	    
		//std::cerr << "\t left mouse button pressed!" << std::endl;
		
		if (state==GLUT_UP)
		{
			//std::cerr << "\t button released...click finished" << std::endl;
			
			 
	
			 switch(gameState) {
			    case MAINMENU:			    
				
				for(int i = 0; i < 4; i++) {
				    if(mainMenu[i].collision(cursorX, cursorY)) 
					mainMenu[i].runAction();
				}
				break;
			    case SETTINGS:
				for(int i = 0; i < 11; i++) {
				    if(radioButtons[i].collision(cursorX, cursorY)) 
					radioButtons[i].runAction();
				}
				break;
				
    			    case PAUSED:			    
				for(int i = 0; i < 5; i++) {
				    if(paused[i].collision(cursorX, cursorY)) 
					paused[i].runAction();
				}
				break;

			 }

		}
		

	} else if (button==GLUT_RIGHT_BUTTON) {
		std::cerr << "\t right mouse button pressed!" << std::endl;
		if (state==GLUT_UP) {
			std::cerr << "\t button released...click finished" << std::endl;

		}
	}
	
	glutPostRedisplay();
}

void mouse_motion(int x, int y) 
{
	y = glutGet(GLUT_WINDOW_HEIGHT) - y + 1;
    
	cursorX = x * WORLD_X / glutGet(GLUT_WINDOW_WIDTH);
	cursorY = y * WORLD_Y / glutGet(GLUT_WINDOW_HEIGHT);
	
	//std::cerr << "\t mouse is at (" << cursorX << ", " << cursorY << ")" << std::endl;
	
	 switch(gameState) {
	    case MAINMENU:			    
		
		for(int i = 0; i < 4; i++) {
		    if(mainMenu[i].collision(cursorX, cursorY)) 
			mainMenu[i].setSelect(true);
		    else 
			mainMenu[i].setSelect(false);
		}
		break;
	    case SETTINGS:
		break;
		
	    case PAUSED:			    
		for(int i = 0; i < 5; i++) {
		    if(paused[i].collision(cursorX, cursorY)) 
			paused[i].setSelect(true);
		    else 
			paused[i].setSelect(false);
		}
		break;

	    }
	
	
	
	glutPostRedisplay();
}