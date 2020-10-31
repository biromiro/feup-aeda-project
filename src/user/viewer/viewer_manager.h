//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_VIEWER_MANAGER_H
#define PROJECT_VIEWER_MANAGER_H

#include "../user_manager.h"
#include "viewer.h"

class ViewerManager{
public:
    /**
     * Constructor of the Viewer Manager
     *
     * @param userManager the user manager
     */
    explicit ViewerManager(UserManager* userManager);

    /**
     * Adds a new viewer to the viewers vector
     *
     * @param viewer new viewer to be added
     * @return True if the action was successful, false otherwise
     */
    bool add(Viewer* viewer);

    /**
     * Removes a viewer from the viewers vector
     *
     * @param viewer new viewer to be added
     * @return True if the action was successful, false otherwise
     */
    bool remove(Viewer* viewer);

    /**
     * Checks if the viewer exists in the viewers vector
     *
     * @param viewer viewer to be found
     * @return True if the action was successful, false otherwise
     */
    bool has(Viewer* viewer) const;

    /**
     * Checks, by nickname (which is unique), if the user exists in the viewers unordered set
     *
     * @param nickname the nickname of the viewer to be found
     * @return True if the action was successful, false otherwise
     */
    bool has(std::string nickname) const;

    /**
     * Returns the pointer to a viewer given his nickname
     *
     * @param nickname the nickname of the viewer to be found and returned
     * @return the viewer with the given nickname
     */
    Viewer* get(std::string nickname) const;

    /**
     * Writes to an output stream the Viewer information
     *
     * @param os output stream to be writen to
     */
    void write(std::ostream os) const;

    /**
     * Reads viewer information from an input stream
     *
     * @param is the input stream to be read from
     */
    void read(std::istream is);

private:
    std::vector<Viewer*> viewers;
    UserManager* userManager;
};

#endif //PROJECT_VIEWER_MANAGER_H
