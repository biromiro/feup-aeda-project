//
// Created by biromiro on 18/10/20.
//
#include "../../../exception/streamAlreadyFinished/streamAlreadyFinished.h"
#include "viewer.h"

#include "../../stream/privateStream/privateStream.h"
#include "../../stream/streamManager.h"
#include "../../transactions/merch/merchRequest.h"
#include "../../../exception/invalidPurchaseAvailability/invalidPurchaseAvailability.h"
#include "../../../exception/orderLimitReached/orderLimitReached.h"
#include "../../../exception/orderNotFound/orderNotFound.h"
#include "../../../exception/viewerAlreadyOrdered/viewerAlreadyOrdered.h"


Viewer::Viewer() : User(UserTypes::VIEWER) {
}

Viewer::Viewer(Date birthDate, std::string name, std::string nickname, std::string password): User(birthDate,std::move(name),std::move(nickname), UserTypes::VIEWER, std::move(password)){

    //a viewer has to be at least 12 years old
    if(getAge() < 12){
        throw InvalidAge(getAge(), "You have to be at least 12 years old!");
    }

    currentStream = nullptr;
    votedInStream = FeedbackLikeSystem::INVALID_VOTE;
}

bool Viewer::joinStream(const std::shared_ptr<Stream>& stream){

    //passing the "this" pointer to the canJoin method
    std::shared_ptr<Viewer> thisViewer = shared_from_this();
    if (!stream->canJoin(thisViewer) || currentStream != nullptr)
        return false;

    if(stream->getStreamType() == StreamType::FINISHED)
        throw StreamAlreadyFinished(stream, "The stream you're trying to join has already ended!");

    stream->newViewerJoin();
    auto it = streamHistory.find(stream);
    if(it != streamHistory.end())
        votedInStream = (*it).second;
    currentStream = stream;

    return true;
}

bool Viewer::isWatchingStream() const{
    return currentStream != nullptr;
}

bool Viewer::leaveCurrentStream() {

    //leaves the current stream (if watching one) and resets the object's parameters to be default
    if(isWatchingStream()){
        if(streamHistory.find(currentStream) == streamHistory.end())
            streamHistory[currentStream] = votedInStream;
        currentStream->viewerLeft();
        currentStream = nullptr;
        votedInStream = FeedbackLikeSystem::INVALID_VOTE;
        return true;
    }

    return false;
}

bool Viewer::giveFeedbackToStream(enum FeedbackLikeSystem feedback) {

    //by initializing the votedInStream variable, it is possible to always know if the user has already voted in
    //the current stream, IN THE CURRENT SESSION. If the viewer had already voted in a previous session in the current
    //stream (if he rejoins, per example), that is verified by the addFeedback and removeFeedback methods of Stream

    if(votedInStream == FeedbackLikeSystem::INVALID_VOTE) {
        if (isWatchingStream() && currentStream->addFeedback(getNickname(), feedback)) {
            votedInStream = feedback;
            return true;
        } else return false;
    }else{
        currentStream->removeFeedback(getNickname(), votedInStream);
        if(isWatchingStream() && currentStream->addFeedback(getNickname(),feedback)){
            votedInStream = feedback;
            return true;
        }else return false;
    }
}

bool Viewer::giveFeedbackToStream(const std::string& comment) {

    //can only comment on private streams
    if(isWatchingStream() && currentStream->getStreamType() == StreamType::PRIVATE ){
        auto currentStreamPrivate = std::dynamic_pointer_cast<PrivateStream>(currentStream);
        currentStreamPrivate->addComment(getNickname(),comment);
        return true;
    }else
        return false;
}

bool Viewer::followStreamer(const std::shared_ptr<Streamer>& streamer) {

    std::string nickname = streamer->getNickname();

    //can follow if not following already
    if(followingStreamers.find(nickname) != followingStreamers.end())
        return false;
    else
        followingStreamers.insert(nickname);
    return true;
}

bool Viewer::unfollowStreamer(const std::shared_ptr<Streamer>& streamer) {

    std::string nickname = streamer->getNickname();
    return followingStreamers.erase(nickname) != 0;
}

