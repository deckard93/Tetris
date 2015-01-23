 //=============== Drawing Functions ===============

 
unsigned int load_and_bind_texture(const char* filename)
{
    char* image_buffer = NULL; // the image data
	int width = 0;
	int height = 0;

	// read in the PNG image data into image_buffer
	if (png_load(filename, &width, &height, &image_buffer)==0)
    {
        fprintf(stderr, "Failed to read image texture from %s\n", filename);
        exit(1);
    }

	unsigned int tex_handle = 0;

	// request one texture handle
	glGenTextures(1, &tex_handle); 

	// create a new texture object and bind it to tex_handle
  	glBindTexture(GL_TEXTURE_2D, tex_handle);

  	glPixelStorei(GL_UNPACK_ALIGNMENT, 50);

  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  	glTexImage2D(GL_TEXTURE_2D, 0, 
				GL_RGB, width, height, 0,
   		 		GL_RGB, GL_UNSIGNED_BYTE, image_buffer);

	
	free(image_buffer); // free the image buffer memory
	
	return tex_handle;
}

void drawEnd(char *msg) 
{
    glColor3f(1.0f, 1.0f, 0.0f); // set RGB values of colour to draw   
    
    glPushMatrix();
	
	// translate it to where we want it
	glTranslatef(WORLD_X/2, WORLD_Y/2, 0.0f);
		    
	// scale it up 
	//glScalef(1.0f, 1.0f, 1.0f);
	glScalef(1.0, 1.0, 1.0);

	// rotate anticlockwise in-plane by 30 degrees
	glRotatef(0.0f, 0.0f, 0.0f, 1.0f); 
		    
	draw_center_text(msg);
		    
    glPopMatrix(); // done with st
    
    glPushMatrix();
    
	glTranslatef(WORLD_X/2, WORLD_Y/3, 0.0f);
	glScalef(0.5, 0.5, 1.0);
	glRotatef(0.0f, 0.0f, 0.0f, 1.0f); 
		    
	string Result = "Score: " ;          // string which will contain the result
	ostringstream convert;  // stream used for the conversion
	convert << score;      	// insert the textual representation of 'Number' in the characters in the stream
	Result.append(convert.str()); // set 'Result' to the contents of the stream
	
	draw_center_text(Result.c_str()); 
		    
    glPopMatrix(); // done with st
    
    
    glPushMatrix();
	
	// translate it to where we want it
	glTranslatef(WORLD_X/2, WORLD_Y / 5, 0.0f);
		    
	// scale it up 
	//glScalef(1.0f, 1.0f, 1.0f);
	glScalef(0.3f, 0.3f, 0.0f);

	// rotate anticlockwise in-plane by 30 degrees
	glRotatef(0.0f, 0.0f, 0.0f, 1.0f); 
		    
	draw_center_text("Press ENTER to return to Main Menu");
		    
    glPopMatrix(); // done with st
    
    
    
}

void draw_stroke_text(const char* text) 
{
	size_t len = strlen(text);
	
	int total_width = 0;
	
	for (size_t i=0;i<len;i++) {
		total_width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}	
	    
}

int draw_center_text(const char* text) 
{
	size_t len = strlen(text);
	
	int total_width = 0;
	
	for (size_t i=0;i<len;i++) {
		total_width += glutStrokeWidth(GLUT_STROKE_ROMAN, text[i]);
		
	}	
	

	
	
	glPushMatrix();
	    glTranslatef(-total_width/2, 0, 0.0f);
	    
	    for (size_t i=0;i<len;i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	    }	
	glPopMatrix();
	    
	
	return total_width;
}

