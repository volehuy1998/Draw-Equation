#include <bits/stdc++.h>
#include <SDL2/SDL.h>
using namespace std;

#define PI     3.14
#define WIDTH  1000
#define HEIGHT 600
#define CENTER SDL_WINDOWPOS_CENTERED

SDL_Window   * window   = NULL;
SDL_Renderer * renderer = NULL;
SDL_Event event;

bool isrunning = true;
double angle = 0.0f;
vector<int> points;
int Ox = WIDTH / 2, Oy = HEIGHT / 2; // translate axis

void quit() {
	isrunning = false;
}

void eclipse(int ix, int iy, int r) {
	vector<SDL_Point> circle_point;
	for (double radian = 0; radian < 2 * PI; radian += 0.01) {
		// Trigonometric formula and translate
		int cx = ix + r * cos(radian);
		int cy = iy + r * sin(radian);
		circle_point.emplace_back(SDL_Point{cx, cy});
	}

	for(const auto& point : circle_point) {
		SDL_RenderDrawPoint(renderer, point.x, point.y);
	}
}

int main() {
	SDL_Init(SDL_INIT_EVERYTHING);	
	window = SDL_CreateWindow("SDL2", CENTER, CENTER, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	while (isrunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_q:
							quit();
							break;
					}
			}
		}
		SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
		int xs = 0;
		int ys = 0;
		if (points.size() > 1200) points.erase(points.begin());
		for (int k = 0; k < 5; k++) {
			int prevx = xs;
			int prevy = ys;
			int n = 2 * k + 1;
			int radius = 200 * (4 / (n * PI));
			xs += radius * cos(n * angle);
			ys += radius * sin(n * angle);
			eclipse(Ox + prevx,  Oy + prevy, radius);
			SDL_RenderDrawLine(renderer, Ox + prevx, Oy + prevy, Ox + xs, Oy + ys);
			eclipse(Ox + xs, Oy + ys, 5);
		}
		points.emplace_back(ys);
		SDL_RenderDrawLine(renderer, Ox + xs, Oy + ys, Ox + 250, Oy + points[points.size() - 1]);
		for(int i = 0; i < points.size(); i++) {
			SDL_RenderDrawPoint(renderer, Ox + 250 + points.size() - i, Oy + points[i]);
		}
		
		SDL_RenderPresent(renderer);
		angle += 0.03;
		SDL_Delay(20);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}
