#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

int main(int argc, char **argv)
{
	//Variables
	ALLEGRO_DISPLAY *settingsDisplay = NULL;
	ALLEGRO_DISPLAY *mainDisplay = NULL;
	ALLEGRO_FONT *mainFont = NULL;
	ALLEGRO_EVENT_QUEUE *mainEventQueue = NULL;
	ALLEGRO_USTR *promptString = al_ustr_new("Hello World");
	bool quit = false;

	//Main function Code
	if (!al_init() && !al_init_font_addon() && !al_install_keyboard()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}
	if (!al_init_font_addon()) {
		fprintf(stderr, "failed to initialize the font addon!\n");
		return -1;
	}
	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	settingsDisplay = al_create_display(1280, 720);
	if (!settingsDisplay) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	mainFont = al_create_builtin_font();

	mainEventQueue = al_create_event_queue();
	al_register_event_source(mainEventQueue, al_get_display_event_source(settingsDisplay));
	al_register_event_source(mainEventQueue, al_get_keyboard_event_source());
	

		
	while (!quit) {
		al_clear_to_color(al_map_rgb_f(60, 63, 66));
		al_draw_ustr(mainFont,
			al_map_rgb_f(1, 1, 1 ),
			al_get_display_width(settingsDisplay)/2,
			al_get_display_height(settingsDisplay)/2,
			ALLEGRO_ALIGN_CENTRE,
			promptString);
		al_flip_display();

		ALLEGRO_EVENT event;
		al_wait_for_event(mainEventQueue, &event);
		switch (event.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			quit = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				quit = true;
				break;
			}
		}
	}

	return 0;
}
