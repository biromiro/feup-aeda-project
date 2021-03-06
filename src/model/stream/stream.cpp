//
// Created by Danny on 15/10/2020.
//
#include "stream.h"
#include "../../exception/invalidFeedback/invalidFeedback.h"
#include "../user/streamer/streamer.h"
#include "../user/viewer/viewer.h"
#include "../user/streamer/streamer_manager.h"

unsigned int Stream::nextID = 0;

Stream::Stream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, std::shared_ptr<Streamer> streamer):
        title(std::move(title)), language(lang), minAge(minAge), type(type), genre(genre), streamer(std::move(streamer)) {

    streamDate = Date();

    if(type != StreamType::FINISHED) {
        uniqueID = ++nextID;
    }

    votingSystem = std::make_pair<unsigned int,unsigned int>(0,0);
    numOfViewers = 0;
    feedback = std::map<std::string,FeedbackLikeSystem>();
}

Stream::Stream(enum StreamType type) : type(type){}


unsigned int Stream::getNumOfViewers() const {
    return numOfViewers;
}

unsigned Stream::getMinAge() const {
    return minAge;
}

std::string Stream::getTitle() const {
    return title;
}

enum StreamLanguage Stream::getLanguage() const {
    return language;
}

bool Stream::canJoin(const  std::shared_ptr<Viewer>& newViewer) const {
    return newViewer->getAge() >= minAge;
}

Date Stream::getStreamDate() const {
    return streamDate;
}

std::shared_ptr<Streamer> Stream::getStreamer() const {
    return streamer;
}

std::pair<unsigned int, unsigned int> Stream::getVotes() const {
    return votingSystem;
}

bool Stream::addFeedback(const std::string& nickname, enum FeedbackLikeSystem newFeedback) {

    //checks if the user has already given any feedback, if he has, removes it from the streams's feedback
    if(feedback.find(nickname) != feedback.end()){
        if(feedback[nickname] == FeedbackLikeSystem::LIKE)
            votingSystem.first--;
        else if(feedback[nickname] == FeedbackLikeSystem::DISLIKE)
            votingSystem.second--;
    }

    //updates the feedback on the stream
    feedback[nickname] = newFeedback;

    if(newFeedback == FeedbackLikeSystem::LIKE)
        votingSystem.first++;
    else if(newFeedback == FeedbackLikeSystem::DISLIKE)
        votingSystem.second++;
    else
        throw InvalidFeedback(newFeedback, "You can only LIKE or DISLIKE a stream!");
    return true;
}

bool Stream::removeFeedback(const std::string& nickname, enum FeedbackLikeSystem newFeedback){

    //checks if the user has, indeed, given feedback
    //if he did not, it throws the InvalidFeedback exception
    if(feedback.find(nickname) != feedback.end()){
        if(feedback[nickname] == FeedbackLikeSystem::LIKE)
            votingSystem.first--;
        else if(feedback[nickname] == FeedbackLikeSystem::DISLIKE)
            votingSystem.second--;
    }else throw InvalidFeedback(newFeedback, "You can't remove feedback if you haven't done one yet!");

    feedback.erase(nickname);

    return true;
}

bool Stream::operator==(const std::shared_ptr<Stream>& stream) const {
    return uniqueID == stream->getUniqueId();
}

unsigned int Stream::getUniqueId() const {
    return uniqueID;
}

StreamGenre Stream::getGenre() const {
    return genre;
}

bool Stream::operator<(const Stream &rhs) const {
    if (streamDate < rhs.streamDate)
        return true;
    if (rhs.streamDate < streamDate)
        return false;
    if (votingSystem.first < rhs.votingSystem.first)
        return true;
    if (rhs.votingSystem.first < votingSystem.first)
        return false;
    if (votingSystem.second < rhs.votingSystem.second)
        return true;
    if (rhs.votingSystem.second < votingSystem.second)
        return false;
    if (numOfViewers < rhs.numOfViewers)
        return true;
    if (rhs.numOfViewers < numOfViewers)
        return false;
    if (uniqueID < rhs.uniqueID)
        return true;
    if (rhs.uniqueID < uniqueID)
        return false;
    return minAge < rhs.minAge;
}

