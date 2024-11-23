#include "keyboard.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <fstream>

// Constructor definition
Keyboard::Keyboard() : keyboardWindow(sf::VideoMode(1920, 1200), "Keyboard Window") {
    keyboardWindow.setFramerateLimit(60);
    for(int pianoIter=0; pianoIter<7; pianoIter++) {
        std::string name = "../assets/sounds/a" + std::to_string(pianoIter+1) + ".mp3";
        // std::ifstream file(name);
        pianoBuffer[pianoIter].loadFromFile(name);
        pianoSound[pianoIter].setBuffer(pianoBuffer[pianoIter]);
    }

    //loads jpg image from computer (change filepath as needed)
    backgroundTexture.loadFromFile("../assets/textures/beigeBackground.jpg");
    backgroundImage.setTexture(&backgroundTexture);
    backgroundImage.setSize(sf::Vector2f(1920,1200));
    //loads in gradient for white and black key textures (change filepath as needed)
    whiteKeyTexture.loadFromFile("../assets/textures/beigeToWhite.jpg");

    // blackKeyTexture.loadFromFile(" ");
    //WHITE KEYS INITIALIZED BELOW
    float xPositionWhiteKeys = 0;
    float yPositionWhiteKeys = 700;
    for(int iter = 0; iter < 36; iter++)
    {
        keyboardNotes[iter].setPosition(xPositionWhiteKeys,yPositionWhiteKeys);
        keyboardNotes[iter].setSize(sf::Vector2f(66.6,400));
        // keyboardNotes[iter].setFillColor(sf::Color::White);
        keyboardNotes[iter].setOutlineThickness(2);
        keyboardNotes[iter].setOutlineColor(sf::Color::Black);
        keyboardNotes[iter].setTexture(&whiteKeyTexture);
        xPositionWhiteKeys += 66.6;
    }
    //BLACK KEYS INITIALIZED BELOW
    float xPositionBlackKeys = 45.3;
    float yPositionBlackKeys = 700;
    std::set<int> xPositionSkip = {38,41,43,46,48,51,53,56,58};
    for(int iterator = 36; iterator < 61; iterator++)
    {
        if(xPositionSkip.find(iterator) != xPositionSkip.end())
        {
            xPositionBlackKeys += 66.6;
        }
        keyboardNotes[iterator].setPosition(xPositionBlackKeys,yPositionBlackKeys);
        keyboardNotes[iterator].setSize(sf::Vector2f(40,200));
        keyboardNotes[iterator].setFillColor(sf::Color::Black);
        keyboardNotes[iterator].setOutlineThickness(2);
        keyboardNotes[iterator].setOutlineColor(sf::Color::Black);
        // keyboardNotes[iterator].setTexture(&blackKeyTexture);
        xPositionBlackKeys += 66.6;
    }
}

void Keyboard::keyboardEvent() {//test for events
    sf::Event events;
    while (keyboardWindow.pollEvent(events)) {
        if(events.type == sf::Event::KeyPressed) {
            switch(events.key.code) {
                case sf::Keyboard::Escape: {
                    keyboardWindow.close();
                    break;
                }
                case sf::Keyboard::A: {
                    pianoSound[0].play();
                    std::cout<< "A\n";
                    break;
                }
                case sf::Keyboard::S: {
                    pianoSound[1].play();
                    std::cout<< "S\n";
                    break;
                }
                case sf::Keyboard::D: {
                    pianoSound[2].play();
                    std::cout<< "D\n";
                    break;
                }
                case sf::Keyboard::F: {
                    pianoSound[3].play();
                    std::cout<< "F\n";
                    break;
                }
                case sf::Keyboard::G: {
                    pianoSound[4].play();
                    std::cout<< "G\n";
                    break;
                }
                case sf::Keyboard::H: {
                    pianoSound[5].play();
                    std::cout<< "H\n";
                    break;
                }
                case sf::Keyboard::J: {
                    pianoSound[6].play();
                    std::cout<< "J\n";
                    break;
                }
                case sf::Keyboard::K: {
                    // pianoSound[7].play();
                    std::cout<< "K\n";
                    break;
                }
                case sf::Keyboard::L: {
                    // pianoSound[8].play();
                    std::cout<< "L\n";
                    break;
                }

            }
        }
    }
}

int Keyboard::charDetectASCII(int unicodeDetect)
{
    std::unordered_map<int, int> unicodeIndexMap =
            {
                    //WHITE KEYS ASCII TO PIANO INDEX
                    //0-9 nums
                    {48,9},{49,0}, {50,1}, {51,2},{52,3},{53,4},{54,5},{55,6},{56,7},{57,8},
                    //lower q-p char
                    {113,10},{119,11},{101,12},{114,13},{116,14},{121,15},{117,16},{105,17},{111,18},{112,19},
                    //lower a-l char
                    {97,20},{115,21},{100,22},{102,23},{103,24},{104,25},{106,26},{107,27},{108,28},
                    //lower z-m char
                    {122,29},{120,30},{99,31},{118,32},{98,33},{110,34},{109,35},

                    //BLACK KEYS ASCII TO PIANO INDEX
                    // @# %^& ()
                    {64,36},{35,37},{37,38},{94,39},{38,40},{40,41},{41,42},
                    // QWE TY IOP
                    {81,43},{87,44},{69,45},{84,46},{89,47},{73,48},{79,49},{80,50},
                    // SD GHJ LZ
                    {83,51},{68,52},{71,53},{72,54},{74,55},{76,56},{90,57},
                    //CVB
                    {67,58},{86,59},{66,60}
            };

    //general template for detection
    if(unicodeIndexMap.find(unicodeDetect) != unicodeIndexMap.end())
    {
        return unicodeIndexMap[unicodeDetect];
    }
    else
        return -1;
}

void Keyboard::drawKeyboard() {
    keyboardWindow.draw(backgroundImage);
    for(int iterate = 0; iterate < 61; iterate++)
    {
        keyboardWindow.draw(keyboardNotes[iterate]);
    }
}

void Keyboard::renderWindow() {
    keyboardWindow.clear();

    drawKeyboard();

    keyboardWindow.display();
}

void Keyboard::runKeyboard() {
    while (keyboardWindow.isOpen()) {
        keyboardEvent();  // Handles events (keyboard, mouse)
        renderWindow();   // clear and draw
    }
}
// SFML has internal events, which are stored somewhere. The object named events we created stores the events that come from the pollEvent function,
// which continuously checks for events in order. Now, the object events of type sf::Event contains data that we can compare to our existing items,
// such as Close, Escape, or KeyboardPressed
