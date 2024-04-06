#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include <fstream>
using namespace std;

// matrice
int matrixWidth = 10;  //MODIF
int matrixHeight = 7; // Numărul de linii
int v[101][101], ok;

float cellSize = 75.0f;  // celule, f este pus ca sa nu se incurce cu double
enum GameState
{
    MainMenu,
    Player1,
    Solo,
    Chapter,
    Level1,
    Level2,
    Level3,
    Level4,
    Level5,
    Player1vsPlayer2,
    WriteHere,
    Output,
    Settings,
    About,
};


struct Button
{
    sf::RectangleShape shape;
    sf::Text text;

    void setButtonProperties(const sf::Font& font, unsigned int characterSize,
        const sf::Color& shapeColor, const sf::Color& textColor, const std::string& buttonText)
    {
        shape.setSize(sf::Vector2f(200.0f, 50.0f));
        shape.setFillColor(shapeColor);
        text.setFont(font);
        text.setCharacterSize(characterSize);
        text.setString(buttonText);
        text.setFillColor(textColor);
    }
};

void centerButton(Button& button, float x, float y)
{
    button.shape.setPosition(x, y);

    float textX = x + button.shape.getSize().x / 8.0f;
    float textY = y + button.shape.getSize().y / 1.20f;
    button.text.setPosition(textX, textY);
    sf::FloatRect textBounds = button.text.getLocalBounds();
    button.text.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);

}

void positionButtonTopLeft(Button& button, float x, float y)
{
    button.shape.setPosition(x, y);
    button.text.setPosition(x, y);
}




centrareaButtons(const sf::Font& font, unsigned int characterSize)///constructor
{


    BackOutputButton.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "Back");
    Player1Button.setButtonProperties(font, characterSize, sf::Color::Green, sf::Color::Black, "Player 1");
    SettingsButton.setButtonProperties(font, characterSize, sf::Color::Blue, sf::Color::White, "Settings");
    AboutButton.setButtonProperties(font, characterSize, sf::Color::Red, sf::Color::White, "About");
    Player1vsPlayer2Button.setButtonProperties(font, characterSize, sf::Color::Yellow, sf::Color::Black, "1vs1");
    SoloButton.setButtonProperties(font, characterSize, sf::Color::Cyan, sf::Color::Black, "Solo");
    ChapterButton.setButtonProperties(font, characterSize, sf::Color::Magenta, sf::Color::White, "Chapter");
    BackPlayer1Button.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "Back");
    BackPlayer1vsPlayer2Button.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "Back");
    BackSettingsButton.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "Back");
    BackAboutButton.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "Back");
    BackSoloButton.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "Back");
    BackChapterButton.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "Back");
    StartAgainButton.setButtonProperties(font, characterSize, sf::Color::Green, sf::Color::Black, "Again");

    Level1Button.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "1");
    Level2Button.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "2");
    Level3Button.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "3");
    Level4Button.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "4");
    Level5Button.setButtonProperties(font, characterSize, sf::Color::White, sf::Color::Black, "5");




    centerButton(Level1Button, 200, 400);
    centerButton(Level2Button, 400, 100);
    centerButton(Level3Button, 600, 700);
    centerButton(Level4Button, 800, 300);
    centerButton(Level5Button, 1000, 800);
    centerButton(AboutButton, 1100, 500);
    centerButton(ChapterButton, 700, 400);
    centerButton(Player1vsPlayer2Button, 700, 700);
    centerButton(Player1Button, 700, 300);
    centerButton(SoloButton, 700, 600);
    centerButton(SettingsButton, 250, 500);
    positionButtonTopLeft(BackOutputButton, 50, 50);
    positionButtonTopLeft(BackPlayer1Button, 50, 50);
    positionButtonTopLeft(BackSettingsButton, 50, 50);
    positionButtonTopLeft(BackAboutButton, 50, 50);
    positionButtonTopLeft(BackPlayer1vsPlayer2Button, 50, 50);
    positionButtonTopLeft(BackChapterButton, 50, 50);
    positionButtonTopLeft(BackSoloButton, 50, 50);

    StartAgainButton.shape.setPosition(50, 950);
    StartAgainButton.text.setPosition(StartAgainButton.shape.getPosition().x, StartAgainButton.shape.getPosition().y);



}


enum class ShapeType
{
    None,
    Piesa1,
    Piesa2,
    Piesa3,
    Piesa4,
    Piesa5,
    Gard,
    PiesaW,
    PiesaL,
};


class Shape  ///clasa tata
{
protected:///doar pt clasele derivate(fii)
    float cellSize;

public:
    Shape(float cellSize) : cellSize(cellSize) {}///constructor, am declarat inainte de incepere sau pot sa fac this->cellSize=cellSize

    virtual void draw(sf::RenderWindow& window, float x, float y) const = 0;///virtual obliga clasele derivate sa contina functia draw, virtual este mai explicit cand suprascriu o functie din clasa de baza
    ///destructor care elibereaza memoria clasei derivate
    ///functie virtuala pura
};


class Piesa1Shape : public Shape  ///adica e de tip shape
{
public:
    using Shape::Shape;///mostenire constructor shape

    void draw(sf::RenderWindow& window, float x, float y) const override///override este folosit ca sa ii zica compilatorului ca se suprascrie functia
    {

        sf::RectangleShape rectangle(sf::Vector2f(cellSize, cellSize));
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::Red);

        window.draw(rectangle);
    }
};
class Piesa2Shape : public Shape
{
public:
    using Shape::Shape;

    void draw(sf::RenderWindow& window, float x, float y) const override
    {

        sf::CircleShape circle(cellSize / 2.0f);///raza
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color::Green);

        window.draw(circle);
    }
};

class Piesa3Shape : public Shape
{
public:
    using Shape::Shape;

    void draw(sf::RenderWindow& window, float x, float y) const override
    {

        sf::CircleShape circle(cellSize / 2.0f);///primeste raza
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color::Blue);

        window.draw(circle);
    }
};

class Piesa4Shape : public Shape
{
public:
    using Shape::Shape;

