#include <GL/glfw.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char**argv){
	glfwInit();
	glfwDisable(GLFW_AUTO_POLL_EVENTS);
	glfwOpenWindow(512,512,0,0,0,0,0,0,GLFW_WINDOW);
	glOrtho(0,512,512,0,1,-1);
	srand(glfwGetTime());
	struct{short x,y;}tail[7396];
	die:;
	int tlen=1,apx=tail->x=256,apy=tail->y=256,dir=0;
	for(;;){
		glClear(GL_COLOR_BUFFER_BIT);
		int dx=glfwGetKey(GLFW_KEY_RIGHT)-glfwGetKey(GLFW_KEY_LEFT),dy=glfwGetKey(GLFW_KEY_DOWN)-glfwGetKey(GLFW_KEY_UP);
		if(!dx!=!dy){
			int d=dx?1-dx:2-dy;
			if((d&1)!=(dir&1))dir=d;
		}
		memmove(tail+1,tail,(tlen-1)*sizeof(*tail));
		switch(dir){
		case 0:tail->x+=8;
		break;case 1:tail->y+=8;
		break;case 2:tail->x-=8;
		break;case 3:tail->y-=8;
		break;default:__builtin_unreachable();
		}
		if(tail->x&512||tail->y&512)goto die;
		glColor3ub(0,255,0);
		for(int i=0;i<tlen;i++){
			if(i>2&&abs(tail[i].x-tail->x)<12&&abs(tail[i].y-tail->y)<12)goto die;
			glRecti(tail[i].x-8,tail[i].y-8,tail[i].x+8,tail[i].y+8);
			if(abs(tail[i].x-apx)<20&&abs(tail[i].y-apy)<20){
				do apx=rand()&511; while(apx<32||apx>480);
				do apy=rand()&511; while(apx<32||apx>480);
				tail[tlen].x=tail[tlen-1].x;
				tail[tlen].y=tail[tlen-1].y;
				tlen++;
			}
		}
		glColor3ub(255,0,0);
		glRecti(apx-12,apy-12,apx+12,apy+12);
		glfwSwapBuffers();
		glfwSleep(1./60-glfwGetTime());
		glfwSetTime(0);
		glfwPollEvents();
		if(glfwGetKey(GLFW_KEY_ESC)||!glfwGetWindowParam(GLFW_OPENED))return 0;
	}
}