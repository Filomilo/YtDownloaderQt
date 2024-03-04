//
// Created by fboro on 01/03/2024.
//

#ifndef YTDLPWRAPPER_YOUTUBEVIDEO_H
#define YTDLPWRAPPER_YOUTUBEVIDEO_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
class YoutubeVideo {

    private:
    std::string name;
    std::string url;
    std::vector<std::string> subtitles;
    std::vector<std::string> autoSubtitles;
    std::string thumbnail;
    std::string duration;

public:



    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        YoutubeVideo::name = name;
    }

    const std::string &getUrl() const {
        return url;
    }

    const std::vector<std::string> &getSubtitles() const {
        return subtitles;
    }

    void setSubtitles(const std::vector<std::string> &subtitles) {
        YoutubeVideo::subtitles = subtitles;
    }
    void setUrl(const  std::string &url) {
        YoutubeVideo::url = url;
    }

    const std::string &getThumbnail() const {
        return thumbnail;
    }

    void setThumbnail(const std::string &thumbnail) {
        YoutubeVideo::thumbnail = thumbnail;
    }

    const std::string &getDuration() const {
        return duration;
    }

    void setDuration(const std::string &duration) {
        YoutubeVideo::duration = duration;
    }

    friend std::ostream &operator<<(std::ostream &os, const YoutubeVideo &video) {
        os << "\n\nname: " << video.name << "\n url: " << video.url << "\n subtitles: " << video.subtitles.size()  << "\nauto subtitles: " << video.autoSubtitles.size() << "\n thumbnail: "
           << video.thumbnail << "\n duration: " << video.duration;
        return os;
    }

    void addSubtitle(std::string sub)
    {
        this->subtitles.push_back(sub);
    }
    void addAutoSubtitle(std::string sub)
    {
        this->autoSubtitles.push_back(sub);
    }

};


#endif //YTDLPWRAPPER_YOUTUBEVIDEO_H