    void draw(sf::RenderWindow& window, float x, float y) const override
    {

        sf::ConvexShape rhombus;
        rhombus.setPointCount(4);
        rhombus.setPoint(0, sf::Vector2f(x + cellSize / 2.0f, y));
        rhombus.setPoint(1, sf::Vector2f(x + cellSize, y + cellSize / 2.0f));
        rhombus.setPoint(2, sf::Vector2f(x + cellSize / 2.0f, y + cellSize));
        rhombus.setPoint(3, sf::Vector2f(x, y + cellSize / 2.0f));
        rhombus.setFillColor(sf::Color::Yellow);

        window.draw(rhombus);
    }

};

class Piesa5Shape : public Shape
{
public:
    using Shape::Shape;

    void draw(sf::RenderWindow& window, float x, float y) const override
    {
        // trapez
        sf::ConvexShape trapez;
        trapez.setPointCount(4);
        trapez.setPoint(0, sf::Vector2f(x + cellSize / 5.0f, y));
        trapez.setPoint(1, sf::Vector2f(x + (4 * cellSize) / 5.0f, y));
        trapez.setPoint(2, sf::Vector2f(x + (3 * cellSize) / 5.0f, y + cellSize));
        trapez.setPoint(3, sf::Vector2f(x + (2 * cellSize) / 5.0f, y + cellSize));
        trapez.setFillColor(sf::Color::Magenta);

        window.draw(trapez);
    }
};
//gard
class GardShape : public Shape
{
public:
    using Shape::Shape;


    void draw(sf::RenderWindow& window, float x, float y) const override
    {
        sf::RectangleShape gard(sf::Vector2f(cellSize, cellSize));
        gard.setPosition(x, y);
        gard.setFillColor(sf::Color::Green);
        window.draw(gard);
    }

};
//cand e corect
class PiesaWShape : public Shape
{
public:
    using Shape::Shape;


    void draw(sf::RenderWindow& window, float x, float y) const override
    {
        //verde inchis
        sf::CircleShape circle(cellSize / 2.0f);
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color(0, 128, 0));
        window.draw(circle);
    }

};
//pentru grad aranjat gresit
class PiesaLShape : public Shape
{
public:
    using Shape::Shape;
    void draw(sf::RenderWindow& window, float x, float y) const override
    {

        sf::CircleShape circle(cellSize / 2.0f);
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color::Red);
        window.draw(circle);
    }

};
//

class CurrentLevelType
{
private:
    ShapeType matrix[7][10];

public:

    void setPiesaType(int row, int col, ShapeType type)
    {
        if (row >= 0 && row < 7 && col >= 0 && col < 10)
        {
            matrix[row][col] = type;
        }

    }


    ShapeType getPiesaType(int row, int col)
        const///indica ca nu modific starea curenta a matricei
    {
        if (row >= 0 && row < 7 && col >= 0 && col < 10)
        {
            return matrix[row][col];
        }
        else
        {

            return ShapeType::None;
        }
    }
};

class Game
{
private:
    int matrix[7][9];
    CurrentLevelType currentLevel;
    int selectedLevel = 1;

    sf::Music music;
    sf::RectangleShape MusicButton;
    sf::Text MusicButtonText;

    sf::RectangleShape volumeBar;
    sf::RectangleShape volumeDivider;

    sf::RectangleShape reviewInputBox;
    sf::Text reviewInputText;
    string currentReview;

    sf::Text gameRulesText;

    sf::RectangleShape horseShape;
    sf::CircleShape sheepShape;
    sf::ConvexShape pigShape;
    sf::CircleShape waterBasinShape;
    sf::ConvexShape cowShape;
    sf::RectangleShape boxRule;
    void saveLevelToFile(const string& levelFileName);
public:
    sf::RenderWindow window;
    sf::Font font;
    unsigned int characterSize = 50;
    GameState currentState = GameState::MainMenu;



