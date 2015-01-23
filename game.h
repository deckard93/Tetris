//=========== Game Functions ===========



void updateTemp()
{
    
    for(int i = 0; i < current.height(); i++) {
	for(int j = 0; j < current.width(); j++) {
	    //sanity check
	    if(
		pieceY + i >= 0 &&
		pieceY + i < BOARD_HEIGHT &&
		pieceX + j >= 0 && 
		pieceX + j < BOARD_WIDTH
	    ) {
		if(current.shape()[i][j] == 1) {
		    temp[pieceY + i][pieceX + j] = current.icon();
		}
	    } 
	}
    }
}

void movePiece()
{
    resetTempBoard();
    
    if(collision()) {	//place the piece and generate a new one
	pieceY--;
	
	if(pieceY < 4 ){
	    gameState = GAMEOVER;
	    gameRunning = false;
	    return;
	}
	
	updateBoard();
	updateTemp();
	
	newPiece();
	
    } else {  //update the draw array
    
	updateTemp();
    }
    
    if(ghost) calculate_Ghost();
}

void resetTempBoard()
{
    
   LinkedNode* node = board;
  
   for(int i = 0; i < BOARD_HEIGHT; i++) {
	for(int j = 0; j < BOARD_WIDTH; j++) {
	   
		temp[i][j] = node->line()[j];

	}
	
	node = node->next();
    }   
       
}

void newPiece()
{
    
    current = following;
    
    following = randomPiece();
  
    pieceY = 0;
    pieceX = BOARD_WIDTH / 2 - current.width();
        
    swapped = false;
}

void rotateRight()
{
    
    int w = current.width();
    int h = current.height();
    
    
    int** shape_r = ( int** ) malloc( w *sizeof( int* ));
    for ( int i = 0; i < w; i++ ) {
	shape_r[i] = ( int* ) malloc( h * sizeof(int) );	
    }
    
    for(int i = 0; i < h; i++) {
	for(int j = 0; j < w; j++) {
	    shape_r[j][i] = current.shape()[i][j];
	}
    }
    
    /*
    int aux;
    for(int i = 0; i < h; i++) {
	aux = shape_r[0][i];
	shape_r[0][i] = shape_r[w-1][i];
	shape_r[w-1][i] = aux;
    }
    */
    
    int aux;
    for(int i = 0; i < w; i++) {
	aux = shape_r[i][0];
	shape_r[i][0] = shape_r[i][h -1];
	shape_r[i][h - 1] = aux;
    }
    

    
    
    //freeArray(current.shape(), h, w);
    
    current.setShape(shape_r);
    current.setHeight(w);
    current.setWidth(h);
    
   
   if(collision()) {
	
	
	
	for(int y = 0; y > -3; y--) {
	    for(int x = -2; x < 3; x++) {
		pieceY += y;
		pieceX += x;
		
		if(!collision()) {
		    return;
		} 
		
		pieceY -= y;
		pieceX -= x;
	    }
	}	    	
	
	for(int y = 1; y < 3; y++) {
	    for(int x = -2; x < 3; x++) {
		pieceY += y;
		pieceX += x;
		
		if(!collision()) {
		    return;
		} 
	    
		pieceY -= y;
		pieceX -= x;
	    }
	}
    }
    
    while(collision()) {
	pieceY--;   
   }
    
}