void drawSettings() 
{
     glClear(GL_COLOR_BUFFER_BIT);	//clears to current background colour
    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    
    
    int x = WORLD_X / 4;
    int y = WORLD_Y - WORLD_Y / 10;
    
    	glPushMatrix();
	    glTranslatef(WORLD_X / 2,  WORLD_Y / 15 + 50, 0.0f);
	    glScalef(0.3f, 0.3f, 1.0f);
	    draw_center_text(" Use Mouse to Navigate ");
	glPopMatrix();
    
	glPushMatrix();
	    glTranslatef(WORLD_X / 2, WORLD_Y / 15, 0.0f);
	    glScalef(0.3f, 0.3f, 1.0f);
	    draw_center_text(" Press ENTER/ESC to return to Menu ");
	glPopMatrix();
    
    
    glPushMatrix();
	glTranslatef(x, y, 0.0f);
	
	
	glPushMatrix();
	    glTranslatef(0, 0, 0.0f);
	    glScalef(0.5f, 0.5f, 1.0f);
	    draw_center_text(" Graphics ");
	glPopMatrix();
	
	glPushMatrix();
	    glTranslatef(0, -620, 0.0f);
	    glScalef(0.5f, 0.5f, 1.0f);
	    draw_center_text(" Game ");
	glPopMatrix();	
	
	
	
    glPopMatrix();
    
    
    x = WORLD_X / 2;
    y = WORLD_Y / 2;
    
	    
     
    for(int i = 0; i < 8; i++) {
	
	glPushMatrix();
	  
	    
	    
	    glTranslatef(settings[i].posX(), settings[i].posY(), 0.0f);
	    glScalef(0.5f, 0.5f, 1.0f);
	    
	    glPushMatrix();
	    
	     glColor3f(0.0f, 0.0f, 0.0f);
	    
	    glTranslatef(0, -10, 0.0f);
	    glScalef(settings[i].width(), settings[i].height() * 2, 1.0f);
	    draw_filled_square();
	    glPopMatrix();
	    
	     glColor3f(1.0f, 1.0f, 0.0f);
	    
	    draw_stroke_text(settings[i].text());
	        
	glPopMatrix();
    }
    
    
    for(int i = 0; i < 7; i++) {
	
	glPushMatrix();
	    bool selected;
	    if(radioButtons[i].collision(cursorX, cursorY)) selected = true;
	    else selected = false;
	    
	    
	    glTranslatef(radioButtons[i].posX() - radioButtons[i].width()/4, radioButtons[i].posY(), 0.0f);
	    glScalef(0.5f, 0.5f, 1.0f);
	    
	    glPushMatrix();
	    
	    if(selected) glColor3f(1.0f, 1.0f, 0.0f);
	    else glColor3f(0.0f, 0.0f, 0.0f);
	    
	    glTranslatef(0, 0, 0.0f);
	    glScalef(radioButtons[i].width(), radioButtons[i].height() * 2, 1.0f);
	    draw_filled_square();
	    glPopMatrix();
	    
	    if(selected) glColor3f(0.0f, 0.0f, 0.0f);
	    else glColor3f(1.0f, 1.0f, 0.0f);
	    
	    draw_Border(0, 0, radioButtons[i].width(), radioButtons[i].height() * 2 );
	    
	    switch(i) {
		case 0: 
		    if(graphics == ASCII) {
			glBegin(GL_LINES);
			    glVertex3f(0, 0, 0);
			    glVertex3f(radioButtons[i].width(), radioButtons[i].height() * 2, 0);
			    
			    glVertex3f(0, radioButtons[i].height() * 2, 0);
			    glVertex3f(radioButtons[i].width(), 0, 0);
			
			glEnd();
		    }
		    break;
		
		case 1: 
		    if(graphics == VECTOR) {
			glBegin(GL_LINES);
			    glVertex3f(0, 0, 0);
			    glVertex3f(radioButtons[i].width(), radioButtons[i].height() * 2, 0);
			    
			    glVertex3f(0, radioButtons[i].height() * 2, 0);
			    glVertex3f(radioButtons[i].width(), 0, 0);
			
			glEnd();
		    }
		    break;
		
		case 2: 
		    if(graphics == THREE_D) {
			glBegin(GL_LINES);
			    glVertex3f(0, 0, 0);
			    glVertex3f(radioButtons[i].width(), radioButtons[i].height() * 2, 0);
			    
			    glVertex3f(0, radioButtons[i].height() * 2, 0);
			    glVertex3f(radioButtons[i].width(), 0, 0);
			
			glEnd();
		    }
		    break;
		
		case 3: 
		    if(texture) {
			glBegin(GL_LINES);
			    glVertex3f(0, 0, 0);
			    glVertex3f(radioButtons[i].width(), radioButtons[i].height() * 2, 0);
			    
			    glVertex3f(0, radioButtons[i].height() * 2, 0);
			    glVertex3f(radioButtons[i].width(), 0, 0);
			
			glEnd();
		    }
		    break;
		    
		case 4: 
		    if(fullscreen) {
			glBegin(GL_LINES);
			    glVertex3f(0, 0, 0);
			    glVertex3f(radioButtons[i].width(), radioButtons[i].height() * 2, 0);
			    
			    glVertex3f(0, radioButtons[i].height() * 2, 0);
			    glVertex3f(radioButtons[i].width(), 0, 0);
			
			glEnd();
		    }
		    break;
		    
		case 5: 
		    if(FPS) {
			glBegin(GL_LINES);
			    glVertex3f(0, 0, 0);
			    glVertex3f(radioButtons[i].width(), radioButtons[i].height() * 2, 0);
			    
			    glVertex3f(0, radioButtons[i].height() * 2, 0);
			    glVertex3f(radioButtons[i].width(), 0, 0);
			
			glEnd();
		    }
		    break;
		
		case 6: 
		    if(ghost) {
			glBegin(GL_LINES);
			    glVertex3f(0, 0, 0);
			    glVertex3f(radioButtons[i].width(), radioButtons[i].height() * 2, 0);
			    
			    glVertex3f(0, radioButtons[i].height() * 2, 0);
			    glVertex3f(radioButtons[i].width(), 0, 0);
			
			glEnd();
		    }
		    break;
	    }
	        
	glPopMatrix();
    }
    
       for(int i = 7; i < 11; i++) {
	
	glPushMatrix();
	    bool selected;
	    if(radioButtons[i].collision(cursorX, cursorY)) selected = true;
	    else selected = false;
	    
	    
	    glTranslatef(radioButtons[i].posX() - radioButtons[i].width()/4, radioButtons[i].posY(), 0.0f);
	    glScalef(0.5f, 0.5f, 1.0f);
	    
	    glPushMatrix();
	    
	    if(selected) glColor3f(1.0f, 1.0f, 0.0f);
	    else glColor3f(0.0f, 0.0f, 0.0f);
	    
	    glTranslatef(0, 0, 0.0f);
	    glScalef(radioButtons[i].width(), radioButtons[i].height() * 2, 1.0f);
	    draw_filled_square();
	    glPopMatrix();
	    
	    if(selected) glColor3f(0.0f, 0.0f, 0.0f);
	    else glColor3f(1.0f, 1.0f, 0.0f);
	    

	    if(i <= 8)draw_Triangle(0, 0, radioButtons[i].width(), radioButtons[i].height() * 2, 1);
	    else draw_Triangle(0, 0, radioButtons[i].width(), radioButtons[i].height() * 2, 0);

	    
	    
	    
	    if(i == 9) {
		glColor3f(1.0f, 1.0f, 0.0f);
		
		glPushMatrix(); 
		    glTranslatef(-400, 0, 0.0f);
		    
		    string Result;          // string which will contain the result
		    ostringstream convert;   // stream used for the conversion
		    convert << startLevel;      // insert the textual representation of 'Number' in the characters in the stream
		    Result = convert.str(); // set 'Result' to the contents of the stream
	    
		    draw_stroke_text(Result.c_str());
		    
		    
		glPopMatrix();
	    } else if(i == 10) {
		glColor3f(1.0f, 1.0f, 0.0f);
		
		glPushMatrix(); 
		    glTranslatef(-400, 0, 0.0f);
		    
		    string Result;          // string which will contain the result
		    ostringstream convert;   // stream used for the conversion
		    convert << endLevel;      // insert the textual representation of 'Number' in the characters in the stream
		    Result = convert.str(); // set 'Result' to the contents of the stream
	    
		    draw_stroke_text(Result.c_str());
		    
		    
		glPopMatrix();
		
		
	    }

	        
	glPopMatrix();
    }
    
    
    for(int i = 0; i < 3; i++) {
	
	glPushMatrix();
	    
	    
	    glTranslatef(render[i].posX(), render[i].posY(), 0.0f);
	    glScalef(0.5f, 0.5f, 1.0f);
	    
	    glPushMatrix();
	    
	    glColor3f(0.0f, 0.0f, 0.0f);
	    
	    glTranslatef(0, -10, 0.0f);
	    glScalef(render[i].width(), render[i].height() * 2, 1.0f);
	    draw_filled_square();
	    glPopMatrix();
	    
	    glColor3f(1.0f, 1.0f, 0.0f);
	    
	    draw_stroke_text(render[i].text());
	        
	glPopMatrix();
    }
    
    
    



    
    
    
}

