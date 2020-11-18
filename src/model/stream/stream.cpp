//
// Created by Danny on 15/10/2020.
//
#include "stream.h"
#include "../../exception/invalidFeedback/invalidFeedback.h"
#include "../user/streamer/streamer.h"
#include "../user/viewer/viewer.h"
#include "../user/streamer/streamer_manager.h"

unsigned int Stream::nextID = 0;

Stream::Stream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, std::shared_ptr<Streamer> streamer): title(std::move(title)), language(lang), minAge(minAge), type(type), genre(genre), streamer(std::move(streamer)) {

    streamDate = Date();
    if(type != StreamType::FINISHED) { uniqueID = ++nextID; }
    votingSystem = std::pair<unsigned int,unsigned int>();
    numOfViewers = 0;
}

Stream::Stream(enum StreamType type) : type(type){}


unsigned int Stream::getNumOfViewers() const { return numOfViewers; }

unsigned Stream::getMinAge() const { return minAge; }

std::string Stream::getTitle() const { return title; }

enum StreamLanguage Stream::getLanguage() const { return language; }

bool Stream::canJoin(const  std::shared_ptr<Viewer>& newViewer) const {
    return newViewer->getAge() >= minAge;
}

Date Stream::getStreamDate() const { return streamDate; }

std::shared_ptr<Streamer> Stream::getStreamer() const { return streamer; }

std::pair<unsigned int, unsigned int> Stream::getVotes() const { return votingSystem; }

bool Stream::addFeedback(enum FeedbackLikeSystem feedback) {
    if(feedback == FeedbackLikeSystem::LIKE)
        votingSystem.first++;
    else if(feedback == FeedbackLikeSystem::DISLIKE)
        votingSystem.second++;
    else
        throw InvalidFeedback(feedback, "You can only LIKE or DISLIKE a stream!");
    return true;
}

bool Stream::operator==(std::shared_ptr<Stream> stream) const { return uniqueID == stream->getUniqueId(); }

unsigned int Stream::getUniqueId() const { return uniqueID; }

StreamGenre Stream::getGenre() const {
    return genre;
}

bool Stream::operator<(const Stream &rhs) const {
    if (type < rhs.type)
        return true;
    if (rhs.type < type)
        return false;
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
    if (minAge < rhs.minAge)
        return true;
    if (rhs.minAge < minAge)
        return false;
    if (title < rhs.title)
        return true;
    if (rhs.title < title)
        return false;
    if (language < rhs.language)
        return true;
    if (rhs.language < language)
        return false;
    if (genre < rhs.genre)
        return true;
    if (rhs.genre < genre)
        return false;
    return genre < rhs.genre;
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

void Stream::readData(std::ifstream &ifs, std::shared_ptr<StreamerManager> streamerManager) {
    std::string streamerNickname;

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

}

void Stream::writeData(std::ofstream &ofs) {
    ofs << uniqueID << "\n";
    ofs << language << "\n";
    switch (type) {
        case StreamType::PUBLIC:
            ofs << "PUBLIC" << "\n";
            break;
        case StreamType::PRIVATE:
            ofs << "PRIVATE" << "\n";
            break;
        case StreamType::FINISHED:
            ofs << "FINISHED" << "\n";
            break;
    }
    switch (genre) {
        case StreamGenre::GAMING:
            ofs << "GAMING" << "\n";
            break;
        case StreamGenre::COOKING:
            ofs << "COOKING" << "\n";
            break;
        case StreamGenre::TALKSHOW:
            ofs << "TALKSHOW" << "\n";
            break;
        case StreamGenre::MUSIC:
            ofs << "MUSIC" << "\n";
            break;
    }
    ofs << title << "\n";
    ofs << streamer->getNickname() << "\n";
    ofs << minAge << "\n";
    ofs << votingSystem.first << "\n";
    ofs << votingSystem.second << "\n";
    ofs << numOfViewers << "\n";
    ofs << streamDate << "\n";


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
        case StreamType::PUBLIC: out << "Public"; break;
        case StreamType::PRIVATE: out << "Private"; break;
        case StreamType::FINISHED: out << "Finished"; break;
        default: out << int(f); break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const StreamGenre& f) {
    switch (f) {
        case StreamGenre::MUSIC: out << "Music"; break;
        case StreamGenre::GAMING: out << "Gaming"; break;
        case StreamGenre::COOKING: out << "Cooking"; break;
        case StreamGenre::TALKSHOW: out << "Talkshow"; break;
        default: out << int(f); break;
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
    std::unordered_map<std::string,StreamType> const table{{"PRIVATE",StreamType::PRIVATE},{"PUBLIC",StreamType::PUBLIC},{"FINISHED",StreamType::FINISHED}};
    getline(inf,type);
    auto it = table.find(type);
    if(it != table.end())
        f = it->second;
    return inf;
}