    centrareaButtons buttons;
    Game() : buttons(font, characterSize), MusicButton(sf::Vector2f(100.0f, 50.0f)), reviewInputBox(sf::Vector2f(400.0f, 50.0f)),
        reviewInputText("", font, characterSize),
        currentReview("")
    {

        cout << "Jocul a fost creat!\n";

        if (!font.loadFromFile("res/fonts/Inkfree.ttf"))
        {
            cerr << "eroare!\n";
        }

        gameRulesText.setFont(font);
        gameRulesText.setCharacterSize(20);
        gameRulesText.setFillColor(sf::Color::White);
        gameRulesText.setPosition(100.0f, 250.0f);

        string rulesText = "BINE ATI VENIT LA SMART FARMER!\n\n";
        rulesText += "AICI VETI GASI REGULILE JOCULUI\n";
        rulesText += "JOCUL CONTINE O TABLA SI MAI MULTE TIPURI DE PIESE\n";
        rulesText += "AVEM 4 PIESE ANIMAL: OAIE, PORC, VACA, CAL)\n";
        rulesText += "4 GARDURI SI 4 BAZINE DE APA\n";
        rulesText += "PATRATUL ROSU  ESTE CALUL,\n";
        rulesText += "CERCUL VERDE (aici desenezi cercul verde) ESTE OAIA,\n";
        rulesText += "TRAPEZUL MAGENTA ESTE PORCUL,\n";
        rulesText += "CERCUL ALABSTRU ESTE BAZINUL DE APA,\n";
        rulesText += "IAR ROMBUL GALBEN ESTE VACA\n\n";
        rulesText += "AVETI 2 TIPURI DE JOC\n";
        rulesText += "CHAPTER DETINE 5 NIVELE DE DIFERITE DIFICULTATI SI VOI TREBUIE SA AMPLASATI GARDURILE\n";
        rulesText += "ASTFEL INCAT SA FIECARE ANIMAL SA FIE INCHIS CU PERECHEA LUI(daca are),\n";
        rulesText += "IAR DACA INTERVINE BAZINUL DE APA, LA FIECARE ANIMAL INCHIS TREBUIE SA AIBA SI UN BAZIN DE APA\n";
        rulesText += "LA SOLO ESTE MAI AVANSAT, ASTFEL INCAT PUTETI PUNE PIESELE UNDE VRETI VOI SI CATE VRETI VOI,\n";
        rulesText += "IAR AICI NU ESTE DE CASTIGAT SAU DE PIERDUT DEOARECE VA PERMITE SA VEDETI TOATE POSIBILITATILE\n";
        rulesText += "LA SECTIUNEA 1VS1 AVETI UN CHAT IN CARE PUTETI SA VA LASATI REVIEW SI IDEI INOVATIVE\n";
        rulesText += "PENTRU A ACTUALIZA JOCUL\n";
        rulesText += "LA SETTINGS AVETI BUTONUL DE MUZICA SI BARA DE VOLUM\n";
        rulesText += "MULT SUCCES SI SPOR LA CREATIVITATE!";

        gameRulesText.setString(rulesText);

        horseShape.setSize(sf::Vector2f(22.0f, 22.0f));
        horseShape.setFillColor(sf::Color::Red);
        horseShape.setPosition(700.0f, 400.0f);

        sheepShape.setRadius(13.0f);
        sheepShape.setFillColor(sf::Color::Green);
        sheepShape.setPosition(600.0f, 420.0f);

        pigShape.setPointCount(4);
        pigShape.setPoint(0, sf::Vector2f(0.0f, 0.0f));
        pigShape.setPoint(1, sf::Vector2f(30.0f, 0.0f));
        pigShape.setPoint(2, sf::Vector2f(10.0f, 20.0f));
        pigShape.setPoint(3, sf::Vector2f(0.0f, 20.0f));
        pigShape.setFillColor(sf::Color::Magenta);
        pigShape.setPosition(640.0f, 450.0f);

        waterBasinShape.setRadius(14.0f);
        waterBasinShape.setFillColor(sf::Color::Blue);
        waterBasinShape.setPosition(550.0f, 470.0f);

        cowShape.setPointCount(4);
        cowShape.setPoint(0, sf::Vector2f(705.0f, 470.0f));
        cowShape.setPoint(1, sf::Vector2f(715.0f, 450.0f));
        cowShape.setPoint(2, sf::Vector2f(705.0f, 430.0f));
        cowShape.setPoint(3, sf::Vector2f(695.0f, 450.0f));
        cowShape.setFillColor(sf::Color::Yellow);
        cowShape.setPosition(9.0f, 55.0f);

        boxRule.setFillColor(sf::Color::Transparent);
        boxRule.setOutlineThickness(2.0f);
        boxRule.setOutlineColor(sf::Color::Red);
        boxRule.setPosition(80.0f, 150.0f);
        boxRule.setSize(sf::Vector2f(1300, 800));


        reviewInputBox.setFillColor(sf::Color::Transparent);
        reviewInputBox.setOutlineThickness(2.0f);
        reviewInputBox.setOutlineColor(sf::Color::Red);
        reviewInputBox.setPosition(300.0f, 200.0f);
        reviewInputBox.setSize(sf::Vector2f(1000, 500));

        reviewInputText.setCharacterSize(24);
        reviewInputText.setFillColor(sf::Color::White);
        reviewInputText.setPosition(reviewInputBox.getPosition().x + 10.0f, reviewInputBox.getPosition().y + 10.0f);





        if (!music.openFromFile("res/music/m.mp3"))
        {
            cerr << "esuare\n";
        }


        MusicButtonText.setFont(font);
        MusicButtonText.setString("Music");
        MusicButtonText.setCharacterSize(30);
        MusicButtonText.setFillColor(sf::Color::White);
        MusicButtonText.setPosition(30.0f, 200.0f);
        MusicButton.setFillColor(sf::Color::Magenta);
        MusicButton.setPosition(20.0f, 300.0f);
        sf::FloatRect textbounds = MusicButtonText.getLocalBounds();
        MusicButtonText.setPosition(MusicButton.getPosition().x + MusicButton.getSize().x / 2 - 35.0f, MusicButton.getPosition().y + MusicButton.getSize().y / 2 - 20.0f);


        volumeBar.setSize(sf::Vector2f(200.0f, 20.0f));
        volumeBar.setFillColor(sf::Color::Cyan);
        volumeBar.setPosition(20.0f, 400.0f);

        volumeDivider.setSize(sf::Vector2f(2.0f, 20.0f));
        volumeDivider.setFillColor(sf::Color::Black);
        volumeDivider.setPosition(volumeBar.getPosition().x + volumeBar.getSize().x / 2 - volumeDivider.getSize().x / 2, volumeBar.getPosition().y); // Plasează bara neagră de împărțire la mijlocul barei de volum

    }



    void handleTextInput(const sf::Uint32& unicode)
    {
        if (unicode < 128)
        {
            if (unicode == '\b' && !currentReview.empty())
            {

                currentReview.pop_back();
            }

            else if (unicode == '\n')
            {

                currentReview += "\n";

                reviewInputText.setString(currentReview);

            }
            else if (unicode == '\r')
            {

                saveReviewToFile(currentReview);
                currentReview.clear();

                reviewInputText.setString(currentReview);

            }
            else
            {

                currentReview += static_cast<char>(unicode);

                reviewInputText.setString(currentReview);
            }
        }
    }

    void saveReviewToFile(const std::string& review)
    {
        ofstream file("res/review.txt", ios::app);
        if (file.is_open())
        {
            file << review << endl;
            file.close();
        }
    }


    void toggleMusic()
    {
        if (music.getStatus() == sf::Music::Playing)
        {
            music.pause();
        }
        else
        {
            music.play();
        }
    }

    void handleMusicButtonClick(const sf::Vector2i& mousePos)
    {
        if (MusicButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            toggleMusic();
        }
    }

