//
// Created by Danny on 25/10/2020.
//

#ifndef PROJECT_STREAMMANAGER_H
#define PROJECT_STREAMMANAGER_H

#include "../../model/user/viewer/viewer_manager.h"
#include "privateStream/privateStream.h"
#include "publicStream/publicStream.h"
#include "finishedStream/finishedStream.h"
#include "../../model/user/streamer/streamer.h"
#include <memory>

class StreamManager{
public:
    /**
     * Constructor of the StreamManager class
     *
     * @param viewerManager the manager of the Viewers
     * @param streamerManaager the manager of the Streamers
     */
    StreamManager(std::shared_ptr<ViewerManager> viewerManager, std::shared_ptr<StreamerManager> streamerManager);


    /**
     * Creates a PublicStream or PrivateStream object using the given parameters
     *
     * @param title title of the stream
     * @param lang language the stream is in
     * @param minAge minimum viewer age allowed
     * @param type type of the stream
     * @param genre genre of the stream
     * @param streamer streamer of the stream
     * @return pointer to the created stream
     */

    std::shared_ptr<Stream> build(std::string title, enum StreamLanguage lang, unsigned int minAge, enum StreamType type, enum StreamGenre genre, std::shared_ptr<Streamer> streamer);

    /**
     * Adds a stream to the streams vector
     *
     * @param streamToAdd stream to be added to the vector
     * @return true if stream is added, false if it is already in the vector
     */
    bool add(std::shared_ptr<Stream> streamToAdd);

    /**
     * Removes a stream from the streams vector
     *
     * @param streamToRemove stream to be removed from the vector
     * @return true if stream is removed, false if it isn't in the vector
     */
    bool remove(std::shared_ptr<Stream> streamToRemove);

    /**
     * Checks if a stream is in the streams vector
     *
     * @param streamToCheck stream to look for in the vector
     * @return true if stream is in the vector, false otherwise
     */
    bool has(const std::shared_ptr<Stream>& streamToCheck);

    /**
     * Gets the stream of a given uniqueID
     *
     * @param streamID the uniqueID of the stream to get
     * @return pointer to the stream that has parameter streamID
     */
    std::shared_ptr<Stream> get(unsigned int streamID);

    /**
     * Creates a FinishedStream object through downcasting, marking the end of a stream
     *
     * @param streamToFinish stream that is downcast as a FinishedStream
     * @return true if FinishedStream is successfully created, false otherwise
     */
  
    std::shared_ptr<FinishedStream> finish(const std::shared_ptr<Stream>& streamToFinish);
    
    /**
     * Getter of the number of viewers of a stream that is to be finished at its end
     *
     * @param streamToFinish stream that is to be finished
     * @return number of viewers of streamToFinish at its end
     */
    unsigned int getNumOfViewers(const std::shared_ptr<Stream>& streamToFinish);
  
    /**
     * Sets/Updates the StreamManager's streamer manager
     *
     * @param newStreamerManager new streamer manager
     */
    void setStreamerManager(std::shared_ptr<StreamerManager> newStreamerManager);
  
    /**
     * Getter of the streams vector
     *
     * @return vector of streams
     */
    const std::vector<std::shared_ptr<Stream>> &getStreams() const;

    /**
     * Getter of the cache of finished streams
     *
     * @return vector of cache of finished streams
     */
    const std::vector<std::shared_ptr<Stream>> &getCacheOfFinishedStreams() const;

    bool readData();

    bool writeData();

private:
    std::shared_ptr<StreamerManager> streamerManager;
    std::shared_ptr<ViewerManager> viewerManager;
    std::vector<std::shared_ptr<Stream>> streams;
    std::vector<std::shared_ptr<Stream>> cacheOfFinishedStreams;
};

#endif //PROJECT_STREAMMANAGER_H
