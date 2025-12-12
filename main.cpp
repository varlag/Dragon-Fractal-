#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <vector>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MAX_DEPTH = 15;  

class DragonWindow : public Fl_Double_Window {
private:
    int depth;  
    
    void drawLine(float x1, float y1, float x2, float y2) {
        fl_color(FL_GREEN);  
        fl_line(x1, y1, x2, y2);
    }
    
    void drawDragon(float x1, float y1, float x2, float y2, int n) {
        if (n == 0) {
            drawLine(x1, y1, x2, y2);
            return;
        }
        
        float mx = (x1 + x2) / 2;
        float my = (y1 + y2) / 2;
        
        float dx = x2 - x1;
        float dy = y2 - y1;
        float nx = mx - dy / 2;
        float ny = my + dx / 2;
        
        drawDragon(x1, y1, nx, ny, n - 1);
        drawDragon(x2, y2, nx, ny, n - 1);
    }
    
public:
    DragonWindow(int w, int h, const char* title) : Fl_Double_Window(w, h, title) {
        depth = 0; 
        color(FL_BLACK);  
    }
    
    void draw() override {
        Fl_Double_Window::draw();
        
        float startX = w() * 0.3f;
        float startY = h() * 0.5f;
        float endX = w() * 0.7f;
        float endY = h() * 0.5f;
        
        drawDragon(startX, startY, endX, endY, depth);
        
        fl_color(FL_WHITE);
        fl_font(FL_HELVETICA, 20);
        std::string text = "Глубина: " + std::to_string(depth);
        fl_draw(text.c_str(), 10, 30);
    }
    
    int handle(int event) override {
        if (event == FL_KEYDOWN) {
            switch (Fl::event_key()) {
                case FL_Up:    
                    if (depth < MAX_DEPTH) depth++;
                    redraw();
                    return 1;
                case FL_Down:  
                    if (depth > 1) depth--;
                    redraw();
                    return 1;
                case ' ':      
                    depth = 1;
                    redraw();
                    return 1;
                case FL_Escape: 
                    hide();
                    return 1;
            }
        }
        return Fl_Double_Window::handle(event);
    }
};

int main() {
    std::cout << "=== Фрактал Дракона ===" << std::endl;
    std::cout << "Управление:" << std::endl;
    std::cout << "  Стрелка вверх - увеличить глубину" << std::endl;
    std::cout << "  Стрелка вниз - уменьшить глубину" << std::endl;
    std::cout << "  Пробел - сбросить на 1" << std::endl;
    std::cout << "  ESC - выход" << std::endl;
    
    DragonWindow window(WINDOW_WIDTH, WINDOW_HEIGHT, "Дракон Хартера-Хейтуэя");
    

    window.show();

    return Fl::run();
}