bool Stream::operator>(const Stream &rhs) const {
    return rhs < *this;
}

bool Stream::operator<=(const Stream &rhs) const {
    return !(rhs < *this);
}

bool Stream::operator>=(const Stream &rhs) const {
    return !(*this < rhs);
}

bool Stream::operator==(const Stream &rhs) const {
    return uniqueID == rhs.uniqueID;
}

bool Stream::operator!=(const Stream &rhs) const {
    return !(rhs == *this);
}

void Stream::readData(std::ifstream &ifs, const std::shared_ptr<StreamerManager>& streamerManager) {
    std::string streamerNickname, viewerNickname;
    unsigned int feedbackSize = 0;
    FeedbackLikeSystem vote = FeedbackLikeSystem::INVALID_VOTE;

    ifs >> nextID;
    ifs >> uniqueID;
    ifs.ignore();
    ifs >> language;
    ifs >> type;
    ifs >> genre;

    getline(ifs,title);
    getline(ifs,streamerNickname);
    streamer = streamerManager->get(streamerNickname);

    ifs >> minAge;
    ifs >> votingSystem.first;
    ifs >> votingSystem.second;
    ifs >> numOfViewers;
    ifs >> streamDate;

    ifs >> feedbackSize;
    ifs.ignore();

    while (feedbackSize--){
        getline(ifs,viewerNickname);
        ifs >> vote;
        feedback[viewerNickname] = vote;
    }

}

void Stream::writeData(std::ofstream &ofs) {

    ofs << nextID << "\n";
    ofs << uniqueID << "\n";
    ofs << language << "\n";
    ofs << type << "\n";
    ofs << genre << "\n";
    ofs << title << "\n";
    ofs << streamer->getNickname() << "\n";
    ofs << minAge << "\n";
    ofs << votingSystem.first << "\n";
    ofs << votingSystem.second << "\n";
    ofs << numOfViewers << "\n";
    ofs << streamDate << "\n";

    ofs << feedback.size() << "\n";

    for(const auto& elem: feedback){
        ofs << elem.first << "\n";
        ofs << elem.second << "\n";
    }
}

void Stream::newViewerJoin() {
    numOfViewers++;
}

void Stream::viewerLeft() {
    numOfViewers--;
}

