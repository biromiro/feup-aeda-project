#include <iostream>
#include "./stream/stream.h"
#include "./user/user.h"
#include "./streamZ/streamZ.h"
#include "./utils/date/date.h"
#include "fstream"

int main() {
    StreamZ twitch = StreamZ();

    twitch.initialize();

    Date birthDate(1992,7,29);
    (twitch.getStreamerManager())->build(birthDate,"João Costa", "jpcosta");
    std::cout << twitch.getLeaderboardManager()->sortStreamers();

    twitch.finish();
    return 0;
}
