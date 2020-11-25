//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_VIEWER_MANAGER_H
#define PROJECT_VIEWER_MANAGER_H

#include "../user_manager.h"
#include "viewer.h"
#include <memory>
#include <fstream>

class StreamerManager;

/**
 * @file viewer_manager.cpp
 *
 * @brief Class representing the Viewer Manager class
 *
 * @ingroup user
 */

/**
 * Implementation of the Viewer Manager class
 *
 * Manages the viewers, taking care of the viewer related events (creating and deleting one, managing the join
 * stream event, giving feedback, etc)
 */
class ViewerManager{
public:
    /**
     * Constructor of the Viewer Manager
     *
     * @param userManager the user manager
     */
    explicit ViewerManager(std::shared_ptr<UserManager> userManager);

    /**
     * Creates an object of class Viewer
     *
     * @param birthDate the birthdate of the viewer
     * @param name the name of the viewer
     * @param nickname the nickname of the viewer
     * @return True if the action was successful, false otherwise
     */
    std::shared_ptr<Viewer> build(Date birthDate, const std::string& name, const std::string& nickname, const std::string& password);

    /**
     * Adds a new viewer to the viewers vector
     *
     * @param viewer new viewer to be added
     * @return True if the action was successful, false otherwise
     */
    bool add(const std::shared_ptr<Viewer>& viewer);

    /**
    * Reloads viewer into the system when reading from file
    *
    * @param viewer viewer to reload into the system
    * @return true if the streamer was added, throws exception if streamer already exists
    * */
    bool reload(const std::shared_ptr<Viewer>& viewer);

    /**
     * Removes a viewer from the viewers vector
     *
     * @param viewer new viewer to be added
     * @return True if the action was successful, false otherwise
     */
    bool remove(const std::shared_ptr<Viewer>& viewer);

    /**
     * Checks if the viewer exists in the viewers vector
     *
     * @param viewer viewer to be found
     * @return True if the action was successful, false otherwise
     */
    [[nodiscard]] bool has(const std::shared_ptr<Viewer>& viewer) const;

    /**
     * Checks, by nickname (which is unique), if the user exists in the viewers unordered set
     *
     * @param nickname the nickname of the viewer to be found
     * @return True if the action was successful, false otherwise
     */
    [[nodiscard]] bool has(std::string nickname) const;

    /**
     * Returns the pointer to a viewer given his nickname
     *
     * @param nickname the nickname of the viewer to be found and returned
     * @return the viewer with the given nickname
     */
    [[nodiscard]] std::shared_ptr<Viewer> get(std::string nickname) const;

    /**
     * Getter of the viewers vector
     *
     * @return the viewers vector
     */
    [[nodiscard]] const std::vector<std::shared_ptr<Viewer>> &getViewers() const;

    /**
     * Reads viewer data from file
     *
     * @param streamManager streamManager to correctly add viewers into streams they are watching
     * @return read successfull
     * */
    bool readData(const std::shared_ptr<StreamManager>& streamManager);

    /**
    * Writes and updates viewer data to file
    *
    * @return write successfull
    * */
    bool writeData();

private:
    std::vector<std::shared_ptr<Viewer>> viewers;
    std::shared_ptr<UserManager> userManager;
};

#endif //PROJECT_VIEWER_MANAGER_H
