#include <iostream>
#include "./stream/stream.h"
#include "./user/user.h"
#include "./streamZ/streamZ.h"
#include "./utils/date/date.h"

int main() {
    Date date, birthDate(2001,4,26);
    std::cout << timeElapsed(date,birthDate) << std::endl;
    return 0;
}