    void handleVolumeBar(const sf::Vector2i& mousePos)
    {

        if (volumeBar.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {

            float newVolume = (mousePos.x - volumeBar.getPosition().x) / volumeBar.getSize().x;


            music.setVolume(newVolume * 100);
        }
    }


    void render();
    void backButtonPress();
    void updateMatrix();
    void drawMatrix();


};

void Game::drawMatrix()
{
    const CurrentLevelType& matrix = currentLevel;///un fel tot lucrez cu currentlevel doar sub numele de matrix


    float startX = (window.getSize().x - matrixWidth * cellSize) / 2.0f;
    float startY = (window.getSize().y - matrixHeight * cellSize) / 2.0f;

    for (int i = 0; i < matrixHeight; i++)
    {
        for (int j = 0; j < matrixWidth; j++)
        {
            float x = startX + j * cellSize;
            float y = startY + i * cellSize;


            sf::RectangleShape cellOutline(sf::Vector2f(cellSize, cellSize));
            cellOutline.setPosition(x, y);
            cellOutline.setOutlineThickness(1.0f);
            cellOutline.setOutlineColor(sf::Color::Black);  // delimitez cu negru
            window.draw(cellOutline);
            ShapeType shapeType = matrix.getPiesaType(i, j);

            switch (shapeType)
            {
            case ShapeType::Piesa1:
            {
                Piesa1Shape piesa1(cellSize);
                piesa1.draw(window, x, y);
                break;
            }
            case ShapeType::Piesa2:
            {
                Piesa2Shape piesa2(cellSize);
                piesa2.draw(window, x, y);
                break;
            }
            case ShapeType::Piesa3:
            {
                Piesa3Shape piesa3(cellSize);
                piesa3.draw(window, x, y);
                break;
            }
            case ShapeType::Piesa4:
            {
                Piesa4Shape piesa4(cellSize);
                piesa4.draw(window, x, y);
                break;
            }
            case ShapeType::Piesa5:
            {
                Piesa5Shape piesa5(cellSize);
                piesa5.draw(window, x, y);
                break;
            }

            case ShapeType::Gard:
            {
                GardShape gard(cellSize);
                gard.draw(window, x, y);
                break;
            }
            //w
            case ShapeType::PiesaW:
            {
                PiesaWShape circle(cellSize);
                circle.draw(window, x, y);
                break;
            }
            //L
            case ShapeType::PiesaL:
            {
                PiesaLShape circle(cellSize);
                circle.draw(window, x, y);
                break;
            }

            default:

                break;
            }

        }
    }

    //
    ifstream file("res/level" + to_string(selectedLevel) + "_gard.txt");
    int x, y;
    ofstream outputFile;
    bool deschis = false;

    while (file >> x >> y)
    {

        if ((x % 2 == 0 || y % 2 == 0) && x >= 0 && x < matrixHeight && y >= 0 && y < matrixWidth)
        {

            currentLevel.setPiesaType(x, y, ShapeType::Gard);
            float startX = (window.getSize().x - matrixWidth * cellSize) / 2.0f;
            float startY = (window.getSize().y - matrixHeight * cellSize) / 2.0f;
            float gx = startX + y * cellSize;
            float gy = startY + x * cellSize;

            sf::RectangleShape gardShape(sf::Vector2f(cellSize, cellSize));
            gardShape.setPosition(gx, gy);
            gardShape.setFillColor(sf::Color(192, 192, 192));
            window.draw(gardShape);
            v[x][y] = -1;
        }

        if (ok == 1)
        {
            if (!deschis)
            {

                if (selectedLevel == 1)
                {
                    outputFile.open("res/level1_gard.txt", ios::out | ios::trunc);
                }
                else if (selectedLevel == 2)
                {
                    outputFile.open("res/level2_gard.txt", ios::out | ios::trunc);
                }
                else if (selectedLevel == 3)
                {
                    outputFile.open("res/level3_gard.txt", ios::out | ios::trunc);
                }
                else if (selectedLevel == 4)
                {
                    outputFile.open("res/level4_gard.txt", ios::out | ios::trunc);
                }
                else if (selectedLevel == 5)
                {
                    outputFile.open("res/level5_gard.txt", ios::out | ios::trunc);
                }

                deschis = outputFile.is_open();
            }



            ok = 0;
        }
    }
    file.close();
    outputFile.close();



}



void Game::saveLevelToFile(const std::string& levelFileName)
{
    std::ofstream file("res/" + levelFileName + ".txt");
    if (file.is_open())
    {
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j <= 7; j++)
            {
                file << i << " " << j << " " << static_cast<int>(currentLevel.getPiesaType(i, j)) << "\n";
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "eroare deschidere fisier.\n";
    }
}

int gard1(int a[101][101])
{

    int i, j, ok, k;
    ok = 1;
    for (i = 1; i <= 5; i++)
        for (j = 1; j <= 7; j++)
        {
            // merge si pt caz general
            if (a[i][j] != 0 && a[i][j] != -1)
            {
                for (k = j; a[i][k] != -1; k++)//linie spre dreapta
                {
                    if (a[i][k] != a[i][j] && a[i][k] != 0 && a[i][k] != -1)
                    {
                        ok = 0;

                        return 0;
                    }
                    if (a[i][k] != -1)a[i][k] = a[i][j];
                }
                for (k = j; a[i][k] != -1; k--)//spre stanga
                {
                    if (a[i][k] != a[i][j] && a[i][k] != 0 && a[i][k] != -1)
                    {
                        ok = 0;

                        return 0;
                    }
                    if (a[i][k] != -1)a[i][k] = a[i][j];
                }
                for (k = i; a[k][j] != -1; k++) //pe coloana spre jos
                {
                    if (a[k][j] != a[i][j] && a[k][j] != 0 && a[k][j] != -1)
                    {
                        ok = 0;

                        return 0;
                    }
                    if (a[k][j] != -1)a[k][j] = a[i][j];
                }
                for (k = i; a[k][j] != -1; k--) //pe coloana in sus
                {
                    if (a[k][j] != a[i][j] && a[k][j] != 0 && a[k][j] != -1)
                    {
                        ok = 0;

                        return 0;
                    }
                    if (a[k][j] != -1)a[k][j] = a[i][j];
                }
                int k1 = i;
                int k2 = j;
                while (a[k1][k2] != -1)
                {
                    k1--;
                    k2--;
                    if (a[k1][k2] != a[i][j] && a[k1][k2] != 0 && a[k1][k2] != -1)
                    {
                        {
                            ok = 0;

                            return 0;
                        }
                    }
                    if (a[k1][k2] != -1) a[k1][k2] = a[i][j];
                }//spre stanga sus-> diagonala
                k1 = i;
                k2 = j;
                while (a[k1][k2] != -1)
                {
                    k1++;
                    k2++;
                    if (a[k1][k2] != a[i][j] && a[k1][k2] != 0 && a[k1][k2] != -1)
                    {
                        {
                            ok = 0;

                            return 0;
                        }
                    }
                    if (a[k1][k2] != -1) a[k1][k2] = a[i][j];
                }//spre dreapta jos-> diagonala
                k1 = i;
                k2 = j;
                while (a[k1][k2] != -1)
                {
                    k1++;
                    k2--;
                    if (a[k1][k2] != a[i][j] && a[k1][k2] != 0 && a[k1][k2] != -1)
                    {
                        {
                            ok = 0;

                            return 0;
                        }
                    }
                    if (a[k1][k2] != -1) a[k1][k2] = a[i][j];
                }//spre stanga jos-> diagonala
                k1 = i;
                k2 = j;
                while (a[k1][k2] != -1)
                {
                    k1--;
                    k2++;
                    if (a[k1][k2] != a[i][j] && a[k1][k2] != 0 && a[k1][k2] != -1)
                    {
                        {
                            ok = 0;

                            return 0;
                        }
                    }
                    if (a[k1][k2] != -1) a[k1][k2] = a[i][j];
                }//spre dreapta sus-> diagonala
            }
        }
    //ma plimb pe cea ramas nevizitat si verific daca e 0
    for (i = 1; i <= 5; i++)
        for (j = 1; j <= 7; j++)
            if (a[i][j] == 0) gard1(a);
    if (ok)  return 1;
}
//verificare pt apa
int gard2(int a[101][101])
{

    int i, j, ok, k;
    int nrap, apa = 65;
    ok = 1;
    for (i = 1; i <= 5; i++)
        for (j = 1; j <= 7; j++)
        {
            // merge si pt caz general matrice de n pe n
            if (a[i][j] > 0 && a[i][j] != 65) // daca e animal
            {
                nrap = 0;
                for (k = j; a[i][k] != -1; k++) //pe linie spre dreapta
                {
                    if (a[i][k] == apa) nrap++;
                    if ((a[i][k] != a[i][j] && a[i][k] > 0 && a[i][k] != 65) || nrap > 1)// nu pot sa am de 2 ori aceeasi piesa
                    {
                        ok = 0;

                        return 0;
                    }
                    if (a[i][k] == 0)a[i][k] = a[i][j];//umplu spatiul gol(0) cu val piesei animal
                }
                for (k = j; a[i][k] != -1; k--) //pe linie spre spre stanga
                {
                    if (a[i][k] == apa) nrap++;
                    if ((a[i][k] != a[i][j] && a[i][k] > 0 && a[i][k] != 65) || nrap > 1)
                    {
                        ok = 0;

                        return 0;
                    }
                    if (a[i][k] == 0)a[i][k] = a[i][j];
                }
                for (k = i; a[k][j] != -1; k++) //pe coloana in jos
                {
                    if (a[k][j] == apa) nrap++;
                    if ((a[k][j] != a[i][j] && a[k][j] > 0 && a[k][j] != 65) || nrap > 1)
                    {
                        ok = 0;

                        return 0;
                    }
                    if (a[k][j] == 0)a[k][j] = a[i][j];
                }
                for (k = i; a[k][j] != -1; k--) //pe coloana in sus
                {
                    if (a[k][j] == apa) nrap++;
                    if ((a[k][j] != a[i][j] && a[k][j] > 0 && a[k][j] != 65) || nrap > 1)
                    {
                        ok = 0;

                        return 0;
                    }
                    if (a[k][j] == 0) a[k][j] = a[i][j];
                }
                int k1 = i;
                int k2 = j;
                while (a[k1][k2] != -1)
                {
                    k1--;
                    k2--;
                    if (a[k1][k2] == apa) nrap++;
                    if ((a[k1][k2] != a[i][j] && a[k1][k2] > 0 && a[k1][k2] != 65) || nrap > 1)
                    {
                        ok = 0;

                        return 0;

                    }
                    if (a[k1][k2] == 0) a[k1][k2] = a[i][j];
                }//spre stanga sus-> diagonala
                k1 = i;
                k2 = j;
                while (a[k1][k2] != -1)
                {
                    k1++;
                    k2++;
                    if (a[k1][k2] == apa) nrap++;
                    if ((a[k1][k2] != a[i][j] && a[k1][k2] > 0 && a[k1][k2] != 65) || nrap > 1)
                    {

                        ok = 0;

                        return 0;

                    }
                    if (a[k1][k2] == 0) a[k1][k2] = a[i][j];
                }//spre dreapta jos-> diagonala
                k1 = i;
                k2 = j;
                while (a[k1][k2] != -1)
                {
                    k1++;
                    k2--;
                    if (a[k1][k2] == apa) nrap++;
                    if ((a[k1][k2] != a[i][j] && a[k1][k2] > 0 && a[k1][k2] != 65) || nrap > 1)
                    {

                        ok = 0;

                        return 0;

                    }
                    if (a[k1][k2] == 0) a[k1][k2] = a[i][j];
                }//spre stanga jos-> diagonala
                k1 = i;
                k2 = j;
                while (a[k1][k2] != -1)
                {
                    k1--;
                    k2++;
                    if (a[k1][k2] == apa) nrap++;
                    if ((a[k1][k2] != a[i][j] && a[k1][k2] > 0 && a[k1][k2] != 65) || nrap > 1)
                    {

                        ok = 0;

                        return 0;

                    }
                    if (a[k1][k2] == 0) a[k1][k2] = a[i][j];
                }//spre dreapta sus-> diagonala
            }

        }

    //ma plimb pe cea ramas nevizitat si verific daca e 0
    for (i = 1; i <= 5; i++)
        for (j = 1; j <= 7; j++)
            if (a[i][j] == 0) gard2(a);
    if (ok) return 1;
}
//
void Game::updateMatrix()
{

    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            currentLevel.setPiesaType(i, j, ShapeType::None);
        }
    }
    for (int i = 0; i <= 6; i++)
        for (int j = 0; j <= 8; j++)
            if (v[i][j] != -1) v[i][j] = 0;
    switch (selectedLevel)
    {
    case 1:///lvl20
        //marcare matrice

        currentLevel.setPiesaType(1, 1, ShapeType::Piesa1);
        saveLevelToFile("level1");
        v[1][1] = 1;
        currentLevel.setPiesaType(3, 1, ShapeType::Piesa1);
        saveLevelToFile("level1");
        v[3][1] = 1; ///cal
        currentLevel.setPiesaType(3, 3, ShapeType::Piesa4);
        saveLevelToFile("level1");
        v[3][3] = 4;
        currentLevel.setPiesaType(1, 7, ShapeType::Piesa4);
        saveLevelToFile("level1");
        v[1][7] = 4;           ///vaca
        currentLevel.setPiesaType(3, 7, ShapeType::Piesa5);
        saveLevelToFile("level1");
        v[3][7] = 5;          ///porc
        currentLevel.setPiesaType(5, 7, ShapeType::Piesa5);
        saveLevelToFile("level1");
        v[5][7] = 5;
        currentLevel.setPiesaType(5, 1, ShapeType::Piesa2);
        saveLevelToFile("level1");
        v[5][1] = 2;                ///oaie
        currentLevel.setPiesaType(5, 3, ShapeType::Piesa2);

        saveLevelToFile("level1");
        v[5][3] = 2;
        //gard
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(0, j, ShapeType::Gard);
            v[0][j] = -1;
        }
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(6, j, ShapeType::Gard);
            v[6][j] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 0, ShapeType::Gard);
            v[j][0] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 8, ShapeType::Gard);
            v[j][8] = -1;
        }


        //bine sau gresit

        if (gard1(v))
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaW);
        }
        else
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaL);
        }
        //restart matrice
        for (int i = 0; i <= 6; i++)
            for (int j = 0; j <= 8; j++)
                v[i][j] = 0;
        break;


    case 2:///lvl30

        currentLevel.setPiesaType(1, 5, ShapeType::Piesa1);
        v[1][5] = 1;
        saveLevelToFile("level2");
        currentLevel.setPiesaType(1, 7, ShapeType::Piesa1);
        v[1][7] = 1;
        saveLevelToFile("level2"); ///cal
        currentLevel.setPiesaType(3, 1, ShapeType::Piesa4);
        v[3][1] = 4;
        saveLevelToFile("level2");
        currentLevel.setPiesaType(5, 1, ShapeType::Piesa4);
        v[5][1] = 4;
        saveLevelToFile("level2");///vaca
        currentLevel.setPiesaType(1, 1, ShapeType::Piesa5);
        v[1][1] = 5;
        saveLevelToFile("level2"); ///porc
        currentLevel.setPiesaType(1, 3, ShapeType::Piesa5);
        v[1][3] = 5;
        saveLevelToFile("level2");
        currentLevel.setPiesaType(3, 7, ShapeType::Piesa2);
        v[3][7] = 2;
        saveLevelToFile("level2");///oaie
        currentLevel.setPiesaType(5, 7, ShapeType::Piesa2);
        v[5][7] = 2;
        saveLevelToFile("level2");
        //gard
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(0, j, ShapeType::Gard);
            v[0][j] = -1;
        }
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(6, j, ShapeType::Gard);
            v[6][j] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 0, ShapeType::Gard);
            v[j][0] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 8, ShapeType::Gard);
            v[j][8] = -1;
        }




        if (gard1(v))
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaW);
        }
        else
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaL);
        }
        //restart matrice
        for (int i = 0; i <= 6; i++)
            for (int j = 0; j <= 8; j++)
                v[i][j] = 0;;
        break;

    case 3:///lvl42
        currentLevel.setPiesaType(1, 1, ShapeType::Piesa3);
        v[1][1] = 65;
        saveLevelToFile("level3");  ///water
        currentLevel.setPiesaType(1, 3, ShapeType::Piesa3);
        v[1][3] = 65;
        saveLevelToFile("level3");
        currentLevel.setPiesaType(3, 5, ShapeType::Piesa4);
        v[3][5] = 4;
        saveLevelToFile("level3");///vaca
        currentLevel.setPiesaType(3, 7, ShapeType::Piesa1);
        v[3][7] = 1;
        saveLevelToFile("level3");///horse
        //gard
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(0, j, ShapeType::Gard);
            v[0][j] = -1;
        }
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(6, j, ShapeType::Gard);
            v[6][j] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 0, ShapeType::Gard);
            v[j][0] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 8, ShapeType::Gard);
            v[j][8] = -1;
        }

        if (gard2(v))
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaW);
        }
        else
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaL);
        }
        //restart matrice
        for (int i = 0; i <= 6; i++)
            for (int j = 0; j <= 8; j++)
                v[i][j] = 0;
        break;

    case 4:///lvl50
        currentLevel.setPiesaType(1, 1, ShapeType::Piesa3);
        v[1][1] = 65;
        saveLevelToFile("level4");  ///water
        currentLevel.setPiesaType(1, 5, ShapeType::Piesa3);
        v[1][5] = 65;
        saveLevelToFile("level4");
        currentLevel.setPiesaType(1, 7, ShapeType::Piesa3);
        v[1][7] = 65;
        saveLevelToFile("level4");
        currentLevel.setPiesaType(5, 1, ShapeType::Piesa4);
        v[5][1] = 4;
        saveLevelToFile("level4");///vaca
        currentLevel.setPiesaType(1, 3, ShapeType::Piesa5);
        v[1][3] = 5;
        saveLevelToFile("level4");///porc
        currentLevel.setPiesaType(5, 3, ShapeType::Piesa1);
        v[5][3] = 1;
        saveLevelToFile("level4");///cal
        //gard
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(0, j, ShapeType::Gard);
            v[0][j] = -1;
        }
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(6, j, ShapeType::Gard);
            v[6][j] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 0, ShapeType::Gard);
            v[j][0] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 8, ShapeType::Gard);
            v[j][8] = -1;
        }

        if (gard2(v))
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaW);
        }
        else
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaL);
        }
        //restart matrice
        for (int i = 0; i <= 6; i++)
            for (int j = 0; j <= 8; j++)
                v[i][j] = 0;
        break;

    case 5:///lvl60
        currentLevel.setPiesaType(1, 7, ShapeType::Piesa3);
        v[1][7] = 65;
        saveLevelToFile("level5");///water
        currentLevel.setPiesaType(5, 3, ShapeType::Piesa3);
        v[5][3] = 65;
        saveLevelToFile("level5");
        currentLevel.setPiesaType(5, 5, ShapeType::Piesa3);
        v[5][5] = 65;
        saveLevelToFile("level5");
        currentLevel.setPiesaType(1, 3, ShapeType::Piesa4);
        v[1][3] = 4;
        saveLevelToFile("level5");///vaca
        currentLevel.setPiesaType(3, 3, ShapeType::Piesa2);
        v[3][3] = 2;
        saveLevelToFile("level5");///oaie
        currentLevel.setPiesaType(5, 7, ShapeType::Piesa1);
        v[5][7] = 1;
        saveLevelToFile("level5");///horse
        //gard
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(0, j, ShapeType::Gard);
            v[0][j] = -1;
        }
        for (int j = 0; j <= 8; j++)
        {
            currentLevel.setPiesaType(6, j, ShapeType::Gard);
            v[6][j] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 0, ShapeType::Gard);
            v[j][0] = -1;
        }
        for (int j = 1; j <= 5; j++)
        {
            currentLevel.setPiesaType(j, 8, ShapeType::Gard);
            v[j][8] = -1;
        }

        if (gard2(v))
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaW);
        }
        else
        {
            for (int k = 0; k <= 6; k++)
                currentLevel.setPiesaType(k, 9, ShapeType::PiesaL);
        }
        //restart matrice
        for (int i = 0; i <= 6; i++)
            for (int j = 0; j <= 8; j++)
                v[i][j] = 0;
        break;
    default:
        break;
    }
}

