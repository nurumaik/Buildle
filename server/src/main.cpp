#include <buildle.pb.h>
#include <buildle.grpc.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include "game.h"
#include "config.h"

#include <random>
#include <unordered_map>

class BuildleService: public Buildle::Service {
private:
    std::random_device m_rd;
    std::default_random_engine m_engine;
    std::uniform_int_distribution<int> m_words;
    std::uniform_int_distribution<int> m_sessions;

    std::unordered_map<std::int32_t, BuildleGame::Game> m_games;

public:
    BuildleService()
    : m_engine(m_rd())
    , m_words(0, BuildleGame::Builds.size())
    , m_sessions(0, std::numeric_limits<int32_t>::max()) {}

    // Start a new game
    virtual ::grpc::Status Start(::grpc::ServerContext* context, const ::StartRequest* request, ::StartResponse* response) {
        if (m_games.size() == std::numeric_limits<int32_t>::max()) {
            // Holy shit
            throw "TODO ERROR";
        }
        int32_t session = m_sessions(m_engine);
        while (m_games.contains(session)) {
            session = m_sessions(m_engine);
        }
        BuildleGame::Game game(request->hard(), BuildleGame::Builds[m_words(m_engine)], request->name());
        response->set_letters(game.Correct().size());
        response->set_attempts(game.Attempts());
        m_games.emplace(session, game);
        response->set_session(session);
        return ::grpc::Status::OK;
    }

    // Attempt to guess a word
    virtual ::grpc::Status Guess(::grpc::ServerContext* context, const ::GuessRequest* request, ::GuessResponse* response) {
        int32_t session = request->session();
        auto game = m_games.find(session);

        if (game == std::end(m_games)) {
            throw "TODO ERROR";
        }

        response->CopyFrom(game->second.Guess(request->attempt()));
        if (response->has_win() || response->has_loss()) {
            m_games.erase(game);
        }

        return ::grpc::Status::OK;
    }
};

int main() {
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:42069", grpc::InsecureServerCredentials());

    BuildleService service;
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
}