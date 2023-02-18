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
    gameOverF,
    welcomeF,
    textF,
    enterF
};

class WelcomeScreen{
    public:
        WelcomeScreen(int xPos, int yPos) : _xPos(xPos), _yPos(yPos){};

        void SetTexture(SDL_Renderer *render);
        void PositionElement();
        void CopyToRender(SDL_Renderer *render);
        void PrepareElement(SDL_Renderer *render, bool isImg);
        void EditPosition(int xPosNew, int yPosNew);

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

        void HandleInputText(SDL_Event &e, bool &renderInputText, bool &WelcomeScreenOn,  bool &insertPlayer1Username);
        void SetTxtSurface();
        std::string GetUsername();
        void EditText(std::shared_ptr<std::string> newText);
        void SetTxtColor(Colors color);
        void SetTxtFont(Fonts font, int size);
    
    private:
        std::shared_ptr<std::string> _myText;
        SDL_Color _color;
        TTF_Font* _font;
};

class Image : public WelcomeScreen{
    public:
        Image(std::shared_ptr<const char*> imgPath, int xPos, int yPos) : _imgPath(std::move(imgPath)),
              WelcomeScreen(xPos, yPos){
            SetImgSurface(); }
    void PositionElement();
    private:
        void SetImgSurface();
        std::shared_ptr<const char*> _imgPath;
};

#endif // WELCOMESCREEN