void Game::render()
{

    window.clear();


    switch (currentState)
    {
    case GameState::MainMenu:
        window.draw(buttons.Player1Button.shape);
        window.draw(buttons.Player1Button.text);
        window.draw(buttons.Player1vsPlayer2Button.shape);
        window.draw(buttons.Player1vsPlayer2Button.text);
        window.draw(buttons.SettingsButton.shape);
        window.draw(buttons.SettingsButton.text);
        window.draw(buttons.AboutButton.shape);
        window.draw(buttons.AboutButton.text);
        break;

    case GameState::Player1:
        window.draw(buttons.BackPlayer1Button.shape);
        window.draw(buttons.BackPlayer1Button.text);
        window.draw(buttons.ChapterButton.shape);
        window.draw(buttons.ChapterButton.text);
        window.draw(buttons.SoloButton.shape);
        window.draw(buttons.SoloButton.text);
        break;

    case GameState::Player1vsPlayer2:
        window.draw(buttons.BackPlayer1vsPlayer2Button.shape);
        window.draw(buttons.BackPlayer1vsPlayer2Button.text);
        window.draw(reviewInputBox);
        window.draw(reviewInputText);


        break;

    case GameState::Settings:
        window.draw(buttons.BackSettingsButton.shape);
        window.draw(buttons.BackSettingsButton.text);
        window.draw(MusicButton);
        window.draw(MusicButtonText);
        window.draw(volumeBar);
        window.draw(volumeDivider);

        break;

    case GameState::About:
        window.draw(buttons.BackAboutButton.shape);
        window.draw(buttons.BackAboutButton.text);
        window.draw(gameRulesText);
        window.draw(horseShape);
        window.draw(sheepShape);
        window.draw(pigShape);
        window.draw(waterBasinShape);
        window.draw(cowShape);
        window.draw(boxRule);
        break;

    case GameState::Chapter:
        window.draw(buttons.BackChapterButton.shape);
        window.draw(buttons.BackChapterButton.text);
        window.draw(buttons.Level1Button.shape);
        window.draw(buttons.Level1Button.text);
        window.draw(buttons.Level2Button.shape);
        window.draw(buttons.Level2Button.text);
        window.draw(buttons.Level3Button.shape);
        window.draw(buttons.Level3Button.text);
        window.draw(buttons.Level4Button.shape);
        window.draw(buttons.Level4Button.text);
        window.draw(buttons.Level5Button.shape);
        window.draw(buttons.Level5Button.text);
        break;

    case GameState::Level1:
        window.draw(buttons.BackChapterButton.shape);
        window.draw(buttons.BackChapterButton.text);
        window.draw(buttons.StartAgainButton.shape);
        window.draw(buttons.StartAgainButton.text);

        selectedLevel = 1;
        updateMatrix();
        drawMatrix();
        if (ok == 1)
        {
            window.clear();
            window.draw(buttons.BackChapterButton.shape);
            window.draw(buttons.BackChapterButton.text);
            window.draw(buttons.StartAgainButton.shape);
            window.draw(buttons.StartAgainButton.text);

            selectedLevel = 1;

            updateMatrix();
            drawMatrix();

        }
        break;

    case GameState::Level2:
        window.draw(buttons.BackChapterButton.shape);
        window.draw(buttons.BackChapterButton.text);
        window.draw(buttons.StartAgainButton.shape);
        window.draw(buttons.StartAgainButton.text);

        selectedLevel = 2;
        updateMatrix();
        drawMatrix();
        if (ok == 1)
        {
            window.clear();
            window.draw(buttons.BackChapterButton.shape);
            window.draw(buttons.BackChapterButton.text);
            window.draw(buttons.StartAgainButton.shape);
            window.draw(buttons.StartAgainButton.text);

            selectedLevel = 2;

            updateMatrix();
            drawMatrix();

        }

        break;
    case GameState::Level3:
        window.draw(buttons.BackChapterButton.shape);
        window.draw(buttons.BackChapterButton.text);
        window.draw(buttons.StartAgainButton.shape);
        window.draw(buttons.StartAgainButton.text);

        selectedLevel = 3;
        updateMatrix();
        drawMatrix();
        if (ok == 1)
        {
            window.clear();
            window.draw(buttons.BackChapterButton.shape);
            window.draw(buttons.BackChapterButton.text);
            window.draw(buttons.StartAgainButton.shape);
            window.draw(buttons.StartAgainButton.text);

            selectedLevel = 3;
            updateMatrix();
            drawMatrix();

        }

        break;
    case GameState::Level4:
        window.draw(buttons.BackChapterButton.shape);
        window.draw(buttons.BackChapterButton.text);
        window.draw(buttons.StartAgainButton.shape);
        window.draw(buttons.StartAgainButton.text);

        selectedLevel = 4;
        updateMatrix();
        drawMatrix();
        if (ok == 1)
        {
            window.clear();
            window.draw(buttons.BackChapterButton.shape);
            window.draw(buttons.BackChapterButton.text);
            window.draw(buttons.StartAgainButton.shape);
            window.draw(buttons.StartAgainButton.text);

            selectedLevel = 4;
            updateMatrix();
            drawMatrix();

        }

        break;
    case GameState::Level5:
        window.draw(buttons.BackChapterButton.shape);
        window.draw(buttons.BackChapterButton.text);
        window.draw(buttons.StartAgainButton.shape);
        window.draw(buttons.StartAgainButton.text);

        selectedLevel = 5;
        updateMatrix();
        drawMatrix();
        if (ok == 1)
        {
            window.clear();
            window.draw(buttons.BackChapterButton.shape);
            window.draw(buttons.BackChapterButton.text);
            window.draw(buttons.StartAgainButton.shape);
            window.draw(buttons.StartAgainButton.text);

            selectedLevel = 5;
            updateMatrix();
            drawMatrix();

        }

        break;
    case GameState::Solo:
        window.draw(buttons.BackSoloButton.shape);
        window.draw(buttons.BackSoloButton.text);

        break;

    default:
        break;
    }


    window.display();
}

