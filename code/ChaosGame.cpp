/*
11/14/23
- Added ability to generate squares and pentagons
- Changed the pixel width and # of iterations

11/10/23
- Fixed background so the picture sizes properly on all interfaces
- Deleted some of the "sf::" parts where it was not needed since we are using namespace sf
- Changed lines 162 and 174 from int i to long long int i to get rid of warnings when using the makefile
*/
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
    RenderWindow window(vm, "Sierpinski CaT-riangle", Style::Default);
   
    // declares vectors to store cordinates of the triangle
    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Random number generator for vertex selection
    default_random_engine generator;

    // Load background texture
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("cat.jfif")) 
    {
      cerr << "Failed to load background image" << endl;
      return 1;
    }

    // create a SMFL sprite object for the background
    Sprite background;
    background.setTexture(backgroundTexture);

    //setting up background so the picture is sized properly
    float windowSizeX = (float) window.getSize().x;
    float windowSizeY = (float) window.getSize().y;
    float bgtSizeX = backgroundTexture.getSize().x;
    float bgtSizeY = backgroundTexture.getSize().y;
    background.setScale(windowSizeX / bgtSizeX, windowSizeY / bgtSizeY );

    // Load the font for displaying the instructions
    Font font;
    if (!font.loadFromFile("JUICE___.TTF")) 
    {
        cerr << "Font not found boo" << endl;
        return 1;
    }

    // create text object
    Text text;
    // select the font
    text.setFont(font); // font is a sf::Font
    // set the string to display
    text.setString("You want to create a fractal? Yes you do. Enter T for a triangle, S for a square, or P for a pentagon :D");
    // set the character size
    text.setCharacterSize(36); // in pixels, not points!
    // set the color
    text.setFillColor(Color::Blue);
    // set the text style
    text.setStyle(Text::Bold);
    // displays actual text
    window.draw(text);

    //holds # of sides for the fractal
    long unsigned int sides = 0;

    while (window.isOpen())
    {

      /*****************************************
	    Handle the players input
      *****************************************/

        // handles SFML window
        Event event;

        // checks for clicks/window closure
        while (window.pollEvent(event))
        {
            // if user closed it
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
            {
                sides = 3;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                sides = 4;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
            {
                sides = 5;
            }

                // adding vertices based on mouse click
                if (event.type == Event::MouseButtonPressed)
                {
                    // left mouse click
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        cout << "the left button was pressed" << endl;
                        cout << "mouse x: " << event.mouseButton.x << endl;
                        cout << "mouse y: " << event.mouseButton.y << endl;

                        // checks number of points clicked
                        if (vertices.size() < sides)
                        {
                            // Assign the coordinates of the mouse click to the vertices vector
                            vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        }
                        else if (points.size() == 0)
                        {
                            ///fourth click
                            ///push back to points vector
                            points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                            // displays that you have put 3 points and ends clicks
                            text.setString("Algorithm  has began. Generating meow...");

                        }
                    }
                }

            //event while loop ends here
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
            int prev = 0;
            uniform_int_distribution<int> distribution(0, sides - 1);
            ///generate more point(s) to speed up
            for (int i = 0; i < 1000; i++)
            {
                //For triangle:
                if (sides == 3)///select random vertex
                {
                    int randomVertexIndex = distribution(generator);
                    ///calculate midpoint between random vertex and the last point in the vector
                    // select random vertex from vertices vector
                    Vector2f randomVertex = vertices[randomVertexIndex];
                    // to calc midpoint
                    Vector2f lastPoint = points.back();
                    Vector2f newPoint = (randomVertex + lastPoint) / 2.0f;
                    ///push back the newly generated coord.
                    points.push_back(newPoint);
                }
                else
                {
		    // prevent the same index consecutively	
                    int randomVertexIndex = distribution(generator);
                    
                    while (randomVertexIndex == prev)
                    {
                        randomVertexIndex = distribution(generator);
                    }
                    // select random vertex from vertices vector
                    Vector2f randomVertex = vertices[randomVertexIndex];
                    // to calc midpoint
                    Vector2f lastPoint = points.back();
                    Vector2f newPoint = (randomVertex + lastPoint) / 2.0f;
                    ///push back the newly generated coord.
                    points.push_back(newPoint);
                    prev = randomVertexIndex;
                }
            }
        }
	    
        // clear the window to erase what was drawn previously on the screen
        window.clear();

	// draw background
        window.draw(background);   

        /*****************************************
			  Draw
	    *****************************************/

        // iterates through vertices as triangles
        for (long unsigned int i = 0; i < vertices.size(); i++)
        {
            // create SFML built in class object
            RectangleShape rect(Vector2f(10, 10));
            // set to current vertix in vector
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            // set color
            rect.setFillColor(Color::Red);
            // draw it
            window.draw(rect);
        }

        // iterates through the points vector as circles
        for (long unsigned int i = 0; i < points.size(); i++)
        {
            // create SFML built in classs object with radius of 2 pixels
            CircleShape point(.5);
            // set object to vector of points
            point.setPosition(points[i]);
            // fill to a certain color
            point.setFillColor(Color::Blue);
            // use RenderWindow object to display
            window.draw(point);
        }

        // Display instructions
        window.draw(text);
        window.display();

        ////////////////////////////////////////////////////////////////////////
 

        //Intial window while loop ends here
    }

    return 0;
}
