// Updated one:
// sf:: prevents name conflicts
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080); // window size
	// Create and open a window for the game
	RenderWindow window(vm, "Sierpinski Triangle yayy", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

   // Random number generator for vertex selection
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 2);

    // Load the font for displaying the instructions
    	Font font;
    	if (!font.loadFromFile("arial.ttf")) {
        cerr << "Font not found boo" << endl;
        return 1;
    	}
    	sf::Text text;
	// select the font
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString("Let the triangle begin...click on the screen to create vertices of the triangle!");
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	// set the color
	text.setFillColor(sf::Color::Blue);
	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	// inside the main loop, between window.clear() and window.display()
	window.draw(text);

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
		// Quit the game when the window is closed
		window.close();
            }

	    // adding vertices
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        // Assign the coordinates of the mouse click to the vertices vector
			vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
			points.push_back(Vector2f(event.mouseButtom.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/
	// generating points/speed up points
        if(points.size() > 0)
        {
            ///generate more point(s)
	    for (int i = 0; i < 100; i++)
	    {
            	///select random vertex
		int randomVertex = distribution(generator);
            	///calculate midpoint between random vertex and the last point in the vector
		Vector2f midpoint = (vertices[randoomVertex] + points.back()) / 2.0f;
           	///push back the newly generated coord.
		points.push_back(midpoint);
        }

        /*
		****************************************
		Draw
		****************************************
		*/
	// clear the window
        window.clear();

	// draw vertices as triangles
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }
        window.display();
    }
}
