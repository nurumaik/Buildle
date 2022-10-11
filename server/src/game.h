#pragma once

#include <cinttypes>
#include <chrono>
#include <string>
#include <unordered_set>
#include <buildle.pb.h>

namespace BuildleGame {

class Game {
public:
    Game(bool hard, const std::string& word, const std::string& playerName);
    const std::string& Correct() const;
    const std::string& PlayerName() const;
    ::GuessResponse Guess(const std::string& attempt);
    int32_t Attempts() const;

private:
    bool m_hard;
    int32_t m_attempts;
    const std::string& m_correct; 
    std::string m_playerName;
    std::unordered_set<char> m_chars;
};

}