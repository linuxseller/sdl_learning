#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define WIN_NUMBER 4
#define PICTURE_NAME "anime.png"

typedef struct Vector2 {
    int x;
    int y;
} Vector2;

typedef struct MyWindow {
    Vector2 vel;
    Vector2 size;
    Vector2 pos;
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Texture *texture;
    SDL_Rect src_rec;
    SDL_Rect dst_rec;
} MyWindow;

#define CHECK(a) { \
    if(a<0) {printf("ERRORRORO\n");exit(1);} \
}
int main(int argc, char *argv[]){
    (void) argc;
    (void) argv;
    srand(1);
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
    CHECK(IMG_Init(IMG_INIT_PNG));
    SDL_Surface *image = IMG_Load(argv[1]);
    if(image==NULL){
        exit(1);
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(1, &DM);
    int screenX = DM.w;
    int screenY = DM.h;
    printf("screen %dx%d\n", screenX, screenY);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    MyWindow *my_windows = malloc(WIN_NUMBER*sizeof(MyWindow));
    for(int i=0; i<WIN_NUMBER; i++){
        char *windowname = malloc(100);
        sprintf(windowname, "win %d", i+1);
        SDL_Window *win = SDL_CreateWindow(windowname, 0,0,100,100, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, image);
        if(win==NULL || rend==NULL || texture==NULL){exit(1);}
        my_windows[i] = (MyWindow){ .vel = {rand()%30,rand()%30}, .size={100, 100}, .pos={rand()%(-200+screenX), rand()%(-200+screenY)}, .win=win, .rend=rend, .texture=texture};
    }
	int close = 0;
	while (!close) {
        SDL_Event event;
        for(int i=0; i<WIN_NUMBER; i++){
            MyWindow *curw   = &my_windows[i];
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    close = 1;
                    break;
                }
            }

            /* if (curw->pos.x + curw->size.x + curw->vel.x > screenX || curw->pos.x + curw->vel.x < 0) { */
            /*     curw->vel.x = -curw->vel.x; */
            /*     curw->pos.x = (curw->pos.x + curw->vel.x < 0) ? 0 : (screenX - curw->size.x); */
            /* } */

            /* if (curw->pos.y + curw->size.y + curw->vel.y > screenY || curw->pos.y + curw->vel.y < 0) { */
            /*     curw->vel.y = -curw->vel.y; */
            /*     curw->pos.y = (curw->pos.y + curw->vel.y < 0) ? 0 : (screenY - curw->size.y); */
            /* } */
            /* curw->pos.x+=curw->vel.x; */
            /* curw->pos.y+=curw->vel.y; */
            /* SDL_SetWindowPosition(curw->win, curw->pos.x, curw->pos.y); */
            SDL_GetWindowSize(curw->win, &curw->size.x, &curw->size.y);
            SDL_GetWindowPosition(curw->win, &curw->pos.x, &curw->pos.y);
            SDL_RenderClear(curw->rend);
            curw->src_rec = (SDL_Rect){curw->pos.x, curw->pos.y, curw->size.x, curw->size.y};
            curw->dst_rec = (SDL_Rect){0,0,curw->size.x, curw->size.y};
            SDL_RenderCopy(curw->rend, curw->texture, &curw->src_rec, &curw->dst_rec);
            SDL_RenderPresent(curw->rend);
        }
        SDL_Delay(1000 / 30);
	}
	/* SDL_DestroyRenderer(rend); */

    for(int i=0; i<WIN_NUMBER; i++){
        SDL_DestroyWindow(my_windows[i].win);
    }
	SDL_Quit();

	return 0;
}

