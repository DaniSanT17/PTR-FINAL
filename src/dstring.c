/*
	Implementação da ADT Dynamic String
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#include "dstring.h"


DString *dstring_create(char *string){
	DString *dstr = malloc(sizeof(DString));
	int size=0;
	while(string[size]){
		size++;
	}
	dstr->strBuff = string;
	dstr->size = size;

	return dstr;
};

void dstring_add_buffer(DString *str, char *string){
	if(str && str->strBuff && string){
		for(int i=0;i<str->size;i++){
			if(!string[i]){
				break;
			}
			str->strBuff[i] = string[i];
		}
	}
};

int dstring_size(DString *string){
	return string->size;
}

DString *dstring_from_int(int size){
	DString *dstr = malloc(sizeof(DString));
	dstr->strBuff = malloc(sizeof(char)*size);
	dstr->size = size;
	
	return dstr;
}

DString *dstring_from_char(char c){
	DString *dstr = malloc(sizeof(DString));
	dstr->strBuff = malloc(sizeof(char));
	dstr->strBuff[0] = c;
	dstr->size = 1;
	
	return dstr;
}

DString *dstring_from_double(double size){
	DString *dstr = malloc(sizeof(DString));
	dstr->size = size;
	dstr->strBuff = malloc(sizeof(char)*dstr->size);
	
	return dstr;
}
DString *dstring_from_float(float size){
	DString *dstr = malloc(sizeof(DString));
	dstr->size = size;
	dstr->strBuff = malloc(sizeof(char)*dstr->size);
	
	return dstr;
}
DString *dstring_from_long(int long size){
	DString *dstr = malloc(sizeof(DString));
	dstr->size = size;
	dstr->strBuff = malloc(sizeof(char)*dstr->size);
	
	return dstr;
}

DString *dstring_from_dstring(DString *string){
	DString *str = malloc(sizeof(DString));
	str->strBuff = malloc(sizeof(char)*string->size);
	str->size = string->size;

	for(int i=0;i<str->size;i++) {
		if(!string->strBuff[i]){
			break;
		}
		str->strBuff[i] = string->strBuff[i];
	}
	return str;
}

DString *dstring_concat(DString *string1, DString *string2){
	DString *str = malloc(sizeof(DString));
	str->strBuff = malloc(sizeof(char)*(string1->size+string2->size));
	str->size = string1->size+string2->size;
	int i=0,j;
	while((string1->strBuff[i]) && i<string1->size){
		str->strBuff[i] = string1->strBuff[i];
		i++;
	}
	j=i;
	while((string2->strBuff[i-j]) && i<str->size){
		str->strBuff[i] = string2->strBuff[i-j];
		i++;
	}

	return str;
}

void print_buffer(DString *str){
	if(!str->strBuff[0]){
		printf("Buffer sem valor definido.");
	}else{
		printf("%c", str->strBuff[0]);
	}
	for(int i=1;i<str->size;i++){
		if(!str->strBuff[i]){
			break;
		}
		printf(" %c", str->strBuff[i]);
	}
	printf("\n");
}

char *dstring_buffer(DString *string){
	return string->strBuff;
}

void free_dstring(DString *str){
	free(str->strBuff);
	str->size = 0;
}


