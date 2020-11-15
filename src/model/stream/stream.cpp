//
// Created by Danny on 15/10/2020.
//
#include "stream.h"
#include "../../model/user/viewer/viewer.h"
#include <iostream>
#include <utility>
#include "../../model/user/streamer/streamer_manager.h"
#include <unordered_map>

unsigned int Stream::nextID = 0;

Stream::Stream(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, std::shared_ptr<Streamer> streamer): title(std::move(title)), language(lang), minAge(minAge), type(type), genre(genre), streamer(std::move(streamer)) {
    uniqueID = ++nextID;
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
    if(feedback == LIKE)
        votingSystem.first++;
    else if(feedback == DISLIKE)
        votingSystem.second++;
    else
        return false;
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
        case PUBLIC:
            ofs << "PUBLIC" << "\n";
            break;
        case PRIVATE:
            ofs << "PRIVATE" << "\n";
            break;
        case FINISHED:
            ofs << "FINISHED" << "\n";
            break;
    }
    switch (genre) {
        case GAMING:
            ofs << "GAMING" << "\n";
            break;
        case COOKING:
            ofs << "COOKING" << "\n";
            break;
        case TALKSHOW:
            ofs << "TALKSHOW" << "\n";
            break;
        case MUSIC:
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
    std::array<std::string,80> e{{"AF","AR","AZ","BE","BG","CA","CZ","CY","DA","DE","EL","EN",
                                    "EO","ES","ET","EU","FA","FI","FO","FR","GL","GU","HE","HI",
                                    "HR","HU","HY","ID","IS","IT","JA","KA","KK","KN","KO","KOK",
                                    "KY","LT","LV","MI ","MK","MN","MR", "MS","MT","NB","NL","NN",
                                    "NS","PA","PL","PS","PT_BR","PT_PT","QU","RO","RU","SA","SE",
                                    "SK","SL","SQ","SR","SV","SW","SYR","TA","TE","TH","TL","TN",
                                    "TR","TT","TS","UK","UR","UZ","YI","XH","ZH"}};
    out << e.at(f);
    return out;
}

std::ostream& operator<<(std::ostream& out, const StreamType& f) {
    switch (f) {
        case PUBLIC: out << "Public"; break;
        case PRIVATE: out << "Private"; break;
        case FINISHED: out << "Finished"; break;
        default: out << int(f); break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const StreamGenre& f) {
    switch (f) {
        case MUSIC: out << "Music"; break;
        case GAMING: out << "Gaming"; break;
        case COOKING: out << "Cooking"; break;
        case TALKSHOW: out << "Talkshow"; break;
        default: out << int(f); break;
    }
    return out;
}

std::istream& operator>>(std::istream& inf, StreamLanguage& f){
    std::string language;
    std::unordered_map<std::string,StreamLanguage> const table{{"AF",AF},{"AR",AR},{"AZ",AZ},{"BE",BE},{"BG",BG},{"CA",CA},{"CZ",CZ},{"CY",CY},{"DA",DA},{"DE",DE},{"EL",EL},{"EN",EN},
                                                               {"EO",EO},{"ES",ES},{"ET",ET},{"EU",EU},{"FA",FA},{"FI",FI},{"FO",FO},{"FR",FR},{"GL",GL},{"GU",GU},{"HE",HE},{"HI",HI},
                                                               {"HR",HR},{"HU",HU},{"HY",HY},{"ID",ID},{"IS",IS},{"IT",IT},{"JA",JA},{"KA",KA},{"KK",KK},{"KN",KN},{"KO",KO},{"KOK",KOK},
                                                               {"KY",KY},{"LT",LT},{"LV",LV},{"MI",MI},{"MK",MK},{"MN",MN},{"MR",MR}, {"MS",MS},{"MT",MT},{"NB",NB},{"NL",NL},{"NN",NN},
                                                               {"NS",NS},{"PA",PA},{"PL",PL},{"PS",PS},{"PT_BR",PT_BR},{"PT_PT",PT_PT},{"QU",QU},{"RO",RO},{"RU",RU},{"SA",SA},{"SE",SE},
                                                               {"SK",SK},{"SL",SL},{"SQ",SQ},{"SR",SR},{"SV",SV},{"SW",SW},{"SYR",SYR},{"TA",TA},{"TE",TE},{"TH",TH},{"TL",TL},{"TN",TN},
                                                               {"TR",TR},{"TT",TT},{"TS",TS},{"UK",UK},{"UR",UR},{"UZ",UZ},{"YI",YI},{"XH",XH},{"ZH",ZH}};
    getline(inf,language);
    auto it = table.find(language);
    if(it != table.end())
        f = it->second;
    return inf;

}
std::istream& operator>>(std::istream& inf, StreamGenre& f){
    std::string genre;
    std::unordered_map<std::string,StreamGenre> const table{{"MUSIC",MUSIC},{"GAMING",GAMING},{"COOKING",COOKING},{"TALKSHOW",TALKSHOW}};
    getline(inf,genre);
    auto it = table.find(genre);
    if(it != table.end())
        f = it->second;
    return inf;

}
std::istream& operator>>(std::istream& inf, StreamType& f){
    std::string type;
    std::unordered_map<std::string,StreamType> const table{{"PRIVATE",PRIVATE},{"PUBLIC",PUBLIC},{"FINISHED",FINISHED}};
    getline(inf,type);
    auto it = table.find(type);
    if(it != table.end())
        f = it->second;
    return inf;
}
