#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <iomanip>
using namespace std;
using namespace sf;


double calculate(double currentGrade, double goal, double weight);

int main(){

    RenderWindow window(VideoMode(600, 600), "Final Grade Calculator");
    Event event;

    Font arial;
    arial.loadFromFile("arial.ttf");

    Text finalGradeLable;
    finalGradeLable.setFont(arial);
    finalGradeLable.setString("Current Grade: ");
    finalGradeLable.setPosition(Vector2f(50, 50));
    finalGradeLable.setFillColor(Color::White);

    Text goalLable;
    goalLable.setFont(arial);
    goalLable.setString("Wanted Grade: ");
    goalLable.setFillColor(Color::White);
    goalLable.setPosition(Vector2f(50, 100));

    Text weightLable;
    weightLable.setFont(arial);
    weightLable.setString("Weight: ");
    weightLable.setFillColor(Color::White);
    weightLable.setPosition(Vector2f(50, 150));

    Text calculateLable;
    calculateLable.setFont(arial);
    calculateLable.setString("Calculate");
    calculateLable.setFillColor(Color::Black);
    calculateLable.setOutlineColor(Color::White);
    calculateLable.setPosition(Vector2f(180, 210));

    Text outputLable;
    outputLable.setFont(arial);
    outputLable.setFillColor(Color::White);
    outputLable.setOutlineColor(Color::White);
    outputLable.setPosition(Vector2f(25, 550));

    RectangleShape calculateButton;
    calculateButton.setFillColor(Color(215, 232, 186));
    calculateButton.setSize(Vector2f(300, 50));
    calculateButton.setPosition(Vector2f(100, 200));

    bool displayOutput = false;
    bool writeFinal = false;
    bool writeWanted = false;
    bool writeGoal = false;

    string userInput;

    Text finalField;
    finalField.setFont(arial);
    finalField.setFillColor(Color::Black);
    finalField.setPosition(Vector2f(265, 50));

    Text wantedField;
    wantedField.setFont(arial);
    wantedField.setFillColor(Color::Black);
    wantedField.setPosition(Vector2f(275, 100));

    Text goalField;
    goalField.setFont(arial);
    goalField.setFillColor(Color::Black);
    goalField.setPosition(Vector2f(165, 150));

    RectangleShape finalBox;
    finalBox.setFillColor(Color::White);
    finalBox.setSize(Vector2f(330, 40));
    finalBox.setPosition(Vector2f(260, 50));

    RectangleShape wantedBox;
    wantedBox.setFillColor(Color::White);
    wantedBox.setSize(Vector2f(320, 40));
    wantedBox.setPosition(Vector2f(270, 100));

    RectangleShape goalBox;
    goalBox.setFillColor(Color::White);
    goalBox.setSize(Vector2f(430, 40));
    goalBox.setPosition(Vector2f(160, 150));


    double weight;
    double goal;
    double currentGrade;

    while(window.isOpen()){
        window.clear(Color(63, 94, 90));

        window.draw(finalGradeLable);
        window.draw(goalLable);
        window.draw(weightLable);
        window.draw(calculateButton);
        window.draw(calculateLable);
        window.draw(finalBox);
        window.draw(finalField);
        window.draw(wantedBox);
        window.draw(goalBox);
        window.draw(wantedField);
        window.draw(goalField);

        if(displayOutput){
            window.draw(outputLable);
        }

        window.display();

        while(window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }

            if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left){
                    if(Mouse::getPosition(window).x >= calculateButton.getPosition().x &&
                    Mouse::getPosition(window).x <= calculateButton.getPosition().x + calculateButton.getSize().x &&
                    Mouse::getPosition(window).y >= calculateButton.getPosition().y &&
                    Mouse::getPosition(window).y <= calculateButton.getPosition().y + calculateButton.getSize().y){
                        bool outputErr = false;
                        string temp = finalField.getString();

                        stringstream outputText;

                        try{
                            currentGrade = stod(temp);
                        }
                        catch(const invalid_argument& err){
                            outputErr = true;
                        }

                        temp = wantedField.getString();

                        try{
                            goal = stod(temp);
                        }
                        catch(const invalid_argument& err){
                            outputErr = true;
                        }

                        temp = goalField.getString();

                        try{
                            weight = stod(temp);
                        }
                        catch(const invalid_argument& err){
                            outputErr = true;
                        }

                        if(!outputErr){
                            cout << fixed << setprecision(2) << currentGrade << " " << goal << " " << weight << endl;

                            double outputGrade = calculate(currentGrade, goal, weight);

                            outputText << fixed << setprecision(2) << "You need a " << outputGrade << " to get a " << goal << endl;

                            outputLable.setString(outputText.str());
                        }
                        else{
                            outputLable.setString("Invalid Input");
                        }

                        displayOutput = true;

                    }

                    else{
                        displayOutput = false;
                    }

                    if(Mouse::getPosition(window).x >= finalBox.getPosition().x &&
                    Mouse::getPosition(window).x <= finalBox.getPosition().x + finalBox.getSize().x &&
                    Mouse::getPosition(window).y >= finalBox.getPosition().y &&
                    Mouse::getPosition(window).y <= finalBox.getPosition().y + finalBox.getSize().y){
                        writeFinal = true;
                    }
                    else{
                        writeFinal = false;
                        userInput = "";
                    }

                    if(Mouse::getPosition(window).x >= wantedBox.getPosition().x &&
                    Mouse::getPosition(window).x <= wantedBox.getPosition().x + wantedBox.getSize().x &&
                    Mouse::getPosition(window).y >= wantedBox.getPosition().y &&
                    Mouse::getPosition(window).y <= wantedBox.getPosition().y + wantedBox.getSize().y){
                        writeWanted = true;
                    }
                    else{
                        writeWanted = false;
                        userInput = "";
                    }

                    if(Mouse::getPosition(window).x >= goalBox.getPosition().x &&
                    Mouse::getPosition(window).x <= goalBox.getPosition().x + goalBox.getSize().x &&
                    Mouse::getPosition(window).y >= goalBox.getPosition().y &&
                    Mouse::getPosition(window).y <= goalBox.getPosition().y + goalBox.getSize().y){
                        writeGoal = true;
                    }
                    else{
                        writeGoal = false;
                        userInput = "";
                    }


                    
                }
            }

            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Escape){
                    window.close();
                }
            }

            if(event.type == Event::TextEntered){
                if(writeFinal){
                    userInput += event.text.unicode;
                    finalField.setString(userInput);
                }

                if(writeWanted){
                    userInput += event.text.unicode;
                    wantedField.setString(userInput);
                }

                if(writeGoal){
                    userInput += event.text.unicode;
                    goalField.setString(userInput);
                }
                
            }

        }
}
    
    return 0;
}

double calculate(double currentgrade, double goal, double weight){
    double neededGrade;
    neededGrade = (goal - (currentgrade * (1 - (weight/100))))/weight;
    return neededGrade * 100;
}