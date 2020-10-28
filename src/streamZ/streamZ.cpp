//
// Created by emanu on 21-Oct-20.
//

#include "streamZ.h"

StreamZ::StreamZ() :
userManager(UserManager()),
viewerManager(ViewerManager(&userManager)),
streamManager(StreamManager(&viewerManager)),
streamerManager(StreamerManager(&streamManager, &viewerManager, &userManager)),
adminManager( AdminManager(&userManager)),
leaderboardManager(LeaderboardManager(&viewerManager,&streamerManager,&streamManager)){}

//void StreamZ::showActiveStreams() {
//}

//void StreamZ::sortByViews(int order){
    /*sort active streams by view count
     (descending ou ascending according to input: 1 to ascending and -1 to descending)*/
//}

//void StreamZ::filterLanguage(std::string streamLang){
    /*show streams with selected language*/
//}

//void StreamZ::filterAge(unsigned int minAge) {
    /*show streams with age >= minAge*/
//}