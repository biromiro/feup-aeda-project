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
#include <fstream>

class StreamerManager;

/**
 * Defines the type of feedback that can be given to a stream
 */
enum FeedbackLikeSystem{
    LIKE,
    DISLIKE,
    INVALID_VOTE
};

/**
 * Defines what type of stream an instantiation of the Stream Class is
 */
enum StreamType{
    PRIVATE,
    PUBLIC,
    FINISHED
};

/**
 * Defines the genres a stream can be
 */
enum StreamGenre{
    MUSIC,
    GAMING,
    COOKING,
    TALKSHOW
};

/**
 * Defines the languages a stream can be in
 */
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
    /**
     * Placeholder for getter of the stream's type
     *
     * @return 0
     */
     virtual enum StreamType getStreamType() const = 0;

    /**
     * Getter of the number of viewers of the stream
     *
     * @return stream's number of viewers
     */
    unsigned int getNumOfViewers() const;

    /**
     * Getter of the minimum age allowed for viewers of the stream
     *
     * @return minimum allowed viewer age
     */
    unsigned int getMinAge() const;

    /**
     * Getter of the stream's title
     *
     * @return stream's title
     */
    std::string getTitle() const;

    /**
     * Getter of the stream's language
     *
     * @return stream's language
     */
    enum StreamLanguage getLanguage() const;

    /**
     * Checks if a viewer can join the stream
     *
     * @param newViewer viewer to check
     * @return true if the viewer meets the requirements to join, false otherwise
     */
    virtual bool canJoin(const std::shared_ptr<Viewer>& newViewer) const;
  
    void newViewerJoin();
  
    void viewerLeft();

    /**
     * Getter of the stream's date
     *
     * @return stream's date
     */
    Date getStreamDate() const;

    /**
     * Getter of the stream's streamer
     *
     * @return pointer to stream's streamer
     */
    std::shared_ptr<Streamer> getStreamer() const;

    /**
     * Getter of the number of each type of votes (like or dislike) the stream has
     *
     * @return pair with the number of votes of each type
     */
    std::pair<unsigned int, unsigned int> getVotes() const;

    /**
     * Adds a vote to the stream's feedback
     *
     * @param feedback vote (like or dislike) to add
     * @return true if feedback added is valid (like or dislike), false otherwise
     */
    bool addFeedback(enum FeedbackLikeSystem feedback);

    /**
     * Sets/Updates the number of viewers of the stream
     *
     * @param numOfViewers stream's new number of viewers
     */
    void setNumOfViewers(unsigned int numOfViewers);

    /**
     * Getter of the unique ID of the stream
     *
     * @return stream's unique ID
     */
    unsigned int getUniqueId() const;

    /**
     * Getter of the stream's genre
     *
     * @return stream's genre
     */
    StreamGenre getGenre() const;
  
    void readData(std::ifstream& ifs, std::shared_ptr<StreamerManager> streamerManager);

    void writeData(std::ofstream& ofs);


    /**
     * Getter of the stream's type
     *
     * @return stream's type
     */
    StreamType getType() const;
  
    bool operator==(std::shared_ptr<Stream> stream) const;
    
    bool operator==(const Stream &rhs) const;
    bool operator!=(const Stream &rhs) const;
    bool operator<(const Stream &rhs) const;
    bool operator>(const Stream &rhs) const;
    bool operator<=(const Stream &rhs) const;
    bool operator>=(const Stream &rhs) const;

protected:
    Stream(enum StreamType type);
  
    /**
     * Constructor of the Stream class
     *
     * @param title title of the stream
     * @param lang language the stream is in
     * @param minAge minimum viewer age allowed
     * @param type type of the stream
     * @param genre genre of the stream
     * @param streamer streamer of the stream
     */
    Stream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, std::shared_ptr<Streamer> streamer);

    std::string title;
    Date streamDate;
    enum StreamLanguage language;
    unsigned int minAge;
    enum StreamType type;
    enum StreamGenre genre;
    std::shared_ptr<Streamer> streamer;
    std::pair<unsigned int,unsigned int> votingSystem;
    unsigned int numOfViewers;
    unsigned int uniqueID;
    static unsigned int nextID;
};

std::ostream& operator<<(std::ostream& out, const StreamLanguage& f);
std::ostream& operator<<(std::ostream& out, const StreamGenre& f);
std::ostream& operator<<(std::ostream& out, const StreamType& f);
std::istream& operator>>(std::istream& inf, StreamLanguage& f);
std::istream& operator>>(std::istream& inf, StreamGenre& f);
std::istream& operator>>(std::istream& inf, StreamType& f);
#endif //PROJECT_STREAM_H