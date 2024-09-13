#include "app/app.h"

#include "game/damath.h"

namespace DamathZero::App {

static sf::Font font;

static auto Clear(sf::RenderWindow* window) -> void {
  window->clear();

  sf::RectangleShape background[64];
  for (int i = 0; i < 64; i++) {
    background[i].setPosition(i % 8 * 800 / 8, i / 8 * 800 / 8);
    background[i].setSize(sf::Vector2f(800 / 8, 800 / 8));
    if (i % 2 == i / 8 % 2) {
      background[i].setFillColor(sf::Color::White);
    } else {
      background[i].setFillColor(sf::Color::Black);
    }

    window->draw(background[i]);
  }
}

static auto Display(sf::RenderWindow* window, Game::Board& board) -> void {
  auto size = sf::Vector2f(800, 800);

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      auto piece = board.GetPiece(x, y);
      if (!piece) {
        continue;
      }

      sf::CircleShape shape(800 / 8 / 2 - 10);
      shape.setPosition(x * 800 / 8 + 10, y * 800 / 8 + 10);

      if (piece->color == Game::Piece::Color::Blue) {
        shape.setFillColor(sf::Color::Blue);
      } else {
        shape.setFillColor(sf::Color::Red);
      }
      window->draw(shape);

      sf::Text text{std::to_string((piece->value)), font, 60};
      text.setFillColor(sf::Color::White);
      text.setOrigin(text.getGlobalBounds().getSize() / 2.f +
                     text.getLocalBounds().getPosition());
      text.setPosition(x * 800 / 8 + 50, y * 800 / 8 + 50);

      window->draw(text);
    }
  }
}

auto Run() -> int {
  Game::Damath game{};

  if (!font.loadFromFile("res/fonts/Akrobat-Black.ttf")) {
    return EXIT_FAILURE;
  }

  sf::RenderWindow window(sf::VideoMode(800, 800), "damath.ai",
                          sf::Style::Close, sf::ContextSettings(24, 8, 4));

  sf::View view{sf::FloatRect{0, 0, 800, 800}};

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    sf::Event event;
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.setView(view);

    Clear(&window);

    Display(&window, game.board());

    window.setView(window.getDefaultView());

    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}

}  // namespace DamathZero::App
