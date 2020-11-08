#include <iostream>
#include "./stream/stream.h"
#include "./user/user.h"
#include "./streamZ/streamZ.h"
#include "./utils/date/date.h"
#include "fstream"

int main() {
    StreamZ twitch = StreamZ();

    twitch.initialize();

    std::cout << twitch.getLeaderboardManager()->sortStreamers();
    std::cout << twitch.getLeaderboardManager()->sortViewers();
    std::cout << twitch.getLeaderboardManager()->sortStreams();

    twitch.finish();
    return 0;
}
