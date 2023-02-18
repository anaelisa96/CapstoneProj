#include "welcomeScreen.h"

void WelcomeScreen::PositionElement(){
    int elementWidth, elementHeight = 0;
    SDL_QueryTexture(_texture, NULL, NULL, &elementWidth, &elementHeight);
    _dstrect = { _xPos, _yPos, elementWidth, elementHeight };
}

void WelcomeScreen::CopyToRender(SDL_Renderer *render){
    SDL_RenderCopy(render, _texture, NULL, &_dstrect);
}

void WelcomeScreen::SetTexture(SDL_Renderer *render){
    _texture = SDL_CreateTextureFromSurface(render, _surface);
}

void WelcomeScreen::EditPosition(int xPosNew, int yPosNew){
    _xPos = xPosNew;
    _yPos = yPosNew;
}

void Text::HandleInputText(SDL_Event &e, bool &renderInputText, bool &welcomeScreenOn, bool &insertPlayer1Username){
    // Check keys pressed by the users
    // If backsapce key is pressed inserted username letters are deleted (one by one)
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && _myText.get()->length() > 10){
        _myText.get()->pop_back();
        renderInputText = true;
    }
    // Insert pressed keys (letters, numbers and SDL recognized symbols) to the players usernames
    else if (e.type == SDL_TEXTINPUT){
        *(_myText.get()) += e.text.text;
        renderInputText = true;
    }
    // If tab key is pressed and player 1 inserted at least one letter in their respective username, the following
    // keys are inserted in player 2 username
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB && insertPlayer1Username && _myText.get()->length() > 10){
        insertPlayer1Username = false;
    }
    // If enter key is pressed and player 2 inserted at least one letter in their respective username, welcome screen 
    // stops being presented and the game starts in the next game loop iteration
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN && !insertPlayer1Username && _myText.get()->length() > 10){
        welcomeScreenOn = false;
    }
}

void Text::SetTxtColor(Colors color){
    switch (color)
    {
        case white:
            _color = { 255, 255, 255, 255 };
            break;
        case blue:
            _color = {  89, 203, 232, 255 };
            break;
        case red:
            _color = { 173,   0,  14, 255 };
            break;
        case green:
            _color = { 121, 170,  47, 255 };
            break;
        case yellow:
            _color = { 161, 118,  27, 255 };
            break;
        default:
            _color = { 255, 255, 255, 255 };
            break;
        }
}

void Text::SetTxtFont(Fonts font, int size){
    switch (font)
    {
        case arial:
            _font = TTF_OpenFont("../Fonts/arial.ttf", size);
            break;
        case welcomeF:
            _font = TTF_OpenFont("../Fonts/welcome.ttf", size);
            break;
        case gameOverF:
            _font = TTF_OpenFont("../Fonts/gameOver.ttf", size);
            break;
        case textF:
            _font = TTF_OpenFont("../Fonts/text.ttf", size);
            break;
        case enterF:
            _font = TTF_OpenFont("../Fonts/enter.ttf", size);
            break;
        default:
            _font = TTF_OpenFont("../Fonts/arial.ttf", size); // Text font set to arial by default
            break;
    }
}

void Text::SetTxtSurface(){
    _surface = TTF_RenderText_Solid(_font, _myText.get()->c_str(),  _color);
}

std::string Text::GetUsername(){
    return *_myText.get();
}

void Text::EditText(std::shared_ptr<std::string> newText){
    _myText = std::move(newText);
}

void Image::SetImgSurface(){
    _surface = SDL_LoadBMP(*(_imgPath.get()));
}

void Image::PositionElement(){
    int elementWidth, elementHeight = 0;
    SDL_QueryTexture(_texture, NULL, NULL, &elementWidth, &elementHeight);
    elementWidth  /=2.5;
    elementHeight /=2.5;
    _xPos -= elementWidth/2;
    _yPos -= elementHeight/2;
    _dstrect = { _xPos, _yPos, elementWidth, elementHeight };
}