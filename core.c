#include "game.h"
#include "libpuyo.h"
#include "orzpcm.h"

#define PGP 12.5f

#define dprogress() \
	ximage_bitblt(__disp,__img,0,0); \
	 \
	ximage_boxnfill(__disp,240-128-4,136-8-2,240+128+3,136+8+2,0xffffff,1); \
	 \
	ximage_boxfill(__disp,240-128-2,136-8,240-128+(pg / 100.0f * 256.0f),136+8,0x802000); \
	 \
	SDL_UpdateRect(sdl_screen,0,0,0,0); \

int main(int argc, char *argv[])
{
	SDL_Event sdl_event;
	SDL_Surface *sdl_screen;
	
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_JOYSTICK|SDL_INIT_AUDIO);
	
	sdl_screen = SDL_SetVideoMode(480,272,32,SDL_SWSURFACE);
	
	SDL_ShowCursor(0);
	
	ximage *__disp = ximage_create(480,272,sdl_screen->pitch >> 2,sdl_screen->pixels);
	
	float pg = 0;
	
	ximage *__img = ximage_load("resource/back.png");
	
	//ximage *__img2 = ximage_load("resource/splash.png");
	
	pg += PGP;
	dprogress();
	
	SDL_Joystick *joy = SDL_JoystickOpen(0);
	
	int fps = 0;
	
	_orzpcm_init();
	
	_orzpcm_chunk ogg[5];
	
	//ximage_bitblt(__disp,__img2,0,0);
	
	//SDL_UpdateRect(sdl_screen,0,0,0,0);
	
	ogg[0] =  _orzpcm_loadfile("resource/game_maoudamashii_1_battle15.wav");
	pg += PGP;
	dprogress();
	
	ogg[1] =  _orzpcm_loadfile("resource/game_maoudamashii_7_event37.wav");
	pg += PGP;
	dprogress();
	
	ogg[2] =  _orzpcm_loadfile("resource/btn07.wav");
	pg += PGP;
	dprogress();
	
	ogg[3] =  _orzpcm_loadfile("resource/btn11.wav");
	pg += PGP;
	dprogress();
	
	ogg[4] =  _orzpcm_loadfile("resource/game_maoudamashii_9_jingle02.wav");
	pg += PGP;
	dprogress();
	
	ximage_init();
	
	ximage_fhndl *tft = ximage_initft("resource/splafont.ttf");
	ximage_textsize(tft,48);
	pg += PGP;
	dprogress();
	
	ximage_fhndl *sft = ximage_initft("resource/ipa-mona/ipag-mona.ttf");
	ximage_textsize(sft,12);
	pg += PGP;
	dprogress();
	
	SDL_Delay(100);
	
	int ftim = SDL_GetTicks();
	
	int hgn;
	FILE *hg = fopen("hg.dat","r+");
	
	fread(&hgn,4,1,hg);
	
	fclose(hg);
	
	char fpss[16];
	fpss[0] = 0;
	
	int tti = _orzpcm_play(ogg[1],1);
	
	while(1) {
		fps_adjust();
		
		ximage_bitblt(__disp,__img,0,0);
		
		ximage_textout(tft,__disp,240+0,106+0,0xffffff,"PACK SLIDE",1);
		
		
		if(fps % 30 < 15) ximage_textout(sft,__disp,240,166,0xffffff,"PRESS START BUTTON",1);
		
		ximage_textout(sft,__disp,240,272-24,0xffffff,"(c)2016 dt650",1);
		ximage_textout(sft,__disp,240,272-24-16,0xffffff,"Powered by SDL and freetype",1);
		
		if(SDL_GetTicks() - ftim >= 1000) {
			sprintf(fpss,"%d fps",fps);
			fps = 0;
			ftim = SDL_GetTicks();
		}
		
		ximage_textout(sft,__disp,2,2,0xffffff,fpss,0);
		
		SDL_UpdateRect(sdl_screen,0,0,0,0);
		
		poll_event(&sdl_event);
		
		if(SDL_JoystickGetButton(joy,11)) break;
		
		fps++;
	}
	
	ximage *__chip[5];
	int i,j;
	
	for(i = 0;i < 5; i++) {
		char f[64];
		sprintf(f,"resource/chip%d.png",i+1);
		__chip[i] = ximage_load(f);
	}
	
	ximage_fhndl *cft = ximage_initft("resource/ipa-mona/ipag-mona.ttf");
	ximage_textsize(cft,9);
	
	ximage_fhndl *nft = ximage_initft("resource/ipa-mona/ipag-mona.ttf");
	ximage_textsize(nft,20);
	
	ftim = SDL_GetTicks();
	fps = 0;
	
	struct FIELD stField;
	
	_orzpcm_stop(tti);

