#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Graphics.hpp>
#include <array>
#include "Sound.h"

class Keyboard {
private:
    sf::RenderWindow keyboardWindow;
    Sound piano;

    sf::RectangleShape backgroundImage;
    sf::Texture backgroundTexture;

    std::array<sf::RectangleShape,61> keyboardNotes;
    std::array<sf::Text, 61> keyboardCharacters;

    sf::Font pianoIndexFont;
    sf::Texture whiteKeyTexture;
    sf::Texture whiteKeyTextureDark;
    sf::Texture blackKeyTexture;
    sf::Texture blackKeyTextureLight;
public:
    // Constructor
    Keyboard();

    //potential differing events for default/preset piano simulator options
    //void keyboardEvent(char presetMode);
    //void keyboardEvent(int defaultMode);
    // Events
    void keyboardEvent();

    // Draws each piano note
    void drawKeyboard();

    // detects ASCII character entered
    static int charDetectASCII(int);

    // Draws each piano note
    void runKeyboard();

    // Draw
    void renderWindow();

};

#endif // KEYBOARD_H
