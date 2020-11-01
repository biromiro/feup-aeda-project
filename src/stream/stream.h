//
// Created by biromiro on 13/10/20.
//

#ifndef PROJECT_STREAM_H
#define PROJECT_STREAM_H


#include "../user/user.h"
#include "../utils/date/date.h"
#include <utility>
#include <iostream>
#include <memory>

enum FeedbackLikeSystem{
    LIKE,
    DISLIKE,
    INVALID_VOTE
};

enum StreamType{
    PRIVATE,
    PUBLIC
};

enum StreamLanguage{
    AF, AR, AZ, BE, BG, CA, CZ, CY, DA, DE, EL, EN,
    EO, ES, ET, EU, FA ,FI, FO, FR, GL, GU, HE, HI,
    HR, HU, HY, ID, IS, IT, JA, KA, KK, KN, KO, KOK,
    KY, LT, LV, MI ,MK, MN, MR, MS, MT, NB, NL, NN,
    NS, PA, PL, PS, PT_BR, PT_PT, QU, RO, RU, SA ,SE,
    SK, SL, SQ, SR, SV, SW, SYR, TA, TE, TH, TL, TN,
    TR, TT, TS, UK, UR, UZ, YI, XH, ZH
};

class Viewer;
class Streamer;

class Stream {
public:
    virtual enum StreamType getStreamType() const = 0;
    unsigned int getNumOfViewers() const;
    unsigned int getMinAge() const;
    std::string getTitle() const;
    enum StreamLanguage getLanguage() const;
    virtual bool canJoin(std::shared_ptr<Viewer> newViewer) const;
    Date getStreamDate() const;
    std::shared_ptr<Streamer> getStreamer() const;
    std::pair<unsigned int, unsigned int> getVotes() const;
    unsigned int getViewerCount() const;
    bool addFeedback(enum FeedbackLikeSystem feedback);
    void setNumOfViewers(unsigned int numOfViewers);
    unsigned int getUniqueId() const;
    bool operator==(std::shared_ptr<Stream> stream) const;
protected:
    Stream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, std::shared_ptr<Streamer> streamer);
    std::string title;
    Date streamDate;
    enum StreamLanguage language;
    unsigned int minAge;
    enum StreamType type;
    std::shared_ptr<Streamer> streamer;
    std::pair<unsigned int,unsigned int> votingSystem;
    unsigned int uniqueViewerCount;
    unsigned int numOfViewers;
    unsigned int uniqueID;
    static unsigned int nextID;
};

#endif //PROJECT_STREAM_H