char * get_base_path( char* str ){
	char *token ;
	char blog_path[100] = "/";

	token = strtok(str, "/");
	strcat(blog_path , token);
	while ( (token = strtok(NULL, "/")) != NULL){
		if( strstr(token ,".php") == NULL){
			strcat(blog_path , "/");
			strcat(blog_path , token);
		}   
	}   
	strcat(blog_path , "/");
	return estrndup(blog_path, strlen(blog_path));
}