void rotateLeft()
{
    
    int w = current.width();
    int h = current.height();
    
    
    int** shape_r = ( int** ) malloc( w *sizeof( int* ));
    for ( int i = 0; i < w; i++ ) {
	shape_r[i] = ( int* ) malloc( h * sizeof(int) );	
    }
    
    for(int i = 0; i < h; i++) {
	for(int j = 0; j < w; j++) {
	    shape_r[j][i] = current.shape()[i][j];
	}
    }
    
    
   
    int aux;
    for(int i = 0; i < h; i++) {
	aux = shape_r[0][i];
	shape_r[0][i] = shape_r[w-1][i];
	shape_r[w-1][i] = aux;
    }
    
    
    //freeArray(current.shape(), h, w);
    
    current.setShape(shape_r);
    current.setHeight(w);
    current.setWidth(h);
    
    
   if(collision()) {
	
	for(int x = -2; x < 3; x++) {
	    for(int y = -2; y < 3; y++) {
		pieceY += y;
		pieceX += x;
		
		if(!collision()) {
		    return;
		} 
		
		pieceY -= y;
		pieceX -= x;
	    }
	}	    	
    }
   
   while(collision()) {
	pieceY--;   
   }
    
}

void holdPiece()
{
    if(swapped) {
	return;
    } else { 
	swapped = true;
	if (holdInit) {
	    Piece aux;
	    aux = hold;
	    hold = current;
	    current = aux;
	    
	    pieceY = 0 - current.height();
	    pieceX = BOARD_WIDTH / 2;

	} else {
	    
	    hold = current;
	    
	    newPiece();
	    
	    holdInit = true;
	    swapped = true;
	}
    }
    
}

Piece randomPiece() 
{
      /* generate secret number between 1 and 10: */
    int r = rand() % 7 + 1;
    
     switch(r) {
	
	case 1:
	   return tetri_I;
	case 2:
	    return tetri_L;
	case 3:
	    return tetri_J;    
	case 4:
	    return tetri_O;
	case 5:
	    return tetri_S;	    
	case 6:
	    return tetri_Z;
	    break;
	case 7:
	    return tetri_T;
	    
    }
}

void calculate_Ghost() 
{
    //does the piece not fit on the board
    
    //did the piece touch another piece
    
    int ghostY = pieceY;
    
    LinkedNode* node = board;
		    
    for(int i = 0; i < ghostY; i++) {	
	node = node->next();
    } 
		    
    do {
	ghostY++;
	
	//check for collisions
	bool collision = false;
	LinkedNode* node = board;
	
	for(int i = 0; i < ghostY; i++) {	
	    node = node->next();
	}   
	
	int diff = 0;
	
	if(ghostY < 0) {
	    diff = ghostY;
	}
	    
	
	for(int i = 0; i < current.height() + diff; i++) {
	    for(int j = 0; j < current.width(); j++) {
		if(
		    ghostY + i >= 0 &&
		    pieceX + j >= 0 && 
		    pieceX + j < BOARD_WIDTH
		) {
		    if(current.shape()[i][j] == 1 && node->line()[pieceX + j] != ' ') {
			collision = true;
		    }
		    
		    if(ghostY + i >= BOARD_HEIGHT && current.shape()[i][j] == 1) {
			collision = true;
		    }
		} 	
	    }
	    
	    node = node->next();
	}
	
	if(collision) {
	    ghostY--;
	    
	    
	    for(int i = 0; i < current.height(); i++) {
		for(int j = 0; j < current.width(); j++) {
		    if(
			ghostY + i >= 0 &&
			ghostY + i < BOARD_HEIGHT &&
			pieceX + j >= 0 && 
			pieceX + j < BOARD_WIDTH
		    ) {
			if(current.shape()[i][j] == 1) {
			    if(temp[ghostY + i][pieceX + j] != current.icon()) temp[ghostY + i][pieceX + j] = 'G';
			}
		    } 
		}
	    }
	    
	    return;
	}
	
			    
    } while (ghostY != 0 - current.height());
				
}

bool collision()
{
    LinkedNode* node = board;
    
    for(int i = 0; i < pieceY; i++) {	
	node = node->next();
    }   
    
    int diff = 0;
    
    if(pieceY < 0) {
	diff = pieceY;
    }
	    
    for(int i = 0; i < current.height() + diff; i++) {
	for(int j = 0; j < current.width(); j++) {
	    
	    if(current.shape()[i][j] == 1) {
		
		if(pieceY + i >= BOARD_HEIGHT) {
		    return true;
		}
		
		if (pieceX + j < 0 || pieceX + j >= BOARD_WIDTH) {
		  
		    return true;
		}

		
		if(pieceY + i >= 0 && node->line()[pieceX + j] != ' ') {
		  
		    return true;
		}
	    }
	}
	
	node = node->next();
    }   
    
    return false;
    
}

