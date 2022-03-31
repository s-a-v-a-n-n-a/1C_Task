#include "Application.hpp"

Application *Application::app = nullptr;
Application_destroyer Application::destroyer;

Application::Application()
{
    app = this;

    renderer = new Renderer();
    graphics_wrapper = new Screen_information(800, 800);
    welcome();
}

Application::~Application()
{
    delete game;
	delete graphics_wrapper;

    goodbye();
}

Application *Application::get_app()
{
	if (app == nullptr)
	{
		new Application();
		destroyer.initialize(app);
	}

	return app;
}

Game *Application::get_game()
{
    return game;
}

Renderer *Application::get_renderer()
{
    return renderer;
}

void Application::welcome()
{
    printf("> Hello user!\n");
    printf("> It is checkers game. Please, enter color of checkers you want to play for:\n");
}

Checker_color Application::get_information()
{
    Checker_color color = WHITE;

    std::string answer = {};
    bool correct = false;
    do
    {
        std::cin >> answer;
        if (answer == "white" || answer == "White" || answer == "WHITE" || answer == "w" || answer == "W") 
        {
            color = WHITE;
            break;
        }

        if (answer == "black" || answer == "Black" || answer == "BLACK" || answer == "b" || answer == "B") 
        {
            color = BLACK;
            break;
        }

        printf("> Sorry, I don't know such color. Please, choose WHITE or BLACK.\n");
    } while (!correct);

    printf("> Thank you! The game is starting. Good luck!\n");

    return color;
}

void Application::goodbye()
{
    printf("> Thank you for the game!\n");
    printf("> See you soon. Goodbye!\n");
}

void Application::draw()
{
	game->draw(graphics_wrapper);
}

void Application::launch()
{
    Checker_color color = get_information();
    
    game = new Game(color);
    game->start();

    bool open = true;
    // Event result = { Event_type::NO_EVENT, 0, 0 };
    while (graphics_wrapper->window.isOpen())
    {
        // Process events
        sf::Event event;
        while (graphics_wrapper->window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                graphics_wrapper->window.close();
        }

        graphics_wrapper->reset();
                
        game->make_move();

        // tick();
        draw();
        
        graphics_wrapper->window.display();

        if (game->is_ended())
        {
            break;
        }
    }

}


Application_destroyer::~Application_destroyer() 
{ 
    delete app; 
}

void Application_destroyer::initialize(Application *par_app) 
{ 
	app = par_app; 
}

