//
// Created by biromiro on 27/10/20.
//

#ifndef PROJECT_VIEWER_MANAGER_H
#define PROJECT_VIEWER_MANAGER_H

#include "../user_manager.h"
#include "viewer.h"

class ViewerManager{
public:
    ViewerManager(UserManager* userManager);
    bool add(Viewer* viewer);
    bool remove(Viewer* viewer);
    bool has(Viewer* viewer) const;
    bool has(std::string nickname) const;
    Viewer* get(std::string nickname) const;
    void write(std::ostream os) const;
    void read(std::ostream os);

private:
    std::vector<Viewer*> viewers;
    UserManager* userManager;
};

#endif //PROJECT_VIEWER_MANAGER_H
