#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>

struct pointers {
	char *pointer;
	int length;
};

struct result {
	struct pointers version;
	struct pointers code;
	struct pointers description;
	bool worked;
};

struct result parse_http(char *str, int length){

	bool space1 = false;
	bool space2 = false;
	int space1_pos = 0;

	struct result res ;


	for (int i = 0; i <= length ; i++){

		if (space1 == false) {
			if (str[i] == ' ') {
				space1 = true;
				//Copy our data as i cant work out how to pass back a pointer and lenght.
				res.version.pointer = str;
				res.version.length = i;
				space1_pos = i;
			}
		}
		else if (space2 == false) {
			if (str[i] == ' '){
				space2 = true;
				res.code.pointer = str + space1_pos+ 1;
				res.code.length = i - space1_pos -1;
				res.description.pointer = str + i + 1;  
				res.description.length = length - i -1;
			}
		}
	}
	return res;
}

void printer(char *pointer, int length){
	if (length == 0) {
		return;
	}
	if (pointer == NULL){
		return;
	}
	for(int i=0; i < length;i++){
		printf("%c",*pointer);
		pointer++;
	}
	printf("\n");
}

int main(){
	char str[] = "HTTP/1.1 418 I'm a teapot\r\n";
	int length = sizeof(str);

	struct timeval stop, start;
	gettimeofday(&start, NULL);
	struct result res;

	for (int i= 0; i < 100000000; i++){
		res = parse_http(str,length);
	}

	gettimeofday(&stop, NULL);
	printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

	printer(res.version.pointer,res.version.length);
	printer(res.code.pointer,res.code.length);
	printer(res.description.pointer,res.description.length);

	return 0;

}
