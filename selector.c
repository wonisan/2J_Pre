#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define Key_Up 0x48
#define Key_Down 0x50
#define Key_Enter '\r'

int select(char*[], unsigned int);

int main(){
	system("cls");
	char input = 0;
	char cnt = 0;
	char* sel[] = {"One", "Two", "Three", "Four", "Five"};
	char* res = sel[select(sel, 5)];
	printf("You Select: %s", res);
}

int select(char* txt[], unsigned int sel_num){
	char input = 0;
	int cnt = 0;
	while(input != Key_Enter){
		for(int i = 0; i < sel_num; i++){
			if(i == cnt) printf("> ");
			else printf("  ");
			printf("%s\n", txt[i]);
		}
		input = getch();
		system("cls");
		if(input == Key_Up && 0 < cnt){
			cnt --;
		}
		if(input == Key_Down && cnt < sel_num - 1){
			cnt ++;
		}
	}
	return cnt;	
}