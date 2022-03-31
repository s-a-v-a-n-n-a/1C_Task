#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>

#include "Visualisation/sfml_drawing/screen_functions.hpp"
#include "Visualisation/sfml_drawing/Renderer.hpp"
#include "Game.hpp"

class Application;

class Application_destroyer
{
private:
	Application *app;

public:
	~Application_destroyer();

	void initialize(Application *par_application);
};

class Application
{
private:
	static Application *app;
	static Application_destroyer destroyer;

    Game *game;

protected:
	Application();
	friend class Application_destroyer;

public:
	Renderer *renderer;
	Screen_information *graphics_wrapper;

	~Application();
	static Application *get_app();

	Game *get_game();
	Renderer *get_renderer();

    void welcome();
    Checker_color get_information();
    void goodbye();

	void draw();
	void tick();

	void launch();
};
#endif // APPLICATION_HPP
