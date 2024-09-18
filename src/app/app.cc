module;

#include <SFML/Graphics.hpp>

#include "utils/utils.h"

export module app;

import damath;
import std;

namespace DamathZero::App {

static sf::Font font;

static std::map<Game::Operation, std::string> operation_map = {
    {Game::Operation::Plus, "+"},
    {Game::Operation::Minus, "-"},
    {Game::Operation::Times, "*"},
    {Game::Operation::Divide, "/"},
};

static auto Clear(sf::RenderWindow* window, Game::Board& board) -> void {
  window->clear();

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      sf::RectangleShape background;
      background.setPosition(x * 800 / 8, y * 800 / 8);
      background.setSize(sf::Vector2f(100, 100));
      if ((y * 8 + x) % 2 == (y * 8 + x) / 8 % 2) {
        background.setFillColor(sf::Color::White);
      } else {
        background.setFillColor(sf::Color::Black);
      }

      window->draw(background);

      auto op = board.GetOperation(x, y);
      if (!op) {
        continue;
      }

      sf::Text text{operation_map[*op], font, 60};
      text.setFillColor(sf::Color::Black);
      text.setOrigin(text.getGlobalBounds().getSize() / 2.f +
                     text.getLocalBounds().getPosition());
      text.setPosition(x * 800 / 8 + 50, y * 800 / 8 + 50);

      window->draw(text);
    }
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

export auto Run() -> int {
  Game::Damath game{};

  if (!(font.loadFromFile(Utils::resourcePath() / "Akrobat-Black.ttf"))) {
    return EXIT_FAILURE;
  }

  sf::RenderWindow window(sf::VideoMode(800, 800), "DamathZero",
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

    Clear(&window, game.board());

    Display(&window, game.board());

    window.setView(window.getDefaultView());

    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}

}  // namespace DamathZero::App
