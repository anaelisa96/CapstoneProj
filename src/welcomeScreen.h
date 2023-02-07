#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include "SDL_ttf.h"
#include <string>
#include <memory>

enum Colors{
    white,
    blue,
    red,
    green,
    yellow
};
     
enum Fonts{
    arial,
    calibri,
    centuryGothic,
    timeNewRoman
};

class WelcomeScreen{
    public:
        WelcomeScreen(){};
        ~WelcomeScreen(){}

        void SetTexture(SDL_Renderer *render);
        void PositionElement(int xPos, int yPos, bool isImg);
        void CopyToRender(SDL_Renderer *render);
        void PrepareElement(SDL_Renderer *render, bool isImg);
    protected:
        SDL_Rect _dstrect;
        SDL_Surface *_surface;
        SDL_Texture *_texture;
};

class Text : public WelcomeScreen{
    public:

    Text(std::shared_ptr<std::string> text, Colors color, Fonts font, int size){
        _myText = std::move(text);
        SetTxtColor(color);
        SetTxtFont(font, size);
        SetTxtSurface();
    }
    ~Text() {}

    void HandleInputText(SDL_Event &e, bool &renderInputText, bool &WelcomeScreenOn);
    void SetTxtSurface();
    std::shared_ptr<std::string> GetInputText();
    
    private:
    void SetTxtColor(Colors color);
    void SetTxtFont(Fonts font, int size);
    std::shared_ptr<std::string> _myText;
    SDL_Color _color;
    TTF_Font* _font;
};

class Image : public WelcomeScreen{
    public:
    Image(const char* imgPath) : _imgPath(imgPath){
        SetImgSurface(); }
    ~Image(){}
    private:
    void SetImgSurface();
    const char* _imgPath;
};

#endif // WELCOMESCREEN