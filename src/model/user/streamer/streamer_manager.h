//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_STREAMER_MANAGER_H
#define PROJECT_STREAMER_MANAGER_H

#include "../../stream/streamManager.h"
#include "streamer.h"

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

    bool reload(const std::shared_ptr<Streamer>& streamer);

    /**
     * Removes a streamer from the streamers vector
     *
     * @param streamer new streamer to be added
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

    [[nodiscard]] unsigned int getNumOfFollowers(const std::shared_ptr<Streamer>& streamer) const;

    [[nodiscard]] const std::vector<std::shared_ptr<Streamer>> &getStreamers() const;

    bool readData();

    bool writeData();

private:
    std::vector<std::shared_ptr<Streamer>> streamers;
    std::shared_ptr<StreamManager> streamManager;
    std::shared_ptr<ViewerManager> viewerManager;
    std::shared_ptr<UserManager> userManager;
};


#endif //PROJECT_STREAMER_MANAGER_H
