
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <SDL2/SDL.h>

typedef struct{
	SDL_Window* sdl_window;
	SDL_Renderer* sdl_renderer;
	SDL_Texture* sdl_texture;
} window_t;

window_t *window = NULL;

int init(char * title, uint16_t width, uint16_t height) {
	
	window = ( window_t* ) calloc( 1, sizeof( window_t ) );
	
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		fprintf( stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	
	window->sdl_window = SDL_CreateWindow( title,
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								width, height, 
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	
	if(!window->sdl_window) {
		fprintf( stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	window->sdl_renderer = SDL_CreateRenderer( window->sdl_window, -1,
		SDL_RENDERER_ACCELERATED );
	
	
	if(!window->sdl_renderer) {
		fprintf( stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	
	window->sdl_texture = SDL_CreateTexture( window->sdl_renderer,
		SDL_PIXELFORMAT_BGR888,
		SDL_TEXTUREACCESS_TARGET,
		width, height);

	if(!window->sdl_texture) {
		fprintf( stderr, "Screen texture could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}

	SDL_RenderClear( window->sdl_renderer );
	
	SDL_SetRenderTarget(window->sdl_renderer, window->sdl_texture);

	return 0;
}

int clear_buffer(){
	if(!window) {
		fprintf( stderr, "Non-existent window\n" );
		return -1;
	}
	
	SDL_SetRenderDrawColor(window->sdl_renderer, 0, 0, 0, 255);
	
	// clear texture
	SDL_RenderClear( window->sdl_renderer );
	
	// clear renderer
	SDL_SetRenderTarget(window->sdl_renderer, NULL);
	SDL_RenderClear(window->sdl_renderer);
	
	// draw to texture
	SDL_SetRenderTarget(window->sdl_renderer, window->sdl_texture);
	
	return 0;

}

int destroy() {
	if(!window) {
		fprintf( stderr, "Non-existent window\n" );
		return -1;
	}

	if(window->sdl_texture) SDL_DestroyTexture( window->sdl_texture );
	if(window->sdl_renderer) SDL_DestroyRenderer( window->sdl_renderer );
	if(window->sdl_window) SDL_DestroyWindow( window->sdl_window );
	free(window);
	
	SDL_Quit();

	return 0;
}

int a = 0;

int update_buffer() {
	if(!window) {
		fprintf( stderr, "Non-existent window\n" );
		return -1;
	}
		
	// draw
		
	SDL_SetRenderTarget(window->sdl_renderer, NULL);
	
	SDL_RenderCopy( window->sdl_renderer, window->sdl_texture, NULL, NULL );
	SDL_RenderPresent( window->sdl_renderer );
	
	SDL_SetRenderTarget(window->sdl_renderer, window->sdl_texture);
	
	clear_buffer();
	
	//~ if( a < 500){
		//~ a++;
	//~ } else {
		//~ destroy();
	//~ }
	
	return 0;
}

int draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
	SDL_RenderDrawLine(window->sdl_renderer, x1, y1, x2, y2);
	return 0;
}

int set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	SDL_SetRenderDrawColor(window->sdl_renderer, r, g, b, a);
	return 0;
}

/*

int main( int argc, char * argv[] ) {
	
	if(init("Pixarray", 1280, 720)) {
		printf("Closing..\n");
		return 1;
	}
	
	//~ while( 1 ) {
			
	set_color(125, 125, 125, 255);
	draw_line(0, 0, 200, 200);
		
	update_buffer();
	destroy();
	//~ }
	
	return 0;
}

*/
