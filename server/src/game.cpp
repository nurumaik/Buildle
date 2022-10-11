#include "game.h"
#include "config.h"

namespace BuildleGame {

Game::Game(bool hard, const std::string& word, const std::string& playerName)
: m_hard(hard)
, m_attempts(MaxAttempts)
, m_correct(word)
, m_playerName(playerName)
{
    for (char c: m_correct) {
        m_chars.insert(c);
    }
}

const std::string& Game::Correct() const {
    return m_correct;
}

int32_t Game::Attempts() const {
    return m_attempts;
}

::GuessResponse Game::Guess(const std::string& attempt) {
    if (attempt.size() != m_correct.size()) {
        throw "TODO ERROR";
    }
    ::GuessResponse response;
    std::vector<::GuessResult> result;
    bool fullGuess = true;
    for (int i = 0; i < attempt.size(); ++i) {
        if (attempt[i] == m_correct[i]) {
            result.push_back(::GuessResult::MATCH);
        } else if (m_chars.contains(attempt[i])) {
            fullGuess = false;
            result.push_back(::GuessResult::PARTIAL_MATCH);
        } else {
            fullGuess = false;
            result.push_back(::GuessResult::NO_MATCH);
        }
    }
    m_attempts--;
    if (fullGuess) {
        response.mutable_win();
    } else if (m_attempts == 0) {
        ::GuessResponseLoss* loss = response.mutable_loss();
        loss->set_correct_word(m_correct);
        for (auto res: result) {
            loss->add_result(res);
        }
    } else {
        ::GuessResponseNormal* normal = response.mutable_keep_guessing();
        normal->set_attempts(m_attempts);
        for (auto res: result) {
            normal->add_result(res);
        }
    }
    return response;
}

}