void Game::backButtonPress()
{
    switch (currentState)
    {
    case GameState::Player1:
    case GameState::About:
    case GameState::Settings:
    case GameState::Player1vsPlayer2:
        currentState = GameState::MainMenu;


        buttons.Player1Button.shape.setFillColor(sf::Color::Green);
        buttons.Player1vsPlayer2Button.shape.setFillColor(sf::Color::Yellow);
        buttons.AboutButton.shape.setFillColor(sf::Color::Red);
        buttons.SettingsButton.shape.setFillColor(sf::Color::Blue);
        break;

    case GameState::Chapter:
    case GameState::Solo:
        currentState = GameState::Player1;
        break;

    case GameState::Level1:
    case GameState::Level2:
    case GameState::Level3:
    case GameState::Level4:
    case GameState::Level5:
        currentState = GameState::Chapter;

        break;
    case GameState::Output:
        currentState = GameState::Player1vsPlayer2;

    default:
        break;
    }
}
//
void openVisualStudioSolution(const string& solutionPath)
{
    string command = "start devenv " + solutionPath;
    int result = system(command.c_str());

    if (result == 0)
    {
        cout << "Visual Studio merge" << endl;
    }
    else
    {
        cerr << "eroare" << endl;
    }
}

int main()
{
    Game game;

    game.window.create(sf::VideoMode(1600, 1000), "SFML Menu");
    while (game.window.isOpen())
    {

        sf::Event event;

        bool mainMenuButtonPressed = false;
        bool Player1ButtonPressed = false;
        while (game.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                game.window.close();
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Escape)
                {
                    game.backButtonPress();
                }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {

                sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);
                game.handleMusicButtonClick(mousePos);
                game.handleVolumeBar(mousePos);
                if (game.buttons.Player1Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y) && game.currentState == GameState::MainMenu)
                {
                    mainMenuButtonPressed = true;
                    game.currentState = GameState::Player1;
                    cout << "butonul Player1\n";
                }
                else  if (game.buttons.Player1vsPlayer2Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y) && game.currentState == GameState::MainMenu)
                {
                    mainMenuButtonPressed = true;
                    game.currentState = GameState::Player1vsPlayer2;
                    cout << "butonul Player1vsPLayer2\n";


                }

                else if (game.buttons.AboutButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y) && game.currentState == GameState::MainMenu)
                {
                    mainMenuButtonPressed = true;
                    game.currentState = GameState::About;
                    cout << "butonul About\n";
                }
                else  if (game.buttons.SettingsButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y) && game.currentState == GameState::MainMenu)
                {
                    mainMenuButtonPressed = true;
                    game.currentState = GameState::Settings;
                    cout << "butonul Settings\n";
                }
                else if (game.buttons.SoloButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y) && game.currentState == GameState::Player1)
                {
                    Player1ButtonPressed = true;
                    game.currentState = GameState::Solo;
                    std::cout << "butonul Solo\n";


                    std::string mergebineSolutionPath = "C:\\Users\\Utilizator\\Desktop\\inceput\\res\\mergebine\\mergebine.sln";
                    openVisualStudioSolution(mergebineSolutionPath);
                }
                else if (game.buttons.ChapterButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y) && game.currentState == GameState::Player1)
                {
                    Player1ButtonPressed = true;
                    game.currentState = GameState::Chapter;
                    cout << "butonul Chapter\n";
                }



                if (game.currentState == GameState::Chapter)
                {
                    if (game.buttons.Level1Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {


                        cout << "butonul Level 1\n";
                        game.currentState = GameState::Level1;

                    }

                    else if (game.buttons.Level2Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        cout << "butonul Level 2\n";
                        game.currentState = GameState::Level2;
                    }
                    else if (game.buttons.Level3Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        cout << "butonul Level 3\n";
                        game.currentState = GameState::Level3;

                    }
                    else if (game.buttons.Level4Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        cout << "butonul Level 4\n";
                        game.currentState = GameState::Level4;

                    }
                    else if (game.buttons.Level5Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {

                        cout << "butonul Level 5\n";
                        game.currentState = GameState::Level5;

                    }
                }


                ok = 0;



                if (game.buttons.BackPlayer1Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    game.backButtonPress();
                    cout << "butonul BackPlayer1\n";
                }
                else  if (game.buttons.BackPlayer1vsPlayer2Button.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    game.backButtonPress();
                    cout << "butonul BackPlayer1vsPlayer2\n";
                }
                else if (game.buttons.BackSoloButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    game.backButtonPress();
                    cout << "butonul BackSolo\n";
                }
                else  if (game.buttons.BackSettingsButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    game.backButtonPress();
                    cout << "butonul BackSettings\n";
                }
                else  if (game.buttons.BackChapterButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    game.backButtonPress();
                    cout << "butonul BackChapter\n";
                }
                else   if (game.buttons.BackAboutButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    game.backButtonPress();
                    cout << "butonul BackAbout\n";
                }
                else if (game.buttons.StartAgainButton.shape.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    cout << "butonul StartAgain\n";
                    ok = 1;
                }

            }

            else if (event.key.code == sf::Keyboard::Down)
            {

                game.handleTextInput('\n');
            }

            if (game.currentState == GameState::Player1vsPlayer2)
                if (event.type == sf::Event::TextEntered)
                {
                    game.handleTextInput(event.text.unicode);

                }
        }


        game.render();


    }
    return 0;
}



