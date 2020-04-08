//
// Created by hoang on 1/8/2020.
//

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <iostream>
using namespace std;
class PlaylistNode
{
private:
    std::string iD;
    std::string songName;
    std::string artistName;
    int songLength;
    PlaylistNode *next;
public:
    PlaylistNode() : iD("none"), songName("none"), artistName("none"), songLength(0), next(nullptr) {}
    PlaylistNode(std::string iD, std::string songName, std::string artistName, int songLength) : iD(iD), songName(songName), artistName(artistName), songLength(songLength), next(nullptr) {}
    void InsertAfter(PlaylistNode* after)
    {
        this->SetNext(after);
    }
    void SetNext(PlaylistNode* newNext)
    {
        this->next = newNext;
    }
    std::string GetID()
    {
        return iD;
    }
    std::string GetSongName()
    {
        return songName;
    }
    std::string GetArtistName()
    {
        return artistName;
    }
    int GetSongLength()
    {
        return songLength;
    }
    PlaylistNode* GetNext()
    {
        return next;
    }
    void PrintPlaylistNode() const
    {
        std::cout << "Unique ID: " << iD << std::endl;
        std::cout << "Song Name: " << songName << std::endl;
        std::cout << "Artist Name: " << artistName << std:: endl;
        std::cout << "Song Length (in seconds): " << songLength << std::endl;
    }


};

class Playlist
{
private:
    std::string title;
    PlaylistNode *head;

public:
    Playlist(std::string title) : title(title), head(nullptr) {}
    void printMenu();
    void outputFullPlaylist();
    void addSong();
    void removeSong();
    void changePosition();
    void outputArtist();
    void outputTotalTime();
};

#endif
