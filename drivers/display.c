
# define VIDEO_ADDRESS 0xb8000
# define MAX_ROWS 25
# define MAX_COLS 80
// Attribute byte for our default colour scheme .
# define WHITE_ON_BLACK 0x0f
// Screen device I / O ports
# define REG_SCREEN_CTRL 0x3D4
# define REG_SCREEN_DATA 0x3D5

int CUR_X=0;
int CUR_Y=0;


void update_cursor(int row, int col)
 {
    unsigned short position=(row*80) + col;
 
    // cursor LOW port to vga INDEX register
    port_byte_out(0x3D4, 0x0F);
    port_byte_out(0x3D5, (unsigned char)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    port_byte_out(0x3D4, 0x0E);
    port_byte_out(0x3D5, (unsigned char )((position>>8)&0xFF));
 }

int get_screen_offset(int col , int row){

	CUR_X = row;
	CUR_Y = col;
	return ((row * 80) + col) *2 ;

}

int get_cursor(){
	return ((CUR_X * 80) + CUR_Y ) *2 ;
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
		CUR_Y =0;
		CUR_X++;
		offset = get_screen_offset(CUR_X , CUR_Y );
	}
	else{
		CUR_Y++;
		vidmem[offset] = character;
		vidmem[offset+1]=attribute_byte;
	}

	update_cursor(CUR_X,CUR_Y);
	
}

void clear_screen () {
int row = 0;
int col = 0;
/* Loop through video memory and write blank characters . */
for ( row =0; row < MAX_ROWS ; row++) {
	for ( col =0; col < MAX_COLS ; col++) {
		print_char( ' ' , col , row , WHITE_ON_BLACK );
		}
	}
	CUR_X=CUR_Y=0;
	update_cursor(0,0);
}