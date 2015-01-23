 //===================== Util =====================

 
int** allocateArray(int height, int width) 
{
    
    int** p = ( int** ) malloc( height *sizeof( int* ));
	for ( int i = 0; i < height; i++ ) {
	    p[i] = ( int* ) malloc( width * sizeof(int) );	
	}
    return p;
}

void freeArray(int** p, int height, int width) 
{
   
    for ( int i = 0; i < height; i++ ) {
	free(p[i]);	
    }
	
    free(p);
}

int png_load(const char* file_name, 
		     int* width, 
			 int* height, 
			 char** image_data_ptr)
{
    png_byte header[8];

    FILE* fp = fopen(file_name, "rb");
    if (fp == 0)
    {
        fprintf(stderr, "erro: could not open PNG file %s\n", file_name);
        perror(file_name);
        return 0;
    }

    // read the header
    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8))
    {
        fprintf(stderr, "error: %s is not a PNG.\n", file_name);
        fclose(fp);
        return 0;
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        fprintf(stderr, "error: png_create_read_struct returned 0.\n");
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        fclose(fp);
        return 0;
    }

    // create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        fprintf(stderr, "error: png_create_info_struct returned 0.\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
        return 0;
    }

    // the code in this if statement gets called if libpng encounters an error
    if (setjmp(png_jmpbuf(png_ptr))) {
        fprintf(stderr, "error from libpng\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // init png reading
    png_init_io(png_ptr, fp);

    // let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);

    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);

    // variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 temp_width, temp_height;

    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth, &color_type,
        NULL, NULL, NULL);

    if (width) { *width = temp_width; }
    if (height){ *height = temp_height; }

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    rowbytes += 3 - ((rowbytes-1) % 4);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte* image_data;
    image_data = (png_byte*)malloc(rowbytes * temp_height * sizeof(png_byte)+15);
    if (image_data == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG image data\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
        return 0;
    }

    // row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep* row_pointers = (png_bytep*)malloc(temp_height * sizeof(png_bytep));
    if (row_pointers == NULL)
    {
        fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(image_data);
        fclose(fp);
        return 0;
    }

    // set the individual row_pointers to point at the correct offsets of image_data
    int i;
    for (i = 0; i < temp_height; i++)
    {
        row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
    }

    // read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    // clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

    //free(image_data);
	*image_data_ptr = (char*)image_data; // return data pointer

    free(row_pointers);
    fclose(fp);

	fprintf(stderr, "\t texture image size is %d x %d\n", *width, *height);

	return 1;
}

void cleanup() 
{
    
    LinkedNode* current = board;
    LinkedNode* next = board;
    
    for(int i = 0; i < BOARD_HEIGHT; i++) {	
	
	next = current->next();
	free(current);
	current = next;
    }
    
    freeArray(tetri_O.shape(), tetri_O.height(), tetri_O.width());
    
    freeArray(tetri_I.shape(), tetri_I.height(), tetri_I.width());
    
    freeArray(tetri_L.shape(), tetri_L.height(), tetri_L.width());
    
    freeArray(tetri_J.shape(), tetri_J.height(), tetri_J.width());
    
    freeArray(tetri_T.shape(), tetri_T.height(), tetri_T.width());
    
    freeArray(tetri_Z.shape(), tetri_Z.height(), tetri_Z.width());
    
    freeArray(tetri_S.shape(), tetri_S.height(), tetri_S.width());
    
}
