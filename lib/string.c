
char* inttostring(int num){

	int q,r;
	char string[6];
	int count =0;
	while(num != 0){
		r = num % 10;
		q = num / 10 ;
		string[count++] = '0'+r;
		num = q;
	}
	string[count] ='\0';
	return string;
}


void strreverse(char *msg){
	int i,j;
	int len = strlen(msg);
	char c;
	for(i=0,j=len-1;i<len/2;i++,j--){
		c=msg[i];
		msg[i] = msg[j];
		msg[i]=c;		
	}
	//return msg;
}

int strcmp(char* m1,char* m2){

	int len1 = strlen(m1);
	int len2 = strlen(m2);
	int i=0;
	if(len1!=len2)
		return -1;

	for(i=0;i<len1;i++){
		if(m1[i]!=m2[i])
			return -1;
	}
	 return 0;
}