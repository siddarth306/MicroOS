void help()
{
	print("Hi");
}

void clear()
{
	clear_screen();

}

void main()
{
	char *video_memory = (char*)0xb8000 ;
	*video_memory = 'y';
	clear_screen();
	gdt_install();
	print("Hello World\n");
	help();
	
}