void updateBoard()
{
         
   LinkedNode* node = board;
   LinkedNode* prev = board;
   
   int linesComepleted = 0;
    
   for(int i = 0; i < pieceY; i++) {	
	prev = node;
	node = node->next();
    }   
    
    
    for(int i = 0; i < current.height(); i++) {
	
	for(int j = 0; j < current.width(); j++) {
	    if(current.shape()[i][j] == 1) {
		node->line()[pieceX + j] = current.icon();
			
	    }
	}
	
	bool complete = true;
	    
	for(int k = 0; k < BOARD_WIDTH; k++) {
	    
	    if(node->line()[k] == 32) {
		
		complete = false;
		break;
	    } 
	    
	}

	if(complete) {
	    
	    
	    linesComepleted++;
	    
	    prev->setNext(node->next());
	    
	    int* line = (int*) malloc(BOARD_WIDTH * sizeof(int));
	    
	    for(int t = 0; t < BOARD_WIDTH; t++) {
		line[t] = ' ';
	    }
	    
	    LinkedNode* n = (LinkedNode*) new LinkedNode;
	    n->setNext(board);
	    n->setLine(line);
	    
	    board = n;
	    
	} else {
	    prev = node;
	}
	
	if (pieceY + i >= BOARD_HEIGHT - 1) {
	    break;
	} else {
	    node = node->next();
	}
	
    }
    
    switch(linesComepleted) {
	
	case 1: 
	    score += 40 * (level + 1);
	    break;
	case 2:
	    score += 100 * (level + 1);
	    break;
	case 3:
	    score += 300 * (level + 1);
	    break;
	case 4:
	    score += 1200 * (level + 1);
	    break;
	
    }
    
    linesCleared += linesComepleted;
    
    if(linesCleared > 10) {
	linesCleared = 0;
	level++;
	
	if(level >= endLevel) {
	    gameState = YOUWIN;
	    gameRunning = false;
	}
    }	    
}

void dropPiece() 
{
    LinkedNode* node = board;

    while(1)
    {
	pieceY++;
	if(collision()) break;
	
	score += 2;
	movePiece();    
    }
    
   
    
    resetTempBoard();   
   
}

void moveDown() 
{	
    pieceY++;   
    score++;
}

void moveLeft() 
{
    
    LinkedNode* node = board;
    
    
    for(int i = 0; i < pieceY; i++) {	
	node = node->next();
    }   
	 	    
    for(int i = 0; i < current.height(); i++) {
	for(int j = 0; j < current.width(); j++) {
	    if(pieceX - 1 + j >= 0 ) {
		if(current.shape()[i][j] == 1 && node->line()[pieceX - 1 + j] != ' ') {
		    //printf("DENIED\n");
		    return;
		}
	    } else {
		if(current.shape()[i][j] == 1) {
		    return;
		}
	    }
	}
	node = node->next();
    }
	        
    pieceX--;
}

void moveRight() 
{
    LinkedNode* node = board;
    
    for(int i = 0; i < pieceY; i++) {	
	node = node->next();
    }   
    
    for(int i = 0; i < current.height(); i++) {
	for(int j = 0; j < current.width(); j++) {
	    if(pieceX + 1 + j < BOARD_WIDTH ) {
		if(current.shape()[i][j] == 1 && node->line()[pieceX + 1 + j] != ' ') {
		    return;
		}    
	    } else if(current.shape()[i][j] == 1) {
		return;
	    }
	}
	node = node->next();
    }
    
    pieceX++;
} 
