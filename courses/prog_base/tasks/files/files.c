void fprocess(const char * pread, const char * pwrite){
	char string[150];
	char * word;
	int i;
	FILE * fr = fopen(pread, "r");
	FILE * fw = fopen(pwrite, "w");
	if (fr == NULL) {
		puts("Error!");
		return EXIT_FAILURE;
	}
	for (i = 0; i < 7; i++){
		fgets(string, 150, fr);
	}
	word = strtok(string, " ");
	if (strlen(word) > 5){
		fputs(word, fw);
	}
	else{
		while (word != NULL)
		{
			word = strtok(NULL, " ");
			if (strlen(word) > 5){
				fputs(word, fw);
				break;
			}
		}
	}
	fclose(fw);
	fclose(fr);
}
