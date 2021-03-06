//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"
#include "../../user/viewer/viewer.h"
#include "../../../exception/nicknameAlreadyAdded/nicknameAlreadyAdded.h"
#include "../../../exception/nicknameNotFound/nicknameNotFound.h"
#include <vector>
#include <fstream>
#include <map>

#ifndef PROJECT_PRIVATESTREAM_H
#define PROJECT_PRIVATESTREAM_H

class Viewer;

/**
 * @file privateStream.cpp
 *
 * @brief Class representing a private stream object
 *
 * @ingroup stream
 */

/**
 * Implementation of the class private stream
 *
 * A private stream is an object, derived from stream, which has special characteristics, such as a limited viewer count and whitelist, and
 * allow viewers to comment on it
 */
class PrivateStream: public Stream {
public:
    PrivateStream();
  
    /**
     * Constructor of the PrivateStream class
     *
     * @param title title of the private stream
     * @param lang language the private stream is in
     * @param minAge minimum viewer age allowed
     * @param genre genre of the private stream
     * @param streamer streamer of private the stream
     */
    PrivateStream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamGenre genre, std::shared_ptr<Streamer> streamer);

    /**
     * Getter of the private stream's type
     *
     * @return private stream's type
     */
    [[nodiscard]] enum StreamType getStreamType() const override;

    /**
     * Getter of the private stream's whitelist (nickname of allowed viewers)
     *
     * @return private stream's whitelist
     */
    [[nodiscard]] std::vector<std::string> getWhitelist() const;

    /**
     * Getter of the private stream's maximum number of viewers
     *
     * @return private stream's maximum number of viewers
     */
    [[nodiscard]] unsigned int getMaxNumViewers() const;

    /**
     * Getter of the private stream's comments
     *
     * @return vector of private stream's comments
     */
    [[nodiscard]] std::map<std::string,std::string> getComments() const;

    /**
     * Adds a viewer to the whitelist (using his nickname)
     *
     * @param v viewer whose nickname is to be added to the whitelist
     * @return true if viewer's nickname is successfully added, false if nickname is already in whitelist
     */
    bool addToWhitelist(const std::shared_ptr<Viewer>& v);

    /**

     * Removes a viewer from the whitelist (using his nickname)
     *
     * @param v viewer whose nickname is to be removed from the whitelist
     * @return true if a viewer's nickname is successfully removed, false if nickname isn't in whitelist
     */
    bool removeFromWhitelist(const std::shared_ptr<Viewer>& v);

    /**

     * Sets/Updates the maximum number of viewers allowed in the private stream
     *
     * @param maxNumViewers new maximum number of viewers of the private stream
     */
    void setMaxNumViewers(unsigned int maxNumViewers);

    /**
     * Adds a comment to the map of the private stream's comments
     *
     * @param comment comment to add to the vector
     * @param nickname who's commenting
     */
    void addComment(const std::string& nickname, const std::string& comment);

    /**
     * Checks if a viewer can join the private stream
     *
     * @param newViewer viewer to check
     * @return true if the viewer can join the private stream, false otherwise
     */
    [[nodiscard]] bool canJoin(const std::shared_ptr<Viewer>& newViewer) const override;

    /**
     * Loads privateStreams from file and relates them to the respective streamer
     *
     * @param ifs File to read from
     * @param streamerManager streamerManager to update streamers with added streams
     * */
    void readData(std::ifstream& ifs, const std::shared_ptr<StreamerManager>& streamerManager) override;

    /**
    * Updates and saves to file the privateStreams
    *
    * @param ofs File to save privateStreams to
    * */
    void writeData(std::ofstream& ofs) override;
private:
    std::vector<std::string> whitelist;
    unsigned int maxNumViewers{};
    std::map<std::string,std::string> comments;
};

#endif //PROJECT_PRIVATESTREAM_H
