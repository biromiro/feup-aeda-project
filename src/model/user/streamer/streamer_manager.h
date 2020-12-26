//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_STREAMER_MANAGER_H
#define PROJECT_STREAMER_MANAGER_H

#include "../../stream/streamManager.h"
#include "../../transactions/donations/donation.h"
#include "../../../utils/binaryTree/bst.h"
#include "../../../exception/streamerHasNoDonations/streamerHasNoDonations.h"
#include "streamer.h"

/**
 * @file streamer_manager.cpp
 *
 * @brief Class representing the Streamer Manager class
 *
 * @ingroup user
 */

/**
 * Implementation of the Streamer Manager class
 *
 * Manages the streamers, taking care of the streamer related events (creating adn deleting one, managing a stream creation, etc)
 */
class StreamerManager{
public:
    StreamerManager();

    /**
     * Constructor of the Streamer Manager
     *
     * @param streamManager the stream manager
     * @param viewerManager the viewer manager
     * @param userManager the user manager
     */
    StreamerManager(std::shared_ptr<StreamManager> streamManager,std::shared_ptr<ViewerManager> viewerManager, std::shared_ptr<UserManager> userManager);

    /**
     * Creates an object of class Streamer
     *
     * @param birthDate the birthdate of the streamer
     * @param name the name of the streamer
     * @param nickname the nickname of the streamer
     * @return True if the action was successful, false otherwise
     */
    std::shared_ptr<Streamer> build(Date birthDate, const std::string& name, const std::string& nickname, const std::string& password);

    /**
     * Adds a new streamer to the streamer vector
     *
     * @param streamer new streamer to be added
     * @return True if the action was successful, false otherwise
     */
    bool add(const std::shared_ptr<Streamer>& streamer);

    /**
     * Reloads streamer into the system when reading from file
     *
     * @param streamer streamer to reload into the system
     * @return true if the streamer was added, throws exception if streamer already exists
     * */
    bool reload(const std::shared_ptr<Streamer>& streamer);

    /**
     * Removes a streamer from the streamers vector
     *
     * @param streamer new streamer to be removed
     * @return True if the action was successful, false otherwise
     */
    bool remove(const std::shared_ptr<Streamer>& streamer);

    /**
     * Ends the stream of a given streamer
     *
     * @param streamer the stream to which the stream is to be finished
     * @return True if the action was successful, false otherwise
     */
    bool endStream(const std::shared_ptr<Streamer>& streamer);

    /**
     * Checks if the streamer exists in the streamers vector
     *
     * @param streamer streamer to be found
     * @return True if the action was successful, false otherwise
     */
    [[nodiscard]] bool has(const std::shared_ptr<Streamer>& streamer) const;

    /**
     * Checks, by nickname (which is unique), if the user exists in the streamers unordered set
     *
     * @param nickname the nickname of the streamer to be found
     * @return True if the action was successful, false otherwise
     */
    [[nodiscard]] bool has(std::string nickname) const;

    /**
    * Returns the pointer to a streamer given his nickname
    *
    * @param nickname the nickname of the streamer to be found and returned
    * @return the streamer with the given nickname
    */
    [[nodiscard]] std::shared_ptr<Streamer> get(std::string nickname) const;

    /**
     * Getter of streamer's number of followers
     *
     * @param streamer streamer to get number of followers from
     * @return number of followers
     * */
    [[nodiscard]] unsigned int getNumOfFollowers(const std::shared_ptr<Streamer>& streamer) const;

    /**
     * Getter of streamers currently in the system
     *
     * @return vector of streamers
     * */
    [[nodiscard]] const std::vector<std::shared_ptr<Streamer>> &getStreamers() const;

    [[nodiscard]] const BST<Donation> &getDonations() const;

    /**
     * Adds a new donation to the donation tree
     *
     * @param nickname the nickname of the streamer to donate
     * @param ammount the ammount to donate to the streamer
     * @param rating the rating given to the streamer
     */
    void addNewDonation(const std::string& nickname, float ammount, streamerWorkRating rating);

    vector<Donation> getStreamerDonations(const std::string& nickname);

    /**
     * Reads streamer data from file
     *
     * @return read successfull
     * */
    bool readData();

    /**
     * Writes and updates streamer data to file
     *
     * @return write successfull
     * */
    bool writeData();

private:
    std::vector<std::shared_ptr<Streamer>> streamers;
    BST<Donation> donations;
    std::shared_ptr<StreamManager> streamManager;
    std::shared_ptr<ViewerManager> viewerManager;
    std::shared_ptr<UserManager> userManager;
};


#endif //PROJECT_STREAMER_MANAGER_H
