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
        WelcomeScreen(int xPos, int yPos) : _xPos(xPos), _yPos(yPos){};
        ~WelcomeScreen(){}

        void SetTexture(SDL_Renderer *render);
        void PositionElement(bool isImg);
        void CopyToRender(SDL_Renderer *render);
        void PrepareElement(SDL_Renderer *render, bool isImg);
    protected:
        SDL_Rect _dstrect;
        SDL_Surface *_surface;
        SDL_Texture *_texture;
        int _xPos, _yPos;
};

class Text : public WelcomeScreen{
    public:

    Text(std::shared_ptr<std::string> text, Colors color, Fonts font, int size, int xPos,
         int yPos) : WelcomeScreen(xPos, yPos){
        _myText = std::move(text);
        SetTxtColor(color);
        SetTxtFont(font, size);
        SetTxtSurface();
    }
    ~Text() {}

    void HandleInputText(SDL_Event &e, bool &renderInputText, bool &WelcomeScreenOn,  bool &insertPlayer1Username);
    void SetTxtSurface();
    std::shared_ptr<std::string> GetInputText();
    std::string GetUsername();
    
    private:
    void SetTxtColor(Colors color);
    void SetTxtFont(Fonts font, int size);
    std::shared_ptr<std::string> _myText;
    SDL_Color _color;
    TTF_Font* _font;
    //int _xPos;
    //int _yPos;
};

class Image : public WelcomeScreen{
    public:
    Image(const char* imgPath, int xPos, int yPos) : _imgPath(imgPath), WelcomeScreen(xPos, yPos){
        SetImgSurface(); }
    ~Image(){}
    private:
    void SetImgSurface();
    const char* _imgPath;
};

#endif // WELCOMESCREEN