void main()
{
	char *video_memory = (char*)0xb8000 ;
	*video_memory = 'X';
	print_char('H',0 ,0 ,0x0f );

}