std::ostream& operator<<(std::ostream& out, const StreamLanguage& f) {
    std::string returnValue;
    std::unordered_map<std::string,StreamLanguage> const table{{"AF",StreamLanguage::AF},{"AR",StreamLanguage::AR},{"AZ",StreamLanguage::AZ},{"BE",StreamLanguage::BE},{"BG",StreamLanguage::BG},{"CA",StreamLanguage::CA},{"CZ",StreamLanguage::CZ},{"CY",StreamLanguage::CY},{"DA",StreamLanguage::DA},{"DE",StreamLanguage::DE},{"EL",StreamLanguage::EL},{"EN",StreamLanguage::EN},
                                                               {"EO",StreamLanguage::EO},{"ES",StreamLanguage::ES},{"ET",StreamLanguage::ET},{"EU",StreamLanguage::EU},{"FA",StreamLanguage::FA},{"FI",StreamLanguage::FI},{"FO",StreamLanguage::FO},{"FR",StreamLanguage::FR},{"GL",StreamLanguage::GL},{"GU",StreamLanguage::GU},{"HE",StreamLanguage::HE},{"HI",StreamLanguage::HI},
                                                               {"HR",StreamLanguage::HR},{"HU",StreamLanguage::HU},{"HY",StreamLanguage::HY},{"ID",StreamLanguage::ID},{"IS",StreamLanguage::IS},{"IT",StreamLanguage::IT},{"JA",StreamLanguage::JA},{"KA",StreamLanguage::KA},{"KK",StreamLanguage::KK},{"KN",StreamLanguage::KN},{"KO",StreamLanguage::KO},{"KOK",StreamLanguage::KOK},
                                                               {"KY",StreamLanguage::KY},{"LT",StreamLanguage::LT},{"LV",StreamLanguage::LV},{"MI",StreamLanguage::MI},{"MK",StreamLanguage::MK},{"MN",StreamLanguage::MN},{"MR",StreamLanguage::MR}, {"MS",StreamLanguage::MS},{"MT",StreamLanguage::MT},{"NB",StreamLanguage::NB},{"NL",StreamLanguage::NL},{"NN",StreamLanguage::NN},
                                                               {"NS",StreamLanguage::NS},{"PA",StreamLanguage::PA},{"PL",StreamLanguage::PL},{"PS",StreamLanguage::PS},{"PT_BR",StreamLanguage::PT_BR},{"PT_PT",StreamLanguage::PT_PT},{"QU",StreamLanguage::QU},{"RO",StreamLanguage::RO},{"RU",StreamLanguage::RU},{"SA",StreamLanguage::SA},{"SE",StreamLanguage::SE},
                                                               {"SK",StreamLanguage::SK},{"SL",StreamLanguage::SL},{"SQ",StreamLanguage::SQ},{"SR",StreamLanguage::SR},{"SV",StreamLanguage::SV},{"SW",StreamLanguage::SW},{"SYR",StreamLanguage::SYR},{"TA",StreamLanguage::TA},{"TE",StreamLanguage::TE},{"TH",StreamLanguage::TH},{"TL",StreamLanguage::TL},{"TN",StreamLanguage::TN},
                                                               {"TR",StreamLanguage::TR},{"TT",StreamLanguage::TT},{"TS",StreamLanguage::TS},{"UK",StreamLanguage::UK},{"UR",StreamLanguage::UR},{"UZ",StreamLanguage::UZ},{"YI",StreamLanguage::YI},{"XH",StreamLanguage::XH},{"ZH",StreamLanguage::ZH}};
    //searches for the string equivalent
    for(const auto& elem: table){
        if(elem.second == f) {
            returnValue = elem.first;
            break;
        }
    }
    out << returnValue;
    return out;
}

