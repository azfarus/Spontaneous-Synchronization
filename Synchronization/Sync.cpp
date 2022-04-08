#include <SFML/Graphics.hpp>
#include <chrono>
#include<Windows.h>
#include <iostream>

class bulb
{
public:
    sf::CircleShape golla;
    
    void create(float x, float y)
    {
        golla.setRadius(30.0);
        golla.setPosition({ x,y });

     }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!");
    sf::CircleShape shape(100.f) , shape2(100.f);
    sf::Text omega;

    double Wa = 1e-3, Wb= 5e-3 , Ta = 0 , Tb = 0 , dTa , dTb;
    dTa = Wa;
    dTb = Wb;
    shape2.setOrigin({ 50,50 });
    shape.setOrigin({ 50,50 });
    shape.setPosition({ 250,400 });
    shape2.setPosition({ 750,400 });


     auto timeStart = std::chrono::steady_clock::now();
    while (window.isOpen())
    {
        auto time = std::chrono::steady_clock::now();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
       
        std::chrono::duration<float, std::milli> gg = time - timeStart;

        

        dTa =dTa + .5e-6 * sinf(Tb - Ta);
        dTb = dTb + .5e-6* sinf(Ta - Tb);

        Ta = abs(dTa) * gg.count();
        Tb = abs(dTb) * gg.count();
       
        if (fabs(cosf(Ta)) == 1) std::cout << "Wa : " << dTa  << " Wb : " <<dTb <<std::endl;
        
       
        
        window.clear();
        shape.setFillColor(sf::Color(0, 0, 255.0   , 255 * std::fabs(cosf(Ta))));
        shape2.setFillColor(sf::Color(150, 0, 255.0, 255 * std::fabs(cosf(Tb))));
        window.draw(shape);
        window.draw(shape2);
        window.display();
    }

    return 0;
}