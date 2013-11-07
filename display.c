
# define VIDEO_ADDRESS 0xb8000
# define MAX_ROWS 25
# define MAX_COLS 80
// Attribute byte for our default colour scheme .
# define WHITE_ON_BLACK 0x0f
// Screen device I / O ports
# define REG_SCREEN_CTRL 0x3D4
# define REG_SCREEN_DATA 0x3D5



int get_screen_offset(int col , int row){
	
	int cursor_offset = (row * MAX_COLS + col) * 2;
	port_byte_out ( REG_SCREEN_CTRL , 14);
	port_byte_out ( REG_SCREEN_DATA , ( unsigned char )( cursor_offset >> 8));
	port_byte_out ( REG_SCREEN_CTRL , 15);

	cursor_offset -= 2*MAX_COLS;
	return cursor_offset;
}

int get_cursor () {

port_byte_out ( REG_SCREEN_CTRL , 14);
int offset = port_byte_in(REG_SCREEN_DATA) << 8;
port_byte_out ( REG_SCREEN_CTRL , 15);
offset += port_byte_in ( REG_SCREEN_DATA );

return offset *2;
}

void set_cursor ( int offset ) {
offset /= 2; // Convert from cell offset to char offset .
// This is similar to get_cursor , only now we write
// bytes to those internal device registers .
port_byte_out ( REG_SCREEN_CTRL , 14);
port_byte_out ( REG_SCREEN_DATA , ( unsigned char )( offset >> 8));
port_byte_out ( REG_SCREEN_CTRL , 15);

}

void print_char(char character ,int col , int row , char attribute_byte){

	unsigned char *vidmem = ( unsigned char *) VIDEO_ADDRESS ;
	if(!attribute_byte){
		attribute_byte = WHITE_ON_BLACK;
	}

	int offset;
	if(col >= 0 && row >=0){
		offset = get_screen_offset(col , row );
	}
	else
		offset = get_cursor();

	if(character == '\n'){
		int rows = offset / (2* MAX_COLS );
		offset = get_screen_offset(79 , rows );
	}
	else{
		vidmem[offset] = character;
		vidmem[offset+1]=attribute_byte;
	}

	offset += 2;
	//offset = handle_scrolling( offset );
	set_cursor( offset );
}