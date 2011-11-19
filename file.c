
char * peblog_file_contents(char * file){

		FILE *fp;
		char *content ;

		int i = 0;
		fp = fopen(file, "r");
		if(fp == NULL){
			return "File is not exists.";
		}
		fseek(fp, 0, SEEK_END);

		i = ftell(fp);

		content = (char *) emalloc( i + 1);
		memset(content, 0, i + 1);

		fseek(fp, 0, SEEK_SET);
		fread(content , 1, i, fp);
		fclose(fp);


		return content;


}