void Viewer::orderMerch(std::shared_ptr<Streamer> streamer, unsigned int quantity, unsigned int purchaseA) {
    try {
        MerchRequest toAdd(nickname, quantity, purchaseA);
        streamer->addMerchOrder(toAdd);
    } catch (InvalidPurchaseAvailability &ipa) {
        throw InvalidPurchaseAvailability(ipa.getPurchaseA(), ipa.what());
    } catch (OrderLimitReached &olr) {
        throw OrderLimitReached(olr.getOrder(), olr.what());
    } catch (ViewerAlreadyOrdered &vao) {
        throw ViewerAlreadyOrdered(vao.getOrder(), vao.what());
    }
}

void Viewer::removeOrder(std::shared_ptr<Streamer> streamer) {
    try {
        streamer->removeMerchOrder(nickname);
    } catch (OrderNotFound &onf) {
        throw OrderNotFound(onf.getBuyer(), onf.what());
    }
}

const std::shared_ptr<Stream> &Viewer::getCurrentStream() const {
    return currentStream;
}

std::map<std::shared_ptr<Stream>,FeedbackLikeSystem>& Viewer::getStreamHistory() {
    return streamHistory;
}

const std::unordered_set<std::string> &Viewer::getFollowingStreamers() const {
    return followingStreamers;
}

bool Viewer::operator<(const Viewer &rhs) const {
    if (joinDate < rhs.joinDate)
        return true;
    if (rhs.joinDate < joinDate)
        return false;
    if (birthDate < rhs.birthDate)
        return true;
    if (rhs.birthDate < birthDate)
        return false;
    if (nickname < rhs.nickname)
        return true;
    if (rhs.nickname < nickname)
        return false;
    if (name < rhs.name)
        return true;
    if (rhs.name < name)
        return false;
    return type < rhs.type;
}

bool Viewer::operator>(const Viewer &rhs) const {
    return rhs < *this;
}

bool Viewer::operator<=(const Viewer &rhs) const {
    return !(rhs < *this);
}

bool Viewer::operator>=(const Viewer &rhs) const {
    return !(*this < rhs);
}

bool Viewer::operator==(const Viewer &rhs) const {
    return nickname == rhs.nickname;
}

bool Viewer::operator!=(const Viewer &rhs) const {
    return !(rhs == *this);
}

void Viewer::readData(std::ifstream &ifs, const std::shared_ptr<StreamManager>& streamManager) {
    unsigned int streamHistorySize = 0, currentStreamID = 0, streamIDFromHistory = 0, followingStreamersSize = 0;
    std::string newStreamerID;
    std::shared_ptr<Stream> streamInHistory;
    FeedbackLikeSystem vote;

    ifs >> currentStreamID;

    if(currentStreamID != 0)
        currentStream = streamManager->get(currentStreamID);

    ifs >> streamHistorySize;
    while (streamHistorySize--){
        ifs >> streamIDFromHistory;
        ifs.ignore();
        ifs >> vote;
        streamInHistory = streamManager->get(streamIDFromHistory);
        if(streamInHistory != nullptr)
            streamHistory[streamInHistory] = vote;
    }

    ifs >> followingStreamersSize;
    ifs.ignore();
    while(followingStreamersSize--){
        getline(ifs,newStreamerID);
        followingStreamers.insert(newStreamerID);
    }

    ifs >> votedInStream;
    User::readData(ifs);
}

void Viewer::writeData(std::ofstream &ofs) {
    ofs << ((currentStream != nullptr) ? currentStream->getUniqueId() : 0) << "\n";

    ofs << streamHistory.size() << "\n";
    for(const auto& elem: streamHistory){
        ofs << elem.first->getUniqueId() << "\n";
        ofs << elem.second << "\n";
    }

    ofs << followingStreamers.size() << "\n";
    for(const auto& elem: followingStreamers){
        ofs << elem << "\n";
    }

    ofs << votedInStream << "\n";
    User::writeData(ofs);
}