__tnt:
	
	tti = _orzpcm_play(ogg[0],1);

	for(i = 0;i < 12; i++) {
		for(j = 0;j < 12; j++) {
			stField.stBlock[i][j].nColor = rand() % 5 + 1;
			stField.stBlock[i][j].nVanish = 0;
		}
	}
	
	int ny=0;
	
	int kf[] = {1,1,1,1,1,1};
	
	int score = 0;
	int level = 0;
	
	int ltime = 2700;
	
	int vtime = 0;
	
	for(i = 0;i < 90; i++) {
		fps_adjust();
		
		ximage_bitblt(__disp,__img,0,0);
		
		int n = 3 - i / 30;
		
		ximage_textoutf(tft,__disp,240,136,0xffffff,1,"%d",n);
		
		SDL_UpdateRect(sdl_screen,0,0,0,0);
		
		poll_event(&sdl_event);
	}
	
	while(1) {
		fps_adjust();
		
		ximage_bitblt(__disp,__img,0,0);
		
		if(SDL_GetTicks() - ftim >= 1000) {
			sprintf(fpss,"%d fps",fps);
			fps = 0;
			ftim = SDL_GetTicks();
		}
		
		for(i = 0;i < 12; i++) {
			for(j = 0;j < 12; j++) {
				if(stField.stBlock[j][i].nColor != 0) ximage_bitblt(__disp,__chip[stField.stBlock[j][i].nColor - 1],j*16+144,i*16+40);
			}
		}
		
		if(SDL_JoystickGetButton(joy,8)) {
			if(kf[0] == 0) {
				if(ny > 0) ny--;
				kf[0] = 1;
			}
		} else {
			kf[0] = 0;
		}
		
		if(SDL_JoystickGetButton(joy,6)) {
			if(kf[1] == 0) {
				if(ny < 11) ny++;
				kf[1] = 1;
			}
		} else {
			kf[1] = 0;
		}
		
		if(SDL_JoystickGetButton(joy,7)) {
			if(kf[2] == 0) {
				struct BLOCK nl[12];
				for(i = 0; i < 12; i++) {
					int n = i + 1;
					if(n >= 12) n = n - 12;
					nl[i] = stField.stBlock[n][ny];
				}
				for(i = 0; i < 12; i++) {
					stField.stBlock[i][ny] = nl[i];
				}
				kf[2] = 1;
			}
		} else {
			kf[2] = 0;
		}
		
		if(SDL_JoystickGetButton(joy,9)) {
			if(kf[3] == 0) {
				struct BLOCK nl[12];
				for(i = 0; i < 12; i++) {
					int n = i - 1;
					if(n < 0) n = 12 + n;
					nl[i] = stField.stBlock[n][ny];
				}
				for(i = 0; i < 12; i++) {
					stField.stBlock[i][ny] = nl[i];
				}
				kf[3] = 1;
			}
		} else {
			kf[3] = 0;
		}
		
		int ln = 1;
		
		while(Check(&stField) != 0) {
			int n = Vanish(&stField) * 200;
			score += n * ln;
			ln++;
		}
		
		if(ln != 1) _orzpcm_play(ogg[3],0);
		
		if(score > hgn) {
			hgn = score;
			FILE *hg = fopen("hg.dat","r+");
	
			fwrite(&hgn,4,1,hg);
			
			fclose(hg);
		}
		
		Slide(&stField);
		
		if(SDL_JoystickGetButton(joy,11)) {
			if(kf[4] == 0 && vtime == 0) {
				for(i = 0;i < 12; i++) {
					for(j = 0;j < 12; j++) {
						stField.stBlock[i][j].nColor = rand() % 5 + 1;
						stField.stBlock[i][j].nVanish = 0;
					}
				}
				level++;
				vtime = 450;
				kf[4] = 1;
			}
		} else {
			kf[4] = 0;
		}
		
		
		ximage_boxfill(__disp,144,8,144+(int)((float)vtime/450.0*192.0),32,0x802000);
		ximage_textoutf(cft,__disp,240,20,0xffffff,1,"%02d",vtime / 30);
		
		
		ximage_boxnfill(__disp,144-1,40+16*ny,144+192+1,40+16+1+ny*16,(fps % 10 < 5) ? (0xffffff) : (0xffff00),2);
		
		ximage_textout(cft,__disp,2,2,0xffffff,fpss,0);
		
		ximage_textoutf(cft,__disp,2,18,0xffffff,0,"%08d pt",score);
		ximage_textoutf(cft,__disp,2,32,0xffffff,0,"high %08d",hgn);
		ximage_textoutf(cft,__disp,2,50,0xffffff,0,"level %d",level);
		
		int m,s,t;
		
		m = ltime / (30 * 60);
		s = (ltime / 30) % 60;
		t = (ltime % 30) * 3;
		
		int nc = 0x00ff00;
		if(ltime < 1800) nc = 0x00ffff;
		if(ltime < 900) nc = 0x0000ff;
		
		char tts[256];
		tts[0] = 0;
		
		int nc2 = 0x00ff00;
		if(ltime < 1800+30 && ltime > 1800-90) nc = 0x00ffff;
		if(ltime < 900+30 && ltime > 900-90) if(ltime < 900) nc = 0x0000ff;
		
		if(ltime < 1800+30 && ltime > 1800-90) strcpy(tts,"Žc‚è 1•ª");
		if(ltime < 900+30 && ltime > 900-90) strcpy(tts,"Žc‚è 30•b");
		
		if(ltime == 1800+30) _orzpcm_play(ogg[2],0);
		if(ltime == 900+30) _orzpcm_play(ogg[2],0);
		
		if(fps % 30 < 15) {
			for(i = -1; i < 2; i++) {
				for(j = -1; j < 2; j++) {
					ximage_textoutf(sft,__disp,240+i,20+j,0,1,"%s",tts);
				}
			}
			ximage_textoutf(sft,__disp,240,20,nc2,1,"%s",tts);
		}
		
		ximage_textoutf(nft,__disp,345,2,nc,0,"%02d:%02d.%02d",m,s,t);
		
		if(SDL_JoystickGetButton(joy,4) && SDL_JoystickGetButton(joy,5)) {
			if(kf[5] == 0) {
				for(i = -2; i < 3; i++) {
					for(j = -2; j < 3; j++) {
						ximage_textout(sft,__disp,240+j,272-24-16-16-8-16+i,0x000000,"ƒQ[ƒ€‚ð‘±‚¯‚é : Z",1);
						ximage_textout(sft,__disp,240+j,272-24-16-8+2-16 +i,0x000000,"‚â‚è‚È‚¨‚µ : ~",1);
						ximage_textout(sft,__disp,240+j,272-24-16-8+2    +i,0x000000,"ƒQ[ƒ€‚ð‚â‚ß‚é :  ",1);
					}
				}
				
				ximage_textout(sft,__disp,240,272-24-16-16-8-16,0xffffff,"ƒQ[ƒ€‚ð‘±‚¯‚é : Z",1);
				ximage_textout(sft,__disp,240,272-24-16-8+2-16 ,0xffffff,"‚â‚è‚È‚¨‚µ : ~",1);
				ximage_textout(sft,__disp,240,272-24-16-8+2    ,0xffffff,"ƒQ[ƒ€‚ð‚â‚ß‚é :  ",1);
				
				SDL_UpdateRect(sdl_screen,0,0,0,0);
			
				while(1) {
					fps_adjust();
					
					poll_event(&sdl_event);
					
					if(SDL_JoystickGetButton(joy,1)) break;
					if(SDL_JoystickGetButton(joy,2)) {
						_orzpcm_stop(tti);
						goto __tnt;
					}
					if(SDL_JoystickGetButton(joy,3))  {
						SDL_JoystickClose(joy);
						SDL_Quit();
						return 0;
					}
				}
				
				kf[5] = 1;
			}
		} else {
			kf[5] = 0;
		}
		
		if(ltime == 0) {
			int i;
			
			_orzpcm_stop(tti);
			
			_orzpcm_play(ogg[4],0);
			
			ximage_textout(tft,__disp,240,136,0xffffff,"TIME UP",1);
			
			SDL_UpdateRect(sdl_screen,0,0,0,0);
			
			for(i = 0; i < 60; i++) {
				fps_adjust();
				
				poll_event(&sdl_event);
			}
			
			for(i = -2; i < 3; i++) {
				for(j = -2; j < 3; j++) {
					ximage_textout(sft,__disp,240+j,272-24-16-16-8+i,0x000000,"ƒQ[ƒ€‚ð‘±‚¯‚é : START",1);
					ximage_textout(sft,__disp,240+j,272-24-16-8+2 +i,0x000000,"ƒQ[ƒ€‚ð‚â‚ß‚é : SELECT",1);
				}
			}
				
			
			ximage_textout(sft,__disp,240,272-24-16-16-8,0xffffff,"ƒQ[ƒ€‚ð‘±‚¯‚é : START",1);
			ximage_textout(sft,__disp,240,272-24-16-8+2 ,0xffffff,"ƒQ[ƒ€‚ð‚â‚ß‚é : SELECT",1);
			
			SDL_UpdateRect(sdl_screen,0,0,0,0);
			
			while(1) {
				fps_adjust();
				
				poll_event(&sdl_event);
				
				if(SDL_JoystickGetButton(joy,11)) {
					goto __tnt;
				}
				if(SDL_JoystickGetButton(joy,10)) {
					SDL_JoystickClose(joy);
					SDL_Quit();
					return 0;
				}
			}
			
			ltime = 2700;
			
			score = 0;
			
			for(i = 0;i < 12; i++) {
				for(j = 0;j < 12; j++) {
					stField.stBlock[i][j].nColor = rand() % 5 + 1;
					stField.stBlock[i][j].nVanish = 0;
				}
			}
			
			level = 0;
			
			vtime = 0;
			
			kf[4] = 1;
		}
		
		SDL_UpdateRect(sdl_screen,0,0,0,0);
		
		poll_event(&sdl_event);
		
		fps++;
		
		ltime--;
		if(vtime > 0) vtime--;
	}
	
	SDL_JoystickClose(joy);
	
	SDL_Quit();
	
	return 0;
}

void fps_adjust(void)
{
	static unsigned long maetime=0;
	static int frame=0;
	long sleeptime;
	if(!maetime) maetime=SDL_GetTicks();
	frame++;
	sleeptime=(frame<FPS)?
		(maetime+(long)((double)frame*(1000.0/FPS))-SDL_GetTicks()):
		(maetime+1000-SDL_GetTicks());
	if(sleeptime>0)SDL_Delay(sleeptime);
	if(frame>=FPS) {
		frame=0;
		maetime=SDL_GetTicks();
	}
}

void poll_event(SDL_Event *sdl_event)
{
	if(SDL_PollEvent(sdl_event)) {
		switch (sdl_event->type) {
		case SDL_QUIT:
			SDL_Quit();
			exit(0);
		}
	}
}
