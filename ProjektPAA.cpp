#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MARGINES = 50;
const int OKNO_SZEROKOSC = 800;
const int OKNO_WYSOKOSC = 800;

// Funkcja do rysowania planszy
void rysujPlansze(sf::RenderWindow& okno, int rozmiar, const vector<vector<char>>& plansza, const sf::Texture& textureX, const sf::Texture& textureO, int ROZMIAR_POLA) {
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            sf::RectangleShape pole(sf::Vector2f(ROZMIAR_POLA, ROZMIAR_POLA));
            pole.setPosition(j * ROZMIAR_POLA + MARGINES, i * ROZMIAR_POLA + MARGINES);
            pole.setOutlineThickness(2);
            pole.setOutlineColor(sf::Color::Black);
            pole.setFillColor(sf::Color::White);
            okno.draw(pole);

            if (plansza[i][j] == 'X') {
                sf::Sprite sprite;
                sprite.setTexture(textureX);
                float scaleX = static_cast<float>(ROZMIAR_POLA) / textureX.getSize().x;
                float scaleY = static_cast<float>(ROZMIAR_POLA) / textureX.getSize().y;
                sprite.setScale(scaleX, scaleY);
                sprite.setPosition(j * ROZMIAR_POLA + MARGINES, i * ROZMIAR_POLA + MARGINES);
                okno.draw(sprite);
            }
            else if (plansza[i][j] == 'O') {
                sf::Sprite sprite;
                sprite.setTexture(textureO);
                float scaleX = static_cast<float>(ROZMIAR_POLA) / textureO.getSize().x;
                float scaleY = static_cast<float>(ROZMIAR_POLA) / textureO.getSize().y;
                sprite.setScale(scaleX, scaleY);
                sprite.setPosition(j * ROZMIAR_POLA + MARGINES, i * ROZMIAR_POLA + MARGINES);
                okno.draw(sprite);
            }
        }
    }
}
char sprawdzZwyciestwo(const vector<vector<char>>& plansza, int a) {
    int rozmiar = a; // Pobieramy rozmiar planszy

    // Sprawdzanie zwycięstwa w rzędach
    for (int i = 0; i < rozmiar; ++i) {
        char pierwszyZnakWiersza = plansza[i][0];
        bool zwyciestwoWiersza = true;
        for (int j = 1; j < rozmiar; ++j) {
            if (plansza[i][j] != pierwszyZnakWiersza || pierwszyZnakWiersza == '-') {
                zwyciestwoWiersza = false;
                break;
            }
        }
        if (zwyciestwoWiersza && pierwszyZnakWiersza != '-') {
            return pierwszyZnakWiersza;
        }
    }

    // Sprawdzanie zwycięstwa w kolumnach
    for (int i = 0; i < rozmiar; ++i) {
        char pierwszyZnakKolumny = plansza[0][i];
        bool zwyciestwoKolumny = true;
        for (int j = 1; j < rozmiar; ++j) {
            if (plansza[j][i] != pierwszyZnakKolumny || pierwszyZnakKolumny == '-') {
                zwyciestwoKolumny = false;
                break;
            }
        }
        if (zwyciestwoKolumny && pierwszyZnakKolumny != '-') {
            return pierwszyZnakKolumny;
        }
    }

    // Sprawdzanie zwycięstwa na przekątnych
    char pierwszyZnakPrzekatnej1 = plansza[0][0];
    bool zwyciestwoPrzekatnej1 = true;
    for (int i = 1; i < rozmiar; ++i) {
        if (plansza[i][i] != pierwszyZnakPrzekatnej1 || pierwszyZnakPrzekatnej1 == '-') {
            zwyciestwoPrzekatnej1 = false;
            break;
        }
    }
    if (zwyciestwoPrzekatnej1 && pierwszyZnakPrzekatnej1 != '-') {
        return pierwszyZnakPrzekatnej1;
    }

    char pierwszyZnakPrzekatnej2 = plansza[0][rozmiar - 1];
    bool zwyciestwoPrzekatnej2 = true;
    for (int i = 1; i < rozmiar; ++i) {
        if (plansza[i][rozmiar - 1 - i] != pierwszyZnakPrzekatnej2 || pierwszyZnakPrzekatnej2 == '-') {
            zwyciestwoPrzekatnej2 = false;
            break;
        }
    }
    if (zwyciestwoPrzekatnej2 && pierwszyZnakPrzekatnej2 != '-') {
        return pierwszyZnakPrzekatnej2;
    }

    // Sprawdzanie remisu
    bool czyRemis = true;
    for (int i = 0; i < rozmiar; ++i) {
        for (int j = 0; j < rozmiar; ++j) {
            if (plansza[i][j] == '-') {
                czyRemis = false;
                break;
            }
        }
    }
    if (czyRemis) {
        return 'D'; // Remis
    }

    // Brak zwycięzcy
    return '-';
}
bool handleNextRoundClick() {
    // Resetowanie zmiennych
    return true;
}
void handleExitClick(sf::RenderWindow& window) {
    window.close();
}
bool gamestate = true;
int main() {
    while (gamestate) {
        sf::RenderWindow okno(sf::VideoMode(OKNO_SZEROKOSC, OKNO_WYSOKOSC), "Podaj wymiar planszy");

        sf::Font font;
        if (!font.loadFromFile("C:/Users/jakub/Desktop/PAA3/fonts/arial.ttf")) {
            cout << "Nie można wczytać czcionki." << endl;
            return -1;
        }

        sf::Text tekst;
        tekst.setFont(font);
        tekst.setString("Podaj wymiar planszy:");
        tekst.setCharacterSize(24);
        tekst.setFillColor(sf::Color::Black);
        tekst.setPosition(50, 50);

        sf::RectangleShape inputBox(sf::Vector2f(200, 50));
        inputBox.setPosition(50, 100);
        inputBox.setFillColor(sf::Color::White);
        inputBox.setOutlineThickness(2);
        inputBox.setOutlineColor(sf::Color::Black);

        sf::Text inputText;
        inputText.setFont(font);
        inputText.setCharacterSize(24);
        inputText.setFillColor(sf::Color::Black);
        inputText.setPosition(60, 105);
        string inputString;

        sf::RectangleShape button(sf::Vector2f(100, 50));
        button.setPosition(50, 200);
        button.setFillColor(sf::Color::Green);

        sf::Text buttonText;
        buttonText.setFont(font);
        buttonText.setString("OK");
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::Black);
        buttonText.setPosition(75, 210);

        bool enterPressed = false;
        int a = 0;
        gamestate = false;
        while (okno.isOpen()) {
            sf::Event zdarzenie;
            while (okno.pollEvent(zdarzenie)) {
                if (zdarzenie.type == sf::Event::Closed) {
                    okno.close();
                }
                if (zdarzenie.type == sf::Event::MouseButtonPressed) {
                    if (zdarzenie.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(okno);
                        if (button.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            if (!inputString.empty()) {
                                a = stoi(inputString);
                                enterPressed = true;
                                okno.close();
                            }
                        }
                    }
                }
                // Obsługa wprowadzania tekstu
                if (zdarzenie.type == sf::Event::TextEntered) {
                    if (zdarzenie.text.unicode >= '0' && zdarzenie.text.unicode <= '9') {
                        inputString += static_cast<char>(zdarzenie.text.unicode);
                        inputText.setString(inputString);
                    }
                    else if (zdarzenie.text.unicode == '\b' && !inputString.empty()) {
                        inputString.pop_back();
                        inputText.setString(inputString);
                    }
                }
            }
            okno.clear(sf::Color::White);
            okno.draw(tekst);
            okno.draw(inputBox);
            okno.draw(inputText);
            okno.draw(button);
            okno.draw(buttonText);
            okno.display();
        }
        if (enterPressed) {
            if (a <= 0) {
                cout << "Podano niepoprawny wymiar planszy." << endl;
                return 1;
            }
            int ROZMIAR_POLA = (OKNO_SZEROKOSC - 2 * MARGINES) / a;
            vector<vector<char>> plansza(a, vector<char>(a, '-'));

            sf::Texture textureO;
            if (!textureO.loadFromFile("C:/Users/jakub/Desktop/PAA3/Resources/circle.png")) {
                cout << "Nie można wczytać tekstury O." << endl;
                return -1;
            }
            sf::Texture textureX;
            if (!textureX.loadFromFile("C:/Users/jakub/Desktop/PAA3/Resources/cross.png")) {
                cout << "Nie można wczytać tekstury X." << endl;
                return -1;
            }
            sf::Text wynikTekst;
            wynikTekst.setFont(font);
            wynikTekst.setCharacterSize(30);
            wynikTekst.setPosition(OKNO_SZEROKOSC / 2 - 100, OKNO_WYSOKOSC - 50);
            bool isXTurn = true;
            sf::RenderWindow gra(sf::VideoMode(OKNO_SZEROKOSC, OKNO_WYSOKOSC), "Kółko i krzyżyk");
            bool graZakonczona = false;
            while (gra.isOpen() && !graZakonczona) {
                sf::Event zdarzenie;
                while (gra.pollEvent(zdarzenie)) {
                    if (zdarzenie.type == sf::Event::Closed) {
                        gra.close();
                    }
                    if (zdarzenie.type == sf::Event::MouseButtonPressed) {
                        if (zdarzenie.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i pozycjaKlikniecia = sf::Mouse::getPosition(gra);
                            int x = (pozycjaKlikniecia.x - MARGINES) / ROZMIAR_POLA;
                            int y = (pozycjaKlikniecia.y - MARGINES) / ROZMIAR_POLA;

                            if (x >= 0 && x < a && y >= 0 && y < a && plansza[y][x] == '-') {
                                if (isXTurn) {
                                    plansza[y][x] = 'X';
                                }
                                else {
                                    plansza[y][x] = 'O';
                                }
                                isXTurn = !isXTurn;

                                char wynik = sprawdzZwyciestwo(plansza, a);
                                if (wynik == 'X') {
                                    wynikTekst.setString("Wygrał gracz X!");
                                    graZakonczona = true;
                                }
                                else if (wynik == 'O') {
                                    wynikTekst.setString("Wygrał gracz O!");
                                    graZakonczona = true;
                                }
                                else if (wynik == 'D') {
                                    wynikTekst.setString("Remis!");
                                    graZakonczona = true;
                                }
                                else {
                                    wynikTekst.setString("chujh");
                                }

                            }
                        }
                    }
                }

                gra.clear(sf::Color::White);
                rysujPlansze(gra, a, plansza, textureX, textureO, ROZMIAR_POLA);
                gra.display();

            }
            sf::RenderWindow wynikOkno(sf::VideoMode(400, 200), "Wynik gry");

            sf::Text wynikWiadomosc;
            wynikWiadomosc.setFont(font);
            wynikWiadomosc.setCharacterSize(24);
            wynikWiadomosc.setFillColor(sf::Color::Black);

            // Ustawienie tekstu w zależności od wyniku gry
            if (wynikTekst.getString() == "Wygrał gracz X!") {
                wynikWiadomosc.setString("Wygrał gracz X!");
            }
            else if (wynikTekst.getString() == "Wygrał gracz O!") {
                wynikWiadomosc.setString("Wygrał gracz O!");
            }
            else if (wynikTekst.getString() == "Remis!") {
                wynikWiadomosc.setString("Remis!");
            }
            else {
                wynikWiadomosc.setString("Błąd - nieprawidłowy wynik!");
            }

            wynikWiadomosc.setPosition(50, 50);
            sf::RectangleShape buttonNextRound(sf::Vector2f(150, 50));
            buttonNextRound.setPosition(50, 120);
            buttonNextRound.setFillColor(sf::Color::Green);

            sf::Text buttonTextNextRound;
            buttonTextNextRound.setFont(font);
            buttonTextNextRound.setString("Następna runda");
            buttonTextNextRound.setCharacterSize(16);
            buttonTextNextRound.setFillColor(sf::Color::Black);
            buttonTextNextRound.setPosition(60, 130);

            sf::RectangleShape buttonExit(sf::Vector2f(100, 50));
            buttonExit.setPosition(220, 120);
            buttonExit.setFillColor(sf::Color::Red);

            sf::Text buttonTextExit;
            buttonTextExit.setFont(font);
            buttonTextExit.setString("Zamknij");
            buttonTextExit.setCharacterSize(16);
            buttonTextExit.setFillColor(sf::Color::Black);
            buttonTextExit.setPosition(230, 130);
            while (wynikOkno.isOpen()) {
                sf::Event event;
                while (wynikOkno.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        wynikOkno.close();
                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            sf::Vector2i mousePos = sf::Mouse::getPosition(wynikOkno);
                            if (buttonNextRound.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                gamestate = handleNextRoundClick();
                                wynikOkno.close();
                            }
                            else if (buttonExit.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                handleExitClick(wynikOkno);
                            }
                        }
                    }
                }

                wynikOkno.clear(sf::Color::White);
                wynikOkno.draw(wynikWiadomosc);
                wynikOkno.draw(buttonNextRound);
                wynikOkno.draw(buttonTextNextRound);
                wynikOkno.draw(buttonExit);
                wynikOkno.draw(buttonTextExit);
                wynikOkno.display();
            }
        }
    }
    return 0;

}