void drawHowTo() 
{
    
    
    glClear(GL_COLOR_BUFFER_BIT);	//clears to current background colour
    glColor3f(1.0f, 1.0f, 1.0f); // white
    
    glEnable(GL_TEXTURE_2D); 
    glBindTexture(GL_TEXTURE_2D, howto);
    
    glBegin(GL_QUADS); 
	glTexCoord2f (0.0f,0.0f); // lower left corner
  	glVertex2i(0, 0);
  	glTexCoord2f (1.0f, 0.0f); // lower right corner
  	glVertex2i(WORLD_X, 0);
  	glTexCoord2f (1.0f, 1.0f); // upper right corner
  	glVertex2i(WORLD_X, WORLD_Y);
  	glTexCoord2f (0.0f, 1.0f); // upper left corner
  	glVertex2i(0, WORLD_Y);
    glEnd();
    
    
   
    
    glDisable(GL_TEXTURE_2D); 	
    
}

void drawMenu() 
{
    glClear(GL_COLOR_BUFFER_BIT);	//clears to current background colour
    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    
    int x = WORLD_X / 2;
    int y = WORLD_Y / 2;
    
    
    for(int i = 0; i < 4; i++) {
	
	glPushMatrix();
	    bool selected;
	    if(mainMenu[i].collision(cursorX, cursorY)) selected = true;
	    else selected = false;
	    
	    
	    glTranslatef(mainMenu[i].posX(), mainMenu[i].posY(), 0.0f);
	    glScalef(0.5f, 0.5f, 1.0f);
	    
	    glPushMatrix();
	    
	    if(mainMenu[i].selected()) glColor3f(1.0f, 1.0f, 0.0f);
	    else glColor3f(0.0f, 0.0f, 0.0f);
	    
	    glTranslatef(-mainMenu[i].width()/2, -10, 0.0f);
	    glScalef(mainMenu[i].width(), mainMenu[i].height() * 2, 1.0f);
	    draw_filled_square();
	    glPopMatrix();
	    
	    if(mainMenu[i].selected()) glColor3f(0.0f, 0.0f, 0.0f);
	    else glColor3f(1.0f, 1.0f, 0.0f);
	    
	    draw_center_text(mainMenu[i].text());
	    	    
	glPopMatrix();
    }

}

void drawPause() 
{
     glClear(GL_COLOR_BUFFER_BIT);	//clears to current background colour
     glColor3f(1.0f, 1.0f, 0.0f); // yellow
    
    int x = WORLD_X / 2;
    int y = WORLD_Y / 2;
    
    
    for(int i = 0; i < 5; i++) {
	
	glPushMatrix();
	    bool selected;
	    if(paused[i].collision(cursorX, cursorY)) selected = true;
	    else selected = false;
	    
	    
	    glTranslatef(paused[i].posX(), paused[i].posY(), 0.0f);
	    glScalef(0.5f, 0.5f, 1.0f);
	    
	    glPushMatrix();
	    
	    if(paused[i].selected()) glColor3f(1.0f, 1.0f, 0.0f);
	    else glColor3f(0.0f, 0.0f, 0.0f);
	    
	    glTranslatef(-paused[i].width()/2, -10, 0.0f);
	    glScalef(paused[i].width(), paused[i].height() * 2, 1.0f);
	    draw_filled_square();
	    glPopMatrix();
	    
	    if(paused[i].selected()) glColor3f(0.0f, 0.0f, 0.0f);
	    else glColor3f(1.0f, 1.0f, 0.0f);
	    
	    draw_center_text(paused[i].text());
	    	    
	glPopMatrix();
    }

}

