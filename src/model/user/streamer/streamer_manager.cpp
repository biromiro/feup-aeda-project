//
// Created by biromiro on 27/10/20.
//

#include "streamer_manager.h"
#include "../../../exception/userNotFound/userNotFound.h"
#include "../../../exception/userAlreadyExists/userAlreadyExists.h"
#include "../../../exception/streamerNotStreaming/streamerNotStreaming.h"
#include "../../../exception/invalidDonationValue/invalidDonationValue.h"

StreamerManager::StreamerManager() : donations(Donation("",0,streamerWorkRating::VERY_BAD)){};


StreamerManager::StreamerManager(std::shared_ptr<StreamManager> streamManager, std::shared_ptr<ViewerManager> viewerManager, std::shared_ptr<UserManager> userManager):
streamManager(std::move(streamManager)), viewerManager(std::move(viewerManager)), userManager(std::move(userManager)), donations(Donation("",0.0,streamerWorkRating::VERY_BAD))
{
    streamers = tabHStreamer();
}

std::shared_ptr<Streamer> StreamerManager::build(Date birthDate, const std::string &name, const std::string &nickname, const std::string& password) {
    if(userManager->has(nickname))
        throw NicknameAlreadyAdded(nickname,"Nickname already in use by another user!");

    //to avoid memory from being aloccated on the case of an underage streamer, tries to build one and, if unsuccessful,
    //resets his shared pointer and rethrows the exception
    std::shared_ptr<Streamer> streamer;
    try{
        streamer = std::make_shared<Streamer>(birthDate,name,nickname,password);
    } catch (InvalidAge& invalidAge) {
        streamer.reset();
        throw InvalidAge(invalidAge.getAge(),invalidAge.what());
    }

    add(streamer);
    std::shared_ptr<User> user_form = std::dynamic_pointer_cast<User>(streamer);
    userManager->add(user_form);
    return streamer;
}

bool StreamerManager::add(const std::shared_ptr<Streamer>& streamer) {

    if(streamers.find(streamer) == streamers.end()){
        streamers.insert(streamer);
        return true;
    }
    throw UserAlreadyExists(streamer,"The streamer you're trying to add already exists!");
}

bool StreamerManager::reload(const std::shared_ptr<Streamer>& streamer){
    if(userManager->has(streamer->getNickname())){
        throw NicknameAlreadyAdded(streamer->getNickname(),"Nickname already in use by another user!");
    }else{
        std::shared_ptr<User> user_form = std::dynamic_pointer_cast<User>(streamer);
        userManager->add(user_form);
        return add(streamer);
    }
}

bool StreamerManager::remove(const std::shared_ptr<Streamer>& streamer) {

    if (streamers.find(streamer) != streamers.end()) {
        streamers.erase(streamer);
        userManager->remove(std::dynamic_pointer_cast<User>(streamer));
        return true;
    }
    throw UserNotFound(streamer,"The streamer you're trying to remove does not exist!");
}

bool StreamerManager::endStream(const std::shared_ptr<Streamer>& streamer) {

    if(streamer->isStreaming()){
        streamManager->finish(streamManager->get(streamer->getCurrentStreamID()));
        streamer->removeStream();
        return true;
    }
    throw StreamerNotStreaming("There is no stream to finish!");
}

bool StreamerManager::has(const std::shared_ptr<Streamer>& streamer) const {
    return streamers.find(streamer) != streamers.end();
}

bool StreamerManager::has(std::string nickname) const {
    return std::find_if(streamers.begin(),streamers.end(),
                        [&nickname](const std::shared_ptr<Streamer>& streamer){return streamer->getNickname() == nickname;}) != streamers.end();
}

std::shared_ptr<Streamer> StreamerManager::get(std::string nickname) const {

    auto it = std::find_if(streamers.begin(),streamers.end(),
                           [&nickname](const std::shared_ptr<Streamer>& streamer){return streamer->getNickname() == nickname;});

    if(it != streamers.end()){
        return *it;
    }
    return nullptr;
}

unsigned int StreamerManager::getNumOfFollowers(const std::shared_ptr<Streamer> &streamer) const {
    return static_cast<unsigned int>(std::count_if(viewerManager->getViewers().begin(), viewerManager->getViewers().end(),
                                                   [&streamer](const std::shared_ptr<Viewer> &viewer) {
                                                       return (viewer->getFollowingStreamers()).find(streamer->getNickname()) != viewer->getFollowingStreamers().end();
                                                   }));
}

const tabHStreamer &StreamerManager::getStreamers() const {
    return streamers;
}

bool StreamerManager::readData() {
    //write object into the file
    std::ifstream file;
    unsigned int streamersSize = 0, bstSize = 0;

    file.open("../../src/model/user/streamer/dataStreamer.txt");

    if(!file){
        std::cout << "Could not open Streamers file...";
        return false;
    }
    file >> streamersSize;

    while(streamersSize--){
        std::shared_ptr<Streamer> newStreamer = std::make_shared<Streamer>();
        newStreamer->readData(file);
        reload(newStreamer);
    }

    file >> bstSize;

    Donation donation("",0.0,streamerWorkRating::VERY_BAD);

    while(bstSize--){
        file >> donation;
        donations.insert(donation);
    }

    file.close();
    return true;
}


bool StreamerManager::writeData() {
    //write object into the file
    std::ofstream file;

    file.open("../../src/model/user/streamer/dataStreamer.txt");

    if(!file){
        std::cout << "Could not open Streamers file...";
        return false;
    }

    file << streamers.size() << "\n";

    for(const auto& elem: streamers){
        elem->writeData(file);
    }

    unsigned int bstSize = 0;

    for(BSTItrIn<Donation> bItr(donations); !bItr.isAtEnd(); bItr.advance()) bstSize++;

    file << bstSize << "\n";

    BSTItrIn<Donation> bstItrIn(donations);

    while(!bstItrIn.isAtEnd()){
        file << bstItrIn.retrieve();
        bstItrIn.advance();
    }

    file.close();
    return true;
}

bool StreamerManager::deactivateStreamer(const std::shared_ptr<Streamer> &streamer) {
    auto it = streamers.begin();
    if(streamers.find(streamer) != streamers.end()){
        streamer->deactivateAcc();
        return true;
    }
    throw UserNotFound(streamer,"The streamer you're trying yo deactivate does not exist!");
}

bool StreamerManager::reactivateStreamer(const std::shared_ptr<Streamer> &streamer) {
    auto it = streamers.begin();
    if(streamers.find(streamer) != streamers.end()){
        streamer->reactivateAcc();
        return true;
    }
    throw UserNotFound(streamer,"The streamer you're trying yo reactivate does not exist!");
}

void StreamerManager::addNewDonation(const string &nickname, float ammount, streamerWorkRating rating) {
    if(!has(nickname)) throw NicknameNotFound(nickname, "That streamer does not exist!");
    if(ammount < 0) throw InvalidDonationValue(ammount, "That donation value is invalid!");
    donations.insert(Donation(nickname,ammount,rating));
}

vector<Donation> StreamerManager::getStreamerDonations(const string &nickname) {
    vector<Donation> streamerDonations;

    for(BSTItrIn<Donation> bItr(donations); !bItr.isAtEnd(); bItr.advance()){
        Donation val = bItr.retrieve();
        if(val.getStreamerNickname() == nickname) streamerDonations.push_back(val);
    }


    if(streamerDonations.empty()) throw StreamerHasNoDonations(nickname, "No donations yet!");
    return streamerDonations;
}

const BST<Donation> &StreamerManager::getDonations() const {
    return donations;
}
