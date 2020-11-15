#include <iostream>
#include "./model/stream/stream.h"
#include "./model/user/user.h"
#include "./model/streamZ/streamZ.h"
#include "./utils/date/date.h"
#include "fstream"

int main() {
    StreamZ twitch = StreamZ();

    twitch.initialize();

    Date birthDate("20/10/2001");

    twitch.getAdminManager()->build(birthDate,"The Admin", "admin", "admin");

    std::cout << twitch.getLeaderboardManager()->sortStreamers();
    std::cout << twitch.getLeaderboardManager()->sortViewers();
    std::cout << twitch.getLeaderboardManager()->sortStreams();

    twitch.finish();
    return 0;
}
