//
// Created by emanu on 21-Oct-20.
//

#include "streamZ.h"

StreamZ::StreamZ() :
userManager(std::make_shared<UserManager>()),
viewerManager(std::make_shared<ViewerManager>(userManager)),
streamManager(std::make_shared<StreamManager>(viewerManager)),
streamerManager(std::make_shared<StreamerManager>(streamManager, viewerManager, userManager)),
adminManager( std::make_shared<AdminManager>(userManager)),
leaderboardManager(std::make_shared<LeaderboardManager>(viewerManager,streamerManager,streamManager,userManager)){}


std::shared_ptr<UserManager> StreamZ::getUserManager() {
    return userManager;
}

std::shared_ptr<ViewerManager> StreamZ::getViewerManager() {
    return viewerManager;
}

std::shared_ptr<StreamManager> StreamZ::getStreamManager() {
    return streamManager;
}

std::shared_ptr<StreamerManager> StreamZ::getStreamerManager() {
    return streamerManager;
}

std::shared_ptr<AdminManager> StreamZ::getAdminManager() {
    return adminManager;
}

std::shared_ptr<LeaderboardManager> StreamZ::getLeaderboardManager() {
    return leaderboardManager;
}

bool StreamZ::initialize() {
    /*
    viewerManager->readData();
    streamManager->readData();
    streamerManager->readData();
    adminManager->readData();*/
    return true;
}

bool StreamZ::finish() {
    /*
    viewerManager->writeData();
    streamManager->writeData();
    streamerManager->writeData();
    adminManager->writeData();*/
    return true;
}



/*bool StreamZ::initialize() {
    std::fstream file;

    file.open("../../src/dataStreamer.dat",std::ios::in|std::ios::binary);
    if(!file){
        std::cout << "Error in opening Streamers file..." << std::endl;
        return false;
    }

    unsigned int numOfStreamers;
    Streamer streamerTemp = Streamer();

    file.read(reinterpret_cast<char *>(&numOfStreamers), sizeof(unsigned int));

    std::vector<std::pair<unsigned int,unsigned >> sizeOfNicknames;
    for(unsigned int i=0;i<numOfStreamers;++i){
        unsigned int sizeNick,sizeName;
        file.read(reinterpret_cast<char *>(&sizeNick), sizeof(unsigned int));
        file.read(reinterpret_cast<char *>(&sizeName), sizeof(unsigned int));
        sizeOfNicknames.emplace_back(sizeNick,sizeName);
    }

    for(const auto& elem: sizeOfNicknames){
        file.read((char *)(&streamerTemp), sizeof(Streamer));
        Streamer* captS = reinterpret_cast<Streamer *>(&streamerTemp);
        auto newStreamer = std::shared_ptr<Streamer>(captS);
        char* nicknameS = new char[elem.first+1];
        char* nameS = new char[elem.second+1];
        file.read(nicknameS, elem.first);
        file.read(nameS, elem.second);
        newStreamer->updateNickname(nicknameS);
        newStreamer->updateName(nameS);
        streamerManager->add(newStreamer);
    }
    file.close();

    /*file.open("../../src/dataViewers.dat",std::ios::in|std::ios::binary);
    if(!file){
        std::cout << "Error in opening Viewers file..." << std::endl;
    }
    Viewer* captV;
    while(file.read(reinterpret_cast<char *>(captV), sizeof(Viewer))){
        auto newViewer = std::shared_ptr<Viewer>(captV);
        viewerManager->add(newViewer);
    }
    file.close();

    file.open("../../src/dataAdmin.dat",std::ios::in|std::ios::binary);
    if(!file){
        std::cout << "Error in opening Admin file..." << std::endl;
    }

    Admin* captA;
    while(file.read(reinterpret_cast<char *>(captA), sizeof(Admin))){
        auto newAdmin = std::shared_ptr<Admin>(captA);
        adminManager->add(newAdmin);
    }
    file.close();

    file.open("../../src/dataStreams.dat",std::ios::in|std::ios::binary);
    if(!file){
        std::cout << "Error in opening Streams file..." << std::endl;
    }

    Stream* captSt;
    while(file.read(reinterpret_cast<char *>(captSt), sizeof(Stream))){
        auto newStream = std::shared_ptr<Stream>(captSt);
        std::string nickname, name;
        file.read(reinterpret_cast<char *>(&nickname), sizeof(std::string));
        file.read(file.read(reinterpret_cast<char *>(captSt), sizeof(Stream));
        streamManager->add(newStream);
    }
    file.close();
return true;
}

bool StreamZ::finish() {

    std::fstream file;

    file.open("../../src/dataStreamer.dat",std::ios::out|std::ios::binary);
    if(!file){
        std::cout << "Error in opening Streamers file..." << std::endl;
    }
    unsigned int numOfStreamers = streamerManager->getStreamers().size();
    file.write(reinterpret_cast<char *>(&numOfStreamers), sizeof(unsigned int));
    for(const auto& elem: streamerManager->getStreamers()){
        unsigned int nicknameS = elem->getNickname().size(), nameS = elem->getName().size();
        file.write(reinterpret_cast<char *>(&nicknameS), sizeof(unsigned int));
        file.write(reinterpret_cast<char *>(&nameS), sizeof(unsigned int));
    }

    for(const auto& elem: streamerManager->getStreamers()){
        file.write(reinterpret_cast<char *>(elem.get()), sizeof(Streamer));
        std::string nickname = elem->getNickname(), name = elem->getName();
        file.write(nickname.c_str(), sizeof(nickname));
        file.write(name.c_str(), sizeof(name));
    }
    file.close();
/*
    file.open("../../src/dataViewers.dat",std::ios::out|std::ios::binary);
    if(!file){
        std::cout << "Error in opening Viewers file..." << std::endl;
    }
    for(const auto& elem: viewerManager->getViewers()){
        file.write(reinterpret_cast<char *>(&(*elem)), sizeof(Viewer));
    }
    file.close();

    file.open("../../src/dataAdmin.dat",std::ios::out|std::ios::binary);
    if(!file){
        std::cout << "Error in opening Admin file..." << std::endl;
    }

    file.write(reinterpret_cast<char *>(&(*adminManager->get())), sizeof(Streamer));

    file.close();

    file.open("../../src/dataStreams.dat",std::ios::out|std::ios::binary);
    if(!file){
        std::cout << "Error in opening Streams file..." << std::endl;
    }

    for(const auto& elem: streamManager->getStreams()){
        file.write(reinterpret_cast<char *>(&(*elem)), sizeof(Stream));
    }

    for(const auto& elem: streamManager->getCacheOfFinishedStreams()){
        file.write(reinterpret_cast<char *>(&(*elem)), sizeof(Stream));
    }
    file.close();
    return true;
}*/