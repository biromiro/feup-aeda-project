//
// Created by biromiro on 18/10/20.
//

#include "../stream.h"
#include "../../user/viewer/viewer.h"
#include "../../../exception/nicknameAlreadyAdded/nicknameAlreadyAdded.h"
#include "../../../exception/nicknameNotFound/nicknameNotFound.h"
#include <vector>
#include <fstream>

#ifndef PROJECT_PRIVATESTREAM_H
#define PROJECT_PRIVATESTREAM_H

class Viewer;

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
    enum StreamType getStreamType() const override;

    /**
     * Getter of the private stream's whitelist (nickname of allowed viewers)
     *
     * @return private stream's whitelist
     */
    std::vector<std::string> getWhitelist() const;

    /**
     * Getter of the private stream's maximum number of viewers
     *
     * @return private stream's maximum number of viewers
     */
    unsigned int getMaxNumViewers() const;

    /**
     * Getter of the private stream's comments
     *
     * @return vector of private stream's comments
     */
    std::vector<std::string> getComments() const;

    /**
     * Adds a viewer to the whitelist (using his nickname)
     *
     * @param v viewer whose nickname is to be added to the whitelist
     * @return true if viewer's nickname is successfully added, false if nickname is already in whitelist
     */
    bool addToWhitelist(std::shared_ptr<Viewer> v);

    /**

     * Removes a viewer from the whitelist (using his nickname)
     *
     * @param v viewer whose nickname is to be removed from the whitelist
     * @return true if a viewer's nickname is successfully removed, false if nickname isn't in whitelist
     */
    bool removeFromWhitelist(std::shared_ptr<Viewer> v);

    /**

     * Sets/Updates the maximum number of viewers allowed in the private stream
     *
     * @param maxNumViewers new maximum number of viewers of the private stream
     * @return true if maximum number of viewers was set successfully, false otherwise
     */
    bool setMaxNumViewers(unsigned int maxNumViewers);

    /**
     * Adds a comment to the vector of the private stream's comments
     *
     * @param comment comment to add to the vector
     */
    void addComment(const std::string& comment);

    /**
     * Checks if a viewer can join the private stream
     *
     * @param newViewer viewer to check
     * @return true if the viewer can join the private stream, false otherwise
     */
    bool canJoin(const std::shared_ptr<Viewer>& newViewer) const override;

    void readData(std::ifstream& ifs, std::shared_ptr<StreamerManager> streamerManager);

    void writeData(std::ofstream& ofs);
private:
    std::vector<std::string> whitelist;
    unsigned int maxNumViewers;
    std::vector<std::string> comments;
};

#endif //PROJECT_PRIVATESTREAM_H
