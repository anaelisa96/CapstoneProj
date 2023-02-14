#include "welcomeScreen.h"

void WelcomeScreen::PositionElement(bool isImg){
    int elementWidth, elementHeight = 0;
    SDL_QueryTexture(_texture, NULL, NULL, &elementWidth, &elementHeight);
    if (isImg){
        elementWidth  /=4;
        elementHeight /=4;
        _xPos -= elementWidth/2;
        _yPos -= elementHeight/2;
    }
    _dstrect = { _xPos, _yPos, elementWidth, elementHeight };
}

void WelcomeScreen::CopyToRender(SDL_Renderer *render){
    SDL_RenderCopy(render, _texture, NULL, &_dstrect);
}

void WelcomeScreen::SetTexture(SDL_Renderer *render){
    _texture = SDL_CreateTextureFromSurface(render, _surface);
}

void Text::HandleInputText(SDL_Event &e, bool &renderInputText, bool &welcomeScreenOn, bool &insertPlayer1Username){
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && _myText.get()->length() > 10){
        _myText.get()->pop_back();
        renderInputText = true;
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN){
        welcomeScreenOn = false;
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB){
        insertPlayer1Username = false;
    }
    else if (e.type == SDL_TEXTINPUT){
        *(_myText.get()) += e.text.text;
        renderInputText = true;
    }
}

void Text::SetTxtColor(Colors color){
    switch (color)
    {
    case white:
        _color = { 255, 255, 255, 255 };
        break;
    
    default:
        _color = { 255, 255, 255, 255 }; // Text set to white by default
        break;
    }
}

void Text::SetTxtFont(Fonts font, int size){
    switch (font)
    {
    case arial:
        _font = TTF_OpenFont("arial.ttf", size);
        break;
    
    default:
        _font = TTF_OpenFont("arial.ttf", size); // Text font set to arial by default
        break;
    }
}

void Text::SetTxtSurface(){
    _surface = TTF_RenderText_Solid(_font, _myText.get()->c_str(),  _color);
}

std::shared_ptr<std::string> Text::GetInputText(){
    return _myText;
}

std::string Text::GetUsername(){
    return *_myText.get();
}

void Image::SetImgSurface(){
    _surface = SDL_LoadBMP(_imgPath);
}
