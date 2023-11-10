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
   
    // declares vectors to store corrdinates of the triangle
    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Random number generator for vertex selection
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, 2);

    // Load the font for displaying the instructions
    sf::Font font;
    if (!font.loadFromFile("JUICE___.TTF")) 
    {
        cerr << "Font not found boo" << endl;
        return 1;
    }
    // create text object
    sf::Text text;
    // select the font
    text.setFont(font); // font is a sf::Font
    // set the string to display
    text.setString("You want to create a triangle? Yes you do. Now click 3 times on the screen:D");
    // set the character size
    text.setCharacterSize(24); // in pixels, not points!
    // set the color
    text.setFillColor(sf::Color::Blue);
    // set the text style
    text.setStyle(sf::Text::Bold);
    // displays actual text
    window.draw(text);

    while (window.isOpen())
    {
      /*****************************************
	     Handle the players input
      *****************************************/
        // handles SFML window
        sf::Event event;
        // checks for clicks/window closure
        while (window.pollEvent(event))
        {
            // if user closed it
            if (event.type == sf::Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }
            // adding vertices based on mouse click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // left mouse click
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    // checks number of points clicked
                    if (vertices.size() < 3)
                    {
                        // Assign the coordinates of the mouse click to the vertices vector
                        vertices.push_back(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                        // displays that you have put 3 points and ends clicks
                        text.setString("Algorithm  has began. Generating meow...");

                    }
                }
            }
        }
	    
        if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
	   window.close();
	}
        /*****************************************
			  Update
	*****************************************/
        // generating points/midpoint/speed up points
        if (points.size() > 0)
        {
            ///generate more point(s) to speed up
            for (int i = 0; i < 100; i++)
            {
                ///select random vertex
                int randomVertexIndex = distribution(generator);
                ///calculate midpoint between random vertex and the last point in the vector
                // select random vertex from vertices vector
                sf::Vector2f randomVertex = vertices[randomVertexIndex];
                // to calc midpoint
                sf::Vector2f lastPoint = points.back();
                sf::Vector2f newPoint = (randomVertex + lastPoint) / 2.0f;
                ///push back the newly generated coord.
                points.push_back(newPoint);
            }
        }
	    
        // clear the window to erase what was drawn previously on the screen
        window.clear();
	    
        /*****************************************
			  Draw
	*****************************************/
        // iterates through vertices as triangles
        for (int i = 0; i < vertices.size(); i++)
        {
            // create SFML built in class object
            sf::RectangleShape rect(Vector2f(10, 10));
            // set to current vertix in vector
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            // set color
            rect.setFillColor(sf::Color::White);
            // draw it
            window.draw(rect);
        }

        // iterates through the points vector as circles
        for (int i = 0; i < points.size(); i++)
        {
            // create SFML built in classs object with radius of 2 pixels
            CircleShape point(2);
            // set object to vector of points
            point.setPosition(points[i]);
            // fill to a certain color
            point.setFillColor(Color::Cyan);
            // use RenderWindow object to display
            window.draw(point);
        }

        // Display instructions
        window.draw(text);
        window.display();    
    }
}