std::ostream& operator<<(std::ostream& out, const StreamType& f) {
    switch (f) {
        case StreamType::PUBLIC: out << "PUBLIC"; break;
        case StreamType::PRIVATE: out << "PRIVATE"; break;
        case StreamType::FINISHED: out << "FINISHED"; break;
        default: out << int(f); break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const StreamGenre& f) {
    switch (f) {
        case StreamGenre::MUSIC: out << "MUSIC"; break;
        case StreamGenre::GAMING: out << "GAMING"; break;
        case StreamGenre::COOKING: out << "COOKING"; break;
        case StreamGenre::TALKSHOW: out << "TALKSHOW"; break;
        default: out << int(f); break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const FeedbackLikeSystem& f){
    switch (f) {
        case FeedbackLikeSystem::LIKE: out << "LIKE"; break;
        case FeedbackLikeSystem::DISLIKE: out << "DISLIKE"; break;
        case FeedbackLikeSystem::INVALID_VOTE: out << "INVALID_VOTE"; break;
    }
    return out;
}


std::istream& operator>>(std::istream& inf, StreamLanguage& f){
    std::string language;
    std::unordered_map<std::string,StreamLanguage> const table{{"AF",StreamLanguage::AF},{"AR",StreamLanguage::AR},{"AZ",StreamLanguage::AZ},{"BE",StreamLanguage::BE},{"BG",StreamLanguage::BG},{"CA",StreamLanguage::CA},{"CZ",StreamLanguage::CZ},{"CY",StreamLanguage::CY},{"DA",StreamLanguage::DA},{"DE",StreamLanguage::DE},{"EL",StreamLanguage::EL},{"EN",StreamLanguage::EN},
                                                               {"EO",StreamLanguage::EO},{"ES",StreamLanguage::ES},{"ET",StreamLanguage::ET},{"EU",StreamLanguage::EU},{"FA",StreamLanguage::FA},{"FI",StreamLanguage::FI},{"FO",StreamLanguage::FO},{"FR",StreamLanguage::FR},{"GL",StreamLanguage::GL},{"GU",StreamLanguage::GU},{"HE",StreamLanguage::HE},{"HI",StreamLanguage::HI},
                                                               {"HR",StreamLanguage::HR},{"HU",StreamLanguage::HU},{"HY",StreamLanguage::HY},{"ID",StreamLanguage::ID},{"IS",StreamLanguage::IS},{"IT",StreamLanguage::IT},{"JA",StreamLanguage::JA},{"KA",StreamLanguage::KA},{"KK",StreamLanguage::KK},{"KN",StreamLanguage::KN},{"KO",StreamLanguage::KO},{"KOK",StreamLanguage::KOK},
                                                               {"KY",StreamLanguage::KY},{"LT",StreamLanguage::LT},{"LV",StreamLanguage::LV},{"MI",StreamLanguage::MI},{"MK",StreamLanguage::MK},{"MN",StreamLanguage::MN},{"MR",StreamLanguage::MR}, {"MS",StreamLanguage::MS},{"MT",StreamLanguage::MT},{"NB",StreamLanguage::NB},{"NL",StreamLanguage::NL},{"NN",StreamLanguage::NN},
                                                               {"NS",StreamLanguage::NS},{"PA",StreamLanguage::PA},{"PL",StreamLanguage::PL},{"PS",StreamLanguage::PS},{"PT_BR",StreamLanguage::PT_BR},{"PT_PT",StreamLanguage::PT_PT},{"QU",StreamLanguage::QU},{"RO",StreamLanguage::RO},{"RU",StreamLanguage::RU},{"SA",StreamLanguage::SA},{"SE",StreamLanguage::SE},
                                                               {"SK",StreamLanguage::SK},{"SL",StreamLanguage::SL},{"SQ",StreamLanguage::SQ},{"SR",StreamLanguage::SR},{"SV",StreamLanguage::SV},{"SW",StreamLanguage::SW},{"SYR",StreamLanguage::SYR},{"TA",StreamLanguage::TA},{"TE",StreamLanguage::TE},{"TH",StreamLanguage::TH},{"TL",StreamLanguage::TL},{"TN",StreamLanguage::TN},
                                                               {"TR",StreamLanguage::TR},{"TT",StreamLanguage::TT},{"TS",StreamLanguage::TS},{"UK",StreamLanguage::UK},{"UR",StreamLanguage::UR},{"UZ",StreamLanguage::UZ},{"YI",StreamLanguage::YI},{"XH",StreamLanguage::XH},{"ZH",StreamLanguage::ZH}};
    getline(inf,language);

    //searches for the enum equivalent
    auto it = table.find(language);
    if(it != table.end())
        f = it->second;
    return inf;

}
std::istream& operator>>(std::istream& inf, StreamGenre& f){
    std::string genre;
    std::unordered_map<std::string,StreamGenre> const table{{"MUSIC",StreamGenre::MUSIC},{"GAMING",StreamGenre::GAMING},{"COOKING",StreamGenre::COOKING},{"TALKSHOW",StreamGenre::TALKSHOW}};
    getline(inf,genre);
    auto it = table.find(genre);
    if(it != table.end())
        f = it->second;
    return inf;

}
std::istream& operator>>(std::istream& inf, StreamType& f){
    std::string type;
    std::unordered_map<std::string,StreamType> const table{
        {"PRIVATE",StreamType::PRIVATE},{"PUBLIC",StreamType::PUBLIC},{"FINISHED",StreamType::FINISHED}
    };

    getline(inf,type);

    //searches for the enum equivalent
    auto it = table.find(type);
    if(it != table.end())
        f = it->second;
    return inf;
}

std::istream& operator>>(std::istream& inf, FeedbackLikeSystem& f){
    std::string type;
    std::unordered_map<std::string,FeedbackLikeSystem> const table{
        {"LIKE",FeedbackLikeSystem::LIKE},{"DISLIKE",FeedbackLikeSystem::DISLIKE},{"INVALID_VOTE",FeedbackLikeSystem::INVALID_VOTE}
    };

    getline(inf,type);

    //searches for the enum equivalent
    auto it = table.find(type);
    if(it != table.end())
        f = it->second;
    return inf;
}

void Stream::reactivationBonus() {
    votingSystem.first += 50;
}