//================= ASCII Render =================
void draw_ASCII_Next() 
{
    glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw   
    
    int d_X;
    int d_Y;
    
    d_X = WORLD_X / 5 * 1 - blockSize/2 - aux_Box_S/2;
    d_Y = 50 + 20 * blockSize ;
  
    glPushMatrix();
	glTranslatef(d_X, d_Y, 0.0f);
	
    
	//Draw Title
	glPushMatrix();
	    glScalef(blockSize/130.0, blockSize/130.0, 1.0f);
	    draw_stroke_text("Next: "); 	
	glPopMatrix();
	
	//Draw top border
	d_X = blockSize;
	d_Y = - 2*blockSize;
	
	for(int j = 0; j < 5; j++) 
	{	  
	    glPushMatrix();
		glTranslatef(d_X + j * blockSize, d_Y, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
		draw_stroke_text("=") ;
	    glPopMatrix(); // done with stack
	}
	
	
	//Print bottom border
	d_Y = -7 * blockSize;
	d_X = blockSize;
	
	for(int j = 0; j < 5; j++) {
		
	    glPushMatrix();
		glTranslatef(d_X + j * blockSize, d_Y, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
			
		draw_stroke_text("=");	
	    glPopMatrix(); // done with stack
	}
	
	
	//Print left border
	d_Y = -2 * blockSize;
	d_X = 0;
	
	for(int j = 0; j < 6; j++) {
		
	    glPushMatrix();
		glTranslatef(d_X, d_Y - j * blockSize, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
			
		draw_stroke_text("<!");	
	    glPopMatrix(); // done with stack
	}
	
	    
	    
	//Print right border
	d_Y = -2 * blockSize;
	d_X = 6 * blockSize;
	
	for(int j = 0; j < 6; j++) {
		
	    glPushMatrix();
		glTranslatef(d_X, d_Y - j * blockSize, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
			
		draw_stroke_text("!>");	
	    glPopMatrix(); // done with stack
	}
	
	
	
	//Draw Piece
	
	d_Y = - 6 * blockSize;
	d_X = blockSize + (5/2 - following.width()/2) * blockSize;
	
	for(int i = following.height() - 1; i >= 0; i--) {
	    for(int j = 0; j < following.width(); j++) {
		if(following.shape()[i][j] == 1) {
		    glPushMatrix();
		    
			glTranslatef(d_X + j * blockSize, d_Y, 0.0f);
			glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
		    
			color_Me(following.icon());
			draw_stroke_text("[]") ;
			    
		    glPopMatrix(); // done with stack
		}
	    }
	    d_Y += blockSize;
	}
	
	
    
    glPopMatrix();
    
     
    
}

void draw_ASCII_Hold() 
{
    glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw   
    
    int d_X;
    int d_Y;
    
    d_X = WORLD_X / 5 * 4 - blockSize/2 - aux_Box_S/2;
    d_Y = 50 + 20 * blockSize ;
  
    glPushMatrix();
	glTranslatef(d_X, d_Y, 0.0f);
	
    
	//Draw Title
	glPushMatrix();
	    glScalef(blockSize/130.0, blockSize/130.0, 1.0f);
	    draw_stroke_text("Hold: "); 	
	glPopMatrix();
	
	//Draw top border
	d_X = blockSize;
	d_Y = - 2*blockSize;
	
	for(int j = 0; j < 5; j++) 
	{	  
	    glPushMatrix();
		glTranslatef(d_X + j * blockSize, d_Y, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
		draw_stroke_text("=") ;
	    glPopMatrix(); // done with stack
	}
	
	
	//Print bottom border
	d_Y = -7 * blockSize;
	d_X = blockSize;
	
	for(int j = 0; j < 5; j++) {
		
	    glPushMatrix();
		glTranslatef(d_X + j * blockSize, d_Y, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
			
		draw_stroke_text("=");	
	    glPopMatrix(); // done with stack
	}
	
	
	//Print left border
	d_Y = -2 * blockSize;
	d_X = 0;
	
	for(int j = 0; j < 6; j++) {
		
	    glPushMatrix();
		glTranslatef(d_X, d_Y - j * blockSize, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
			
		draw_stroke_text("<!");	
	    glPopMatrix(); // done with stack
	}
	
	    
	    
	//Print right border
	d_Y = -2 * blockSize;
	d_X = 6 * blockSize;
	
	for(int j = 0; j < 6; j++) {
		
	    glPushMatrix();
		glTranslatef(d_X, d_Y - j * blockSize, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
			
		draw_stroke_text("!>");	
	    glPopMatrix(); // done with stack
	}
	
	
	
	//Draw Piece
	
	d_Y = - 6 * blockSize;
	d_X = blockSize + (5/2 - hold.width()/2) * blockSize;
	
	for(int i = hold.height() - 1; i >= 0; i--) {
	    for(int j = 0; j < hold.width(); j++) {
		if(hold.shape()[i][j] == 1) {
		    glPushMatrix();
		    
			glTranslatef(d_X + j * blockSize, d_Y, 0.0f);
			glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
		    
			color_Me(hold.icon());
			if(holdInit) draw_stroke_text("[]") ;
			    
		    glPopMatrix(); // done with stack
		}
	    }
	    d_Y += blockSize;
	}
	
	
    
    glPopMatrix();
    
    
}

void draw_ASCII_Board() 
{
    
    int d_X = WORLD_X / 5 * 2 - blockSize;
    int d_Y = 0 + 22 * blockSize - 1 ;
   
    char buffer[4];
   
    glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw   
    
    for(int i = INVISIBLE; i < BOARD_HEIGHT + 1 ; i++) {
	
	glPushMatrix();
	    glTranslatef(d_X, d_Y - (i - INVISIBLE)* blockSize, 0.0f);
	    
	    glPushMatrix();    
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
		
		draw_stroke_text("<!") ;
	    glPopMatrix();
			    
	    for(int j = 0; j < BOARD_WIDTH; j++) {
		
		glTranslatef(blockSize, 0, 0.0f);
		
		glPushMatrix();
		    
		    glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
		    
		    if(i >= BOARD_HEIGHT) {
			buffer[0] = '=';
			buffer[1] = '\0';
		    } else {
			if(temp[i][j] == ' ') {

			    buffer[0] = ' ';
			    buffer[1] = '.';
			    buffer[2] = '\0';
			} else {
			    
			    buffer[0] = '[';
			    buffer[1] = ']';
			    buffer[2] = '.';
			    buffer[3] = '\0';
			    //buffer[0] = temp[i][j];
			    
			    color_Me(temp[i][j]);
			    
			    if(temp[i][j] == 'G') {
				buffer[0] = '#';
				buffer[1] = '.';
				buffer[2] = '\0';
			    }   
			}
		    }
		    
		    draw_stroke_text(buffer) ;
		    
		    glColor3f(1.0f, 1.0f, 1.0f);
			
		    glPopMatrix();
		
	    }
	    glPushMatrix();

		glTranslatef( blockSize, 0, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
			    
		draw_stroke_text("!>") ;
				    
	    glPopMatrix();
	
	glPopMatrix();
    }
   
    glPushMatrix();
	
	glTranslatef(d_X, d_Y - 21 * blockSize, 0.0f);
	
	for(int j = 0; j < BOARD_WIDTH; j++) {
	    
	    glPushMatrix();  
		glTranslatef(0 + (j + 1) * blockSize, 0, 0.0f);
		glScalef(blockSize/190.0, blockSize/190.0, blockSize/190.0);
		    
		draw_stroke_text("\\/") ;
		    
	    glPopMatrix(); 
	}

    glPopMatrix();
	    
}

//================= Vector Render =================
void displayFPS() 							
{
	glColor3f(1.0f, 1.0f, 0.0f); // set RGB values of colour to draw
    

	glPushMatrix(); //FPS
		glScalef(0.3f, 0.3f, 1.0f); // this will work
		glTranslatef(10, 10, 0.0f); // this will work
		
		
		string Result;          // string which will contain the result
		ostringstream convert;   // stream used for the conversion
		convert << fps;      // insert the textual representation of 'Number' in the characters in the stream
		Result = convert.str(); // set 'Result' to the contents of the stream
		
		draw_stroke_text(Result.c_str());
	glPopMatrix();	
	
}

void draw_filled_square() 
{
    
	
	static float vertex[4][2] =
		{
			{0, 1},
			{1, 1},
			{1, 0},
			{0, 0}
		};
	
	glBegin(GL_QUADS); 
		for (size_t i=0;i<4;i++) {
			
			glVertex2fv(vertex[i]);
		}
	glEnd();
	
}

void draw_square(char c) 
{
    
	glColor3f(0.0f, 0.0f, 0.0f); // set RGB values of colour to draw
    

	
	//printf('%c', c);
	
	if(!texture) {
	    switch((char) c) {
		case 'T':
		    glColor3f(1.0f, 0.0f, 1.0f); // purple
		    break;
		case 'J':
		    glColor3f(0.0f, 0.0f, 1.0f); // blue
		    break;
		case 'I':
		    glColor3f(0.0f, 1.0f, 1.0f); // light-blue
		    break;
		case 'Z':
		    glColor3f(1.0f, 0.0f, 0.0f); // red
		    break;
		case 'S':
		    glColor3f(0.0f, 1.0f, 0.0f); // green
		    break;
		case 'O':
		    glColor3f(1.0f, 1.0f, 0.0f); // yellow
		    break;
		case 'L':
		    glColor3f(1.0f, 0.5f, 0.0f); // orange
		    break;
		    
		case 'G':
		    draw_Ghost_Block();
		    return;
	    }
	} else {	  
	    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
	    glColor3f(1.0f, 1.0f, 1.0f); // black
	    
	    glEnable(GL_TEXTURE_2D); 
	    
	    switch((char) c) {
		case 'T':
		    glBindTexture(GL_TEXTURE_2D, tetri_T.texture());
		    break;
		case 'J':
		    glBindTexture(GL_TEXTURE_2D, tetri_J.texture());
		    break;
		case 'I':
		    glBindTexture(GL_TEXTURE_2D, tetri_I.texture());
		    break;
		case 'Z':
		    glBindTexture(GL_TEXTURE_2D, tetri_Z.texture());
		    break;
		case 'S':
		    glBindTexture(GL_TEXTURE_2D, tetri_S.texture());
		    break;
		case 'O':
		    glBindTexture(GL_TEXTURE_2D, tetri_O.texture());
		    break;
		case 'L':
		    glBindTexture(GL_TEXTURE_2D, tetri_L.texture());
		    break;
		    
		case 'G':
		    glDisable(GL_TEXTURE_2D);
		    draw_Ghost_Block();
		    return;
	    }
	    
	}
	   
	
	static float vertex[4][2] =
		{
			{-1, 1},
			{1, 1},
			{1, -1},
			{-1, -1}
		};
		
		
	glBegin(GL_QUADS); 
		for (size_t i=0;i<4;i++) {
			glTexCoord2f ( (vertex[i][0] + 1) / 2,(vertex[i][1] + 1) / 2); // lower left corner
			glVertex2fv(vertex[i]);
		}
	glEnd();
	
	
	    
	    
	
	    glColor3f(0.0f, 0.0f, 0.0f); // set RGB values of colour to draw
		    
	    glBegin(GL_LINE_LOOP); 
		    for (size_t i=0;i<4;i++) {
			    
			    glVertex2fv(vertex[i]);
		    }
	    glEnd();
	
	
  	if(texture) glDisable(GL_TEXTURE_2D);
	
	
}

void draw_Border(int d_X, int d_Y, int size_X, int size_Y) 
{
    
    //glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw
    
    
    
    
	glBegin(GL_LINE_LOOP); 
	    glVertex2i(d_X , d_Y );
	    glVertex2i(d_X + size_X, d_Y);
	    glVertex2i(d_X + size_X, d_Y + size_Y);
	    glVertex2i(d_X , d_Y + size_Y);
	glEnd();   
    
    
}

void draw_Triangle(int d_X, int d_Y, int size_X, int size_Y,  int orientation) 
{
    
    //glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw
    if(orientation == 1) {
    
	glBegin(GL_LINE_LOOP); 
	    glVertex2i(d_X , d_Y );
	    glVertex2i(d_X + size_X, d_Y);
	    glVertex2i(d_X + size_X/2, d_Y + size_Y);
	glEnd();   
    
    } else {
	glBegin(GL_LINE_LOOP); 
	    glVertex2i(d_X , d_Y + size_Y);
	    glVertex2i(d_X + size_X/2, d_Y);
	    glVertex2i(d_X + size_X, d_Y + size_Y);
	glEnd();   
	
    }
    
}

void draw_Ghost_Block() 
{
    
	glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw
    
	//printf('%c', c);
	
	
	static float vertex[4][2] =
		{
			{-1, 1},
			{1, 1},
			{1, -1},
			{-1, -1}
		};
	
	glBegin(GL_LINE_LOOP); 
		for (size_t i=0;i<4;i++) {
			
			glVertex2fv(vertex[i]);
		}
	glEnd();
}

void draw_Score() 
{
    glColor3f(1.0f, 1.0f, 0.0f); // set RGB values of colour to draw
    
    glPushMatrix(); //FPS
	glTranslatef(10, WORLD_Y - 40, 0.0f); // this will work
	glScalef(0.3f, 0.3f, 1.0f); // this will work
	
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << score;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	
	draw_stroke_text("Score: "); 
	draw_stroke_text(Result.c_str());
    glPopMatrix();	
}

void draw_Level() 
{
    glColor3f(1.0f, 1.0f, 0.0f); // set RGB values of colour to draw
    
    glPushMatrix(); //FPS
	
	glTranslatef(10, WORLD_Y - 80, 0.0f); // this will work
	glScalef(0.3f, 0.3f, 1.0f); // this will work
	
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << level;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	
	draw_stroke_text("Level: "); 
	draw_stroke_text(Result.c_str());
    glPopMatrix();
}

void draw_Next() 
{
    glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw
    
    int d_X = WORLD_X / 5;
    int d_Y = 0 + 20 * blockSize - 1 ;
    
     glPushMatrix();
	glTranslatef(d_X - blockSize/2 - aux_Box_S/2, d_Y + 50, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	
	draw_stroke_text("Next: "); 
	
    glPopMatrix();
    
    
    draw_Border(d_X - blockSize/2 - aux_Box_S/2, d_Y + blockSize/2, aux_Box_S, -aux_Box_S );
    
    
    d_X = WORLD_X / 5 + (-1) * blockSize;
    d_Y = 0 + 20 * blockSize - 1 - (5 - following.height()) * blockSize;
    
    for(int i = 0; i < following.height(); i++) {
	for(int j = 0; j < following.width(); j++) {
	    if(following.shape()[i][j] == 1) {
		glPushMatrix();

		    // translate it to where we want it
		    glTranslatef(d_X, d_Y, 0.0f);
		    
		    glScalef(blockSize/2, blockSize/2, blockSize/2);

		    
		    draw_square(following.icon());

			
		glPopMatrix(); // done with stack
	    }
	    d_X += blockSize;
	}
	d_Y -= blockSize;
	d_X = WORLD_X / 5 + (-1) * blockSize;
    }
}

void draw_Hold() 
{
    glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw   
    
    int d_X = WORLD_X / 5 * 4;
    int d_Y = 0 + 20 * blockSize - 1 ;
    
    glPushMatrix();
	glTranslatef(d_X - blockSize/2 - aux_Box_S/2, d_Y + 50, 0.0f);
	glScalef(0.3f, 0.3f, 1.0f);
	
	draw_stroke_text("Hold: "); 
	
    glPopMatrix();
    
    draw_Border(d_X - blockSize/2 - aux_Box_S/2, d_Y + blockSize/2, aux_Box_S, -aux_Box_S );
    
    d_X = WORLD_X / 5 * 4 + (-1) * blockSize;
    d_Y = 0 + 20 * blockSize - 1 - (5 - hold.height()) * blockSize;
    
    for(int i = 0; i < hold.height(); i++) {
	for(int j = 0; j < hold.width(); j++) {
	    if(hold.shape()[i][j] == 1) {
		glPushMatrix();

		    // translate it to where we want it
		    glTranslatef(d_X, d_Y, 0.0f);
		    
		    glScalef(blockSize/2, blockSize/2, blockSize/2);

		    
		   if(holdInit) draw_square(hold.icon());

			
		glPopMatrix(); // done with stack
	    }
	    d_X += blockSize;
	}
	d_Y -= blockSize;
	d_X = WORLD_X / 5 * 4 + (-1) * blockSize;
    }
}

void draw_Board() 
{
    int d_X = WORLD_X / 5 * 2;
    int d_Y = 0 + 22 * blockSize - 1 ;
    
     glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw   
    
    draw_Border(d_X - blockSize/2 - 1, d_Y + blockSize/2 + 1, 10 * blockSize + 2, (- 20 * blockSize) - 3);
    
    for(int i = INVISIBLE; i < BOARD_HEIGHT; i++) {
	glPushMatrix();
	
	glTranslatef(d_X, d_Y - (i - INVISIBLE) * blockSize, 0.0f);
	
	
	for(int j = 0; j < BOARD_WIDTH; j++) {
	    if(temp[i][j] != ' ') {
	    
		glPushMatrix();

		    // translate it to where we want it
		    glTranslatef(0 + j * blockSize, 0, 0.0f);
		    
		    // scale it up 
		    //glScalef(1.0f, 1.0f, 1.0f);
		    glScalef(blockSize/2, blockSize/2, blockSize/2);

		    // rotate anticlockwise in-plane by 30 degrees
		    glRotatef(0.0f, 0.0f, 0.0f, 1.0f); 
		    
		    draw_square(temp[i][j]);
		    
		glPopMatrix(); // done with stack

	    }	    
	}
	glPopMatrix(); // done with stack
    }
}

void color_Me(char c) 
{
    
    switch(c) {
	case 'T':
	    glColor3f(1.0f, 0.0f, 1.0f); // purple
	    break;
	case 'J':
	    glColor3f(0.0f, 0.0f, 1.0f); // blue
	    break;
	case 'I':
	    glColor3f(0.0f, 1.0f, 1.0f); // light-blue
	    break;
	case 'Z':
	    glColor3f(1.0f, 0.0f, 0.0f); // red
	    break;
	case 'S':
	    glColor3f(0.0f, 1.0f, 0.0f); // green
	    break;
	case 'O':
	    glColor3f(1.0f, 1.0f, 0.0f); // yellow
	    break;
	case 'L':
	    glColor3f(1.0f, 0.5f, 0.0f); // orange
	    break;    
    }
}


//================= 3D Render =================
void make_cube(char c)
{
    
	glEnable(GL_TEXTURE_2D); 
    
    
	    switch((char) c) {
		case 'B':
		    glBindTexture(GL_TEXTURE_2D, border);
		    break;
		case 'T':
		    glBindTexture(GL_TEXTURE_2D, tetri_T.texture());
		    break;
		case 'J':
		    glBindTexture(GL_TEXTURE_2D, tetri_J.texture());
		    break;
		case 'I':
		    glBindTexture(GL_TEXTURE_2D, tetri_I.texture());
		    break;
		case 'Z':
		    glBindTexture(GL_TEXTURE_2D, tetri_Z.texture());
		    break;
		case 'S':
		    glBindTexture(GL_TEXTURE_2D, tetri_S.texture());
		    break;
		case 'O':
		    glBindTexture(GL_TEXTURE_2D, tetri_O.texture());
		    break;
		case 'L':
		    glBindTexture(GL_TEXTURE_2D, tetri_L.texture());
		    break;
		    
		case 'G':
		    //glBindTexture(GL_TEXTURE_2D, tetri_L.texture());
		    glColor3f(1.0, 1.0, 1.0);
		    glDisable(GL_TEXTURE_2D); 
		    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		    break;
		
	    }
	    
    
	static float vertices[8][3] = 
		{
			{-0.5f, -0.5f, -0.5f}, // front
			{0.5f, -0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			{-0.5f, 0.5f, -0.5f},
			{-0.5f, -0.5f, 0.5f}, // back 
			{0.5f, -0.5f, 0.5f},
			{0.5f, 0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f}
		};

	// indices into verices
	static size_t faces[6][4] =
		{
			{0, 1, 2, 3},  // front
			{5, 4, 7, 6},  // back
			{4, 0, 3, 7},  // left
			{1, 5, 6, 2},  // right
			{4, 5, 1, 0},  // bottom
			{3, 2, 6, 7}   // top
		};

	
	glBegin(GL_QUADS);
	for (size_t f=0;f<6;f++) { // for each face 
	    
		glTexCoord2f (0.0f,0.0f); // lower left corner
		glVertex3fv(vertices[faces[f][0]]);
		
		glTexCoord2f (1.0f, 0.0f); // lower right corner
		glVertex3fv(vertices[faces[f][1]]);
		
		glTexCoord2f (1.0f, 1.0f); // upper right corner
		glVertex3fv(vertices[faces[f][2]]);
		
		glTexCoord2f (0.0f, 1.0f); // upper left corner
		glVertex3fv(vertices[faces[f][3]]);
		
		
		
	}
	glEnd();

	
	if(c == 'G') glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	
	glDisable(GL_TEXTURE_2D); 
	

}

void draw_3D_Next() 
{
    glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw   
    
    
    int d_X;
    int d_Y;
    
    int blockSize = 1;
    
    d_X = -14;
    d_Y = 19 ;
  
    glPushMatrix();
	glTranslatef(d_X, d_Y, 0.0f);
	
	d_Y = -3;
    
	//Draw Title
	glPushMatrix();
	    glScalef(1.0/60.0, 1.0/60.0, 0.0f);
	    draw_stroke_text("Next: "); 	
	glPopMatrix();
	
	//Draw top border and bottom border
	
	for(int j = 0; j < 5; j++) 
	{	  
	    glPushMatrix();
		glTranslatef(0 + j, d_Y, 0.0f);
		make_cube('B');
	    glPopMatrix(); // done with stack
	    
	    glPushMatrix();
		glTranslatef(0 + j, d_Y-6, 0.0f);
		make_cube('B');
	    glPopMatrix(); // done with stack
	    
	}
	
	
	
	//Print left and right border
	
	for(int j = 0; j < 7; j++) {
		
	    glPushMatrix();
		glTranslatef(-1, d_Y - j, 0.0f);
			
		make_cube('B');
	    glPopMatrix(); // done with stack
	    
	    glPushMatrix();
		glTranslatef(5, d_Y - j, 0.0f);
		
		make_cube('B');
	    glPopMatrix(); // done with stack
	}
	
	    
	
	
	
	//Draw Piece
	
	d_Y = - 8;
	d_X = blockSize + (5/2 - following.width()/2);
	
	for(int i = following.height() - 1; i >= 0; i--) {
	    for(int j = 0; j < following.width(); j++) {
		if(following.shape()[i][j] == 1) {
		    glPushMatrix();
			glTranslatef(d_X + j * blockSize, d_Y, 0.0f);
			make_cube(following.icon()) ;
			    
		    glPopMatrix(); // done with stack
		}
	    }
	    d_Y += blockSize;
	}
	
	
    
    glPopMatrix();
}
    
void draw_3D_Hold() 
{
    glColor3f(1.0f, 1.0f, 1.0f); // set RGB values of colour to draw   
    
    
    int d_X;
    int d_Y;
    
    int blockSize = 1;
    
    d_X = 9;
    d_Y = 19 ;
  
    glPushMatrix();
	glTranslatef(d_X, d_Y, 0.0f);
	
	d_Y = -3;
    
	//Draw Title
	glPushMatrix();
	    glScalef(1.0/60.0, 1.0/60.0, 0.0f);
	    draw_stroke_text("Hold: "); 	
	glPopMatrix();
	
	//Draw top border and bottom border
	
	for(int j = 0; j < 5; j++) 
	{	  
	    glPushMatrix();
		glTranslatef(0 + j, d_Y, 0.0f);
		make_cube('B');
	    glPopMatrix(); // done with stack
	    
	    glPushMatrix();
		glTranslatef(0 + j, d_Y-6, 0.0f);
		make_cube('B');
	    glPopMatrix(); // done with stack
	    
	}
	
	
	
	//Print left and right border
	
	for(int j = 0; j < 7; j++) {
		
	    glPushMatrix();
		glTranslatef(-1, d_Y - j, 0.0f);
			
		make_cube('B');
	    glPopMatrix(); // done with stack
	    
	    glPushMatrix();
		glTranslatef(5, d_Y - j, 0.0f);
		
		make_cube('B');
	    glPopMatrix(); // done with stack
	}
	
	    
	
	
	
	//Draw Piece
	
	d_Y = - 8;
	d_X = blockSize + (5/2 - hold.width()/2);
	
	for(int i = hold.height() - 1; i >= 0; i--) {
	    for(int j = 0; j < hold.width(); j++) {
		if(hold.shape()[i][j] == 1) {
		    glPushMatrix();
			glTranslatef(d_X + j * blockSize, d_Y, 0.0f);
			if(holdInit) make_cube(hold.icon()) ;
			    
		    glPopMatrix(); // done with stack
		}
	    }
	    d_Y += blockSize;
	}
	
	
    
    glPopMatrix();
}
 
void draw3DScore() 
{
    
    glColor3f(1.0f, 1.0f, 0.0f); // set RGB values of colour to draw
    
    glPushMatrix(); //FPS
	glTranslatef(-24, 26, 0.0f); // this will work
	glScalef(1.0/60.0, 1.0/60.0, 0.0f);
	
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << score;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	
	draw_stroke_text("Score: "); 
	draw_stroke_text(Result.c_str());
    glPopMatrix();	
    
}

void draw3DLevel() 
{
    glColor3f(1.0f, 1.0f, 0.0f); // set RGB values of colour to draw
    
    glPushMatrix(); //FPS
	glTranslatef(-24, 24, 0.0f); // this will work
	glScalef(1.0/60.0, 1.0/60.0, 0.0f);
	
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << level;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream
	
	draw_stroke_text("Level: "); 
	draw_stroke_text(Result.c_str());
    glPopMatrix();
    
}

void draw3DFPS() 
{
        glColor3f(1.0f, 1.0f, 0.0f); // set RGB values of colour to draw
    
    glPushMatrix(); //FPS
	glTranslatef(-24, -3, 0.0f); // this will work
	glScalef(1.0/60.0, 1.0/60.0, 0.0f);
	
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << fps;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str(); // set 'Result' to the contents of the stream

	draw_stroke_text(Result.c_str());
    glPopMatrix();
    
}

 
void draw3DBoard() {
       
    //Draw Left and Right Borders
    for(int i = 0 ; i < BOARD_HEIGHT - INVISIBLE; i++)
    {

	glPushMatrix();
	    glTranslatef(-BOARD_WIDTH/2 - 1, i, 0.0f);
	    make_cube('B');
	glPopMatrix();
	
	glPushMatrix();
	    glTranslatef(BOARD_WIDTH/2, i, 0.0f);
	    make_cube('B');
	glPopMatrix();	

    }

    //Draw Bottom Border
    for(int i = -BOARD_WIDTH/2 -1 ; i < BOARD_WIDTH/2 + 1; i++) {

	glPushMatrix();
	    glTranslatef(i, -1, 0.0f);
	    //glCallList(g_the_cube);
	    make_cube('B');
	glPopMatrix();
	
    }


    //Draw Board
    int blockSize = 1.0;

    int d_X = -5;
    int d_Y = 19;

    for(int i = INVISIBLE; i < BOARD_HEIGHT; i++) {
	glPushMatrix();
	
	glTranslatef(d_X, d_Y - (i - INVISIBLE) * blockSize, 0.0f);
	
	for(int j = 0; j < BOARD_WIDTH; j++) {
	    if(temp[i][j] != ' ') {
	    
		glPushMatrix();

		    // translate it to where we want it
		    glTranslatef(0 + j * blockSize, 0, 0.0f);
		    
		    // scale it up 
		    //glScalef(1.0f, 1.0f, 1.0f);
		    //glScalef(blockSize/2, blockSize/2, blockSize/2);

		    // rotate anticlockwise in-plane by 30 degrees
		    //glRotatef(0.0f, 0.0f, 0.0f, 1.0f); 
		    
		    //glCallList(g_the_cube);
		    make_cube(temp[i][j]);
		    
		glPopMatrix(); // done with stack

	    }	    
	}
	glPopMatrix(); // done with stack
    }
}


void draw3DMain()
{
	init3D();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	
	// position and orient camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, // eye position
			  eyeX, eyeY, 0, // reference point
			  0, 1, 0  // up vector
		);

	// draw something in 3D
	glColor3f(1.0f, 1.0f, 1.0f); 
	
	
	
	glPushMatrix();
	    glRotated(rotateZ, 0.0, 1.0, 0.0 );
	
	    if(FPS) draw3DFPS();
	    
	    draw3DScore();
	    draw3DLevel();
	    
	    
	    draw_3D_Next();
	    draw_3D_Hold();
	    
	
	    draw3DBoard();
	    
	glPopMatrix();	   
	
}