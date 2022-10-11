#include <buildle.pb.h>
#include <buildle.grpc.pb.h>

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <iostream>

void renderResult(decltype(buildle::GuessResponseNormal().result())& result) {
    for (auto res: result) {
        if (res == ::buildle::GuessResult::MATCH) {
            std::cout << "*";
        } else if (res == ::buildle::GuessResult::PARTIAL_MATCH) {
            std::cout << "/";
        } else {
            std::cout << ".";
        }
    }
}

int main() {
    // Call
    auto channel = grpc::CreateChannel("localhost:42069", grpc::InsecureChannelCredentials());

    std::unique_ptr<buildle::Buildle::Stub> stub = buildle::Buildle::NewStub(channel);

    ::buildle::StartRequest startReq;
    ::buildle::StartResponse startResp;

    ::buildle::GuessRequest guessReq;
    ::buildle::GuessResponse guessResp;

    std::cout << "Guess the build system you will be using in your next C++ project" << std::endl;

    while (true) {
        grpc::ClientContext context;

        std::cout << "Enter name: " << std::endl;
        std::cin >> *startReq.mutable_name();
        startReq.set_hard(false);  // TODO hard

        ::grpc::Status status = stub->Start(&context, startReq, &startResp);

        if (!status.ok()) {
            std::cout << "Error: <" << status.error_code() << "> " << status.error_message() << std::endl;
            continue;
        }

        bool won = false;

        std::cout << startResp.letters() << " letters" << std::endl;
        std::cout << "You have " << startResp.attempts() << " attempts" << std::endl;
        int32_t session = startResp.session();
        std::cout << "You have " << session << " session" << std::endl;

        while (!won) {
            grpc::ClientContext context;
            std::cout << "Enter your guess: " << std::endl;
            std::string guess;
            std::cin >> guess;

            guessReq.set_attempt(guess);
            guessReq.set_session(session);

            ::grpc::Status status = stub->Guess(&context, guessReq, &guessResp);

            if (!status.ok()) {
                std::cout << "Error: <" << status.error_code() << "> " << status.error_message() << std::endl;
                continue;
            }

            if (guessResp.has_win()) {
                std::cout << "YOU WON!!!\n\n\n\n";
                break;
            } else if (guessResp.has_keep_guessing()) {
                const auto& resp = guessResp.keep_guessing();
                renderResult(resp.result());
                std::cout << std::endl;
                std::cout << resp.attempts() << " attempts left" << std::endl;
            } else if (guessResp.has_loss()) {
                const auto& resp = guessResp.loss();
                renderResult(resp.result());
                std::cout << std::endl;
                std::cout << "You lost" << std::endl;
                std::cout << "Correct build was " << resp.correct_word() << std::endl;
            }
        }
    }
}