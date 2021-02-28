#include "music.h"
#include<windows.h>
#pragma comment(lib, "Winmm.lib")
void BGM(){
	mciSendString("open music\\BGM.mp3 alias mymusic", NULL, 0, NULL);  
	mciSendString("play mymusic repeat",NULL,0,NULL);
} 
