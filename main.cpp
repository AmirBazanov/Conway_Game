#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

void drawGrid(RenderWindow* wn){
    RectangleShape line;
    Vector2i wn_size = (Vector2i)wn->getSize();
    for(int x = 0; x<=wn_size.x; x += 10){
        line = RectangleShape({1, (float)wn_size.y});
        line.setFillColor(Color(80,80,80, 80));
        line.setPosition({(float)x,0});
        wn->draw(line);
    }
    for(int x = 0; x<=wn_size.y; x += 10){
        line = RectangleShape({(float )wn_size.x,1});
        line.setFillColor(Color(80,80,80, 80));
        line.setPosition({0,(float)x});
        wn->draw(line);
    }

}


void begin(RenderWindow* wn, short origin[75][145]) {
    Vector2f mouse_poss = {(float)Mouse::getPosition().x-wn->getPosition().x-10, (float)Mouse::getPosition().y-wn->getPosition().y-30};
    RectangleShape cell({10, 10});
    if(Mouse::isButtonPressed(Mouse::Left)) {
        origin[(int)mouse_poss.y / 10][(int)mouse_poss.x / 10] = 1;
    }if(Mouse::isButtonPressed(Mouse::Right)) {
        origin[(int)mouse_poss.y / 10][(int)mouse_poss.x / 10] = 0;
    }
    for (int y = 0; y < 75; ++y) {
        for (int x = 0; x < 145; ++x) {
            if (origin[y][x]){
                cell.setPosition({(float)x*10, (float)y*10});
                wn->draw(cell);
            }
        }

    }
}
void check(short origin[75][145],short gen[75][145], bool game_status,RenderWindow* wn){
    int near;
    RectangleShape cell({10, 10});
    if (game_status) {
    for (int y = 0; y < 75; ++y) {
        for (int x = 0; x < 145; ++x) {
            near = 0;
//            std::cout<<origin[y][x]<<std::endl;
                for (int j = -1; j <= 1; j++) {
                    for (int i = -1; i <= 1; i++) {
                        near +=origin[y + j][x + i];
                        }
                    }
//                    near -= origin[y][x];/
//                std::cout<<near<<std::endl;
            if ((origin[y][x] == 1) && (near < 2)){
                gen[y][x] = 0;}

                // Cell dies due to over population
            else if ((origin[y][x] == 1) && (near > 3)){
                gen[y][x] = 0;}

                // A new cell is born
            else if ((origin[y][x] == 0) && (near == 3)){
                gen[y][x] = 1;}

                // Remains the same
            else{
                gen[y][x] = origin[y][x];}
            origin[y][x] = gen[y][x];
                }
            }
        }
    for (int y = 0; y < 75; ++y) {
        for (int x = 0; x < 145; ++x) {
            if (gen[y][x]) {
                cell.setPosition({(float) x * 10, (float) y * 10});
                wn->draw(cell);
            }
        }

    }
    }

int main() {
    bool start = false;
    RenderWindow window(VideoMode(1451, 751), "Conway");
//    window.setFramerateLimit(10);
    short origin[75][145]={};
    short next_gen[75][145]={};
    Event event{};
    window.clear();
    while(window.isOpen()){
        while (window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::R)) {
            start = true;
        }
        if(start){
            window.setTitle("Conway Start");
        }else window.setTitle("Conway Stop");
        window.clear();
        drawGrid(&window);
        if(!start){
        begin(&window, origin);
        }
        check(origin, next_gen, start, &window);
        window.display();
    }
}
