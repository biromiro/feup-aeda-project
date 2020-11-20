//
// Created by biromiro on 13/10/20.
//

#ifndef PROJECT_STREAM_H
#define PROJECT_STREAM_H

#include "../../utils/date/date.h"
#include <utility>
#include <iostream>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <map>


class StreamerManager;

/**
 * Defines the type of feedback that can be given to a stream
 */
enum class FeedbackLikeSystem{
    LIKE,
    DISLIKE,
    INVALID_VOTE
};

/**
 * Defines what type of stream an instantiation of the Stream Class is
 */
enum class StreamType{
    PRIVATE,
    PUBLIC,
    FINISHED,
    INVALID
};

/**
 * Defines the genres a stream can be
 */
enum class StreamGenre{
    MUSIC,
    GAMING,
    COOKING,
    TALKSHOW,
    INVALID
};

/**
 * Defines the languages a stream can be in
 */
enum class StreamLanguage{
    AF, AR, AZ, BE, BG, CA, CZ, CY, DA, DE, EL, EN,
    EO, ES, ET, EU, FA ,FI, FO, FR, GL, GU, HE, HI,
    HR, HU, HY, ID, IS, IT, JA, KA, KK, KN, KO, KOK,
    KY, LT, LV, MI ,MK, MN, MR, MS, MT, NB, NL, NN,
    NS, PA, PL, PS, PT_BR, PT_PT, QU, RO, RU, SA ,SE,
    SK, SL, SQ, SR, SV, SW, SYR, TA, TE, TH, TL, TN,
    TR, TT, TS, UK, UR, UZ, YI, XH, ZH,INVALID
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
     [[nodiscard]] virtual enum StreamType getStreamType() const = 0;

    /**
     * Getter of the number of viewers of the stream
     *
     * @return stream's number of viewers
     */
    [[nodiscard]] unsigned int getNumOfViewers() const;

    /**
     * Getter of the minimum age allowed for viewers of the stream
     *
     * @return minimum allowed viewer age
     */
    [[nodiscard]] unsigned int getMinAge() const;

    /**
     * Getter of the stream's title
     *
     * @return stream's title
     */
    [[nodiscard]] std::string getTitle() const;

    /**
     * Getter of the stream's language
     *
     * @return stream's language
     */
    [[nodiscard]] enum StreamLanguage getLanguage() const;

    /**
     * Checks if a viewer can join the stream
     *
     * @param newViewer viewer to check
     * @return true if the viewer meets the requirements to join, false otherwise
     */
    [[nodiscard]] virtual bool canJoin(const std::shared_ptr<Viewer>& newViewer) const;
  
    /**
     * Increases numOfViewers by one
     *
     */
    void newViewerJoin();
  
    /**
     * Decreases numOfViewers by one
     *
     */
    void viewerLeft();

    /**
     * Getter of the stream's date
     *
     * @return stream's date
     */
    [[nodiscard]] Date getStreamDate() const;

    /**
     * Getter of the stream's streamer
     *
     * @return pointer to stream's streamer
     */
    [[nodiscard]] std::shared_ptr<Streamer> getStreamer() const;

    /**
     * Getter of the number of each type of votes (like or dislike) the stream has
     *
     * @return pair with the number of votes of each type
     */
    [[nodiscard]] std::pair<unsigned int, unsigned int> getVotes() const;

    /**
     * Adds a vote to the stream's feedback
     *
     * @param feedback vote (like or dislike) to add
     * @param nickname viewer to add feedback
     * @return true if feedback added is valid (like or dislike), false otherwise
     */
    bool addFeedback(const std::string& nickname, enum FeedbackLikeSystem feedback);

    /**
     * Removes a vote to the stream's feedback
     *
     * @param feedback vote (like or dislike) to remove
     * @param nickname viewer to remove feedback
     * @return true if feedback removed is valid (like or dislike), false otherwise
     */
    bool removeFeedback(const std::string& nickname, enum FeedbackLikeSystem feedback);
    /**
     * Getter of the unique ID of the stream
     *
     * @return stream's unique ID
     */
    [[nodiscard]] unsigned int getUniqueId() const;

    /**
     * Getter of the stream's genre
     *
     * @return stream's genre
     */
    [[nodiscard]] StreamGenre getGenre() const;

    /**
     * Reads saved streams from file
     *
     * @param ifs File to read from
     * @param streamerManager streamerManager to allocate streams to respective streamer
     */
    virtual void readData(std::ifstream& ifs, const std::shared_ptr<StreamerManager>& streamerManager);

    /**
     * Stores and updates saved streams to file
     *
     * @param ofs File to write to
     */
    virtual void writeData(std::ofstream& ofs);

    /**
     * Overload of == operator for pointer to stream
     *
     * @param stream stream to compare with self
     * @return self == stream given
     * */
    bool operator==(const std::shared_ptr<Stream>& stream) const;

    /**
     * Overload of == operator for stream
     *
     * @param stream stream to compare with self
     * @return self == stream given
     * */
    bool operator==(const Stream &rhs) const;

    /**
     * Overload of != operator for stream
     *
     * @param stream stream to compare with self
     * @return self != stream given
     * */
    bool operator!=(const Stream &rhs) const;

    /**
    * Overload of < operator for stream
    *
    * @param stream stream to compare with self
    * @return self < stream given
    * */
    bool operator<(const Stream &rhs) const;

    /**
    * Overload of > operator for stream
    *
    * @param stream stream to compare with self
    * @return self > stream given
    * */
    bool operator>(const Stream &rhs) const;

    /**
    * Overload of <= operator for stream
    *
    * @param stream stream to compare with self
    * @return self <= stream given
    * */
    bool operator<=(const Stream &rhs) const;

    /**
    * Overload of >= operator for stream
    *
    * @param stream stream to compare with self
    * @return self >= stream given
    * */
    bool operator>=(const Stream &rhs) const;

protected:
    explicit Stream(enum StreamType type);
  
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
    unsigned int minAge{};
    enum StreamType type;
    enum StreamGenre genre;
    std::shared_ptr<Streamer> streamer;
    std::pair<unsigned int,unsigned int> votingSystem;
    unsigned int numOfViewers{};
    unsigned int uniqueID{};
    static unsigned int nextID;
    std::map<std::string,FeedbackLikeSystem> feedback;
};

std::ostream& operator<<(std::ostream& out, const StreamLanguage& f);
std::ostream& operator<<(std::ostream& out, const StreamGenre& f);
std::ostream& operator<<(std::ostream& out, const StreamType& f);
std::ostream& operator<<(std::ostream& out, const FeedbackLikeSystem& f);
std::istream& operator>>(std::istream& inf, StreamLanguage& f);
std::istream& operator>>(std::istream& inf, StreamGenre& f);
std::istream& operator>>(std::istream& inf, StreamType& f);
std::istream& operator>>(std::istream& inf, FeedbackLikeSystem& f);
#endif //PROJECT_STREAM_H