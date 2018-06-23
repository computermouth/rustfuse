
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
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
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	
	if(!window->sdl_renderer) {
		fprintf( stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	
	window->sdl_texture = SDL_CreateTexture( window->sdl_renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width, height);

	if(!window->sdl_texture) {
		fprintf( stderr, "Screen texture could not be created! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	
	SDL_SetTextureBlendMode(window->sdl_texture, SDL_BLENDMODE_BLEND);

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
	
	int rc = 0;
	
	// draw
		
	rc += SDL_SetRenderTarget(window->sdl_renderer, NULL);
	
	rc += SDL_RenderCopy( window->sdl_renderer, window->sdl_texture, NULL, NULL );
	
	// returns void
	SDL_RenderPresent( window->sdl_renderer );
	
	rc += SDL_SetRenderTarget(window->sdl_renderer, window->sdl_texture);
	
	rc += clear_buffer();
	
	return rc;
}

int draw_point(uint16_t x, uint16_t y){
	return SDL_RenderDrawPoint(window->sdl_renderer, x, y);
}

int draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
	return SDL_RenderDrawLine(window->sdl_renderer, x1, y1, x2, y2);
}

int set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
	return SDL_SetRenderDrawColor(window->sdl_renderer, r, g, b, a);
}

/*

int main( int argc, char * argv[] ) {
	
	if(init("Pixarray", 1280, 720)) {
		printf("Closing..\n");
		return 1;
	}
	
	float c1_angle = 0;
	int c1_x_origin = 639;
	int c1_y_origin = 100;
	int c1_radius = 30;
	
	
	float c2_angle = 0;
	int c2_x_origin = 639;
	int c2_y_origin = 500;
	int c2_radius = 100;
	
	for(int i = 0; i < 5000; i++){
		
		for(int j = 0; j < 10; j++){
			set_color(i , i * 2 , i * 3, 255 - (j * 42));
			
			c1_angle = (  i + (j * 5)          % 360 ) * 3.14159 / 180;
			c2_angle = ( (i + ( j * 5 ) + 180) % 360 ) * 3.14159 / 180;
			
			int x1 = c1_x_origin + c1_radius * cos(c1_angle);
			int y1 = c1_y_origin + c1_radius * sin(c1_angle);
			
			int x2 = c2_x_origin + c2_radius * cos(c2_angle);
			int y2 = c2_y_origin + c2_radius * sin(c2_angle);
			
			draw_line(x1, y1, x2, y2);
		}
				
		update_buffer();
		
	}
	
	destroy();
	
	return 0;
}

*/
