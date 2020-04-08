//
// Created by hoang on 1/8/2020.
//

#include "Playlist.h"
#include <string>
#include <iostream>
using namespace std;

void Playlist::printMenu()
{
    char input;
    std::cout << title << " PLAYLIST MENU" << std::endl;
    std::cout << "a - Add song" << std::endl;
    std::cout << "d - Remove song" << std::endl;
    std::cout << "c - Change position of song" << std::endl;
    std::cout << "s - Output songs by specific artist" << std::endl;
    std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
    std::cout << "o - Output full playlist" << std::endl;
    std::cout << "q - Quit" << std::endl << std:: endl;
    std::cout << "Choose an option:" << std::endl;

    std::cin >> input;
    while(input != 'q')
    {
        if(input == 'a')
        {
            addSong();
            std::cout << title << " PLAYLIST MENU" << std::endl;
            std::cout << "a - Add song" << std::endl;
            std::cout << "d - Remove song" << std::endl;
            std::cout << "c - Change position of song" << std::endl;
            std::cout << "s - Output songs by specific artist" << std::endl;
            std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
            std::cout << "o - Output full playlist" << std::endl;
            std::cout << "q - Quit" << std::endl << std:: endl;
            std::cout << "Choose an option:" << std::endl;

            std::cin >> input;

        }
        if(input == 'd')
        {
            removeSong();
            std::cout << title << " PLAYLIST MENU" << std::endl;
            std::cout << "a - Add song" << std::endl;
            std::cout << "d - Remove song" << std::endl;
            std::cout << "c - Change position of song" << std::endl;
            std::cout << "s - Output songs by specific artist" << std::endl;
            std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
            std::cout << "o - Output full playlist" << std::endl;
            std::cout << "q - Quit" << std::endl << std:: endl;
            std::cout << "Choose an option:" << std::endl;

            std::cin >> input;
        }
        if(input == 'c')
        {
            changePosition();
            std::cout << title << " PLAYLIST MENU" << std::endl;
            std::cout << "a - Add song" << std::endl;
            std::cout << "d - Remove song" << std::endl;
            std::cout << "c - Change position of song" << std::endl;
            std::cout << "s - Output songs by specific artist" << std::endl;
            std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
            std::cout << "o - Output full playlist" << std::endl;
            std::cout << "q - Quit" << std::endl << std:: endl;
            std::cout << "Choose an option:" << std::endl;

            std::cin >> input;
        }
        if(input == 's')
        {
            outputArtist();
            std::cout << title << " PLAYLIST MENU" << std::endl;
            std::cout << "a - Add song" << std::endl;
            std::cout << "d - Remove song" << std::endl;
            std::cout << "c - Change position of song" << std::endl;
            std::cout << "s - Output songs by specific artist" << std::endl;
            std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
            std::cout << "o - Output full playlist" << std::endl;
            std::cout << "q - Quit" << std::endl << std:: endl;
            std::cout << "Choose an option:" << std::endl;

            std::cin >> input;
        }
        if(input == 't')
        {
            outputTotalTime();
            std::cout << title << " PLAYLIST MENU" << std::endl;
            std::cout << "a - Add song" << std::endl;
            std::cout << "d - Remove song" << std::endl;
            std::cout << "c - Change position of song" << std::endl;
            std::cout << "s - Output songs by specific artist" << std::endl;
            std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
            std::cout << "o - Output full playlist" << std::endl;
            std::cout << "q - Quit" << std::endl << std:: endl;
            std::cout << "Choose an option:" << std::endl;

            std::cin >> input;
        }
        if(input == 'o')
        {
            outputFullPlaylist();
            std::cout << title << " PLAYLIST MENU" << std::endl;
            std::cout << "a - Add song" << std::endl;
            std::cout << "d - Remove song" << std::endl;
            std::cout << "c - Change position of song" << std::endl;
            std::cout << "s - Output songs by specific artist" << std::endl;
            std::cout << "t - Output total time of playlist (in seconds)" << std::endl;
            std::cout << "o - Output full playlist" << std::endl;
            std::cout << "q - Quit" << std::endl << std:: endl;
            std::cout << "Choose an option:" << std::endl;

            std::cin >> input;
        }
        if(input != 'a' && input != 'd' && input != 'c' && input != 's' && input != 't' && input != 'o' && input != 'q')
        {
            std::cout << "Choose a valid option: ";
            std::cin >> input;
            std::cout << std::endl;

        }
    }

}

void Playlist::outputFullPlaylist()
{
    std::cout << title << " - OUTPUT FULL PLAYLIST" << std::endl;
    if(head == nullptr)
    {
        std::cout << "Playlist is empty" << std::endl << std::endl;
    }
    else
    {
        int cnt = 1;
        PlaylistNode *curr = head;
        while (curr)
        {
            std::cout << cnt << "." << std::endl;
            curr->PrintPlaylistNode();
            std::cout << std::endl;
            curr = curr->GetNext();
            cnt++;
        }
    }
}
void Playlist::addSong()
{
    std::cout << "ADD SONG" << std::endl;
    std::string iD;
    std::string songName;
    std::string artistName;
    int songLength;
    std::cout << "Enter song's unique ID:" << std::endl;
    std::cin >> iD;
    std::cout << "Enter song's name:" << std::endl;
    std::cin.ignore();
    getline(std::cin, songName);
    std::cout << "Enter artist's name:" << std::endl;
    getline(std::cin, artistName);
    std::cout << "Enter song's length (in seconds):" << std::endl;
    std::cin >> songLength;
    std::cout << std::endl;
    if(head == nullptr)
    {
        head = new PlaylistNode(iD, songName, artistName, songLength);
    }
    else
    {
        PlaylistNode* curr = head;
        while(curr->GetNext() != nullptr)
        {
            curr = curr->GetNext();
        }
        curr->SetNext(new PlaylistNode(iD, songName, artistName, songLength));
    }
}
void Playlist::removeSong()
{
    std::string iD;
    std::cout << "REMOVE SONG" << std::endl;
    std::cout << "Enter song's unique ID:";
    std::cin >> iD;
    std::cout << std::endl;
    if(head == nullptr)
    {
        std::cout << "Empty Playlist!!!" << std::endl;
    }
    if(head->GetID() == iD)
    {
        PlaylistNode* curr = head->GetNext();
        std::cout << "\"" << head->GetSongName() << "\"" << " removed" << std::endl;
        delete head;
        head = curr;
    }
    else
    {
        PlaylistNode* curr = head;
        while(curr->GetNext() != nullptr)
        {
            if(curr->GetNext()->GetID() == iD)
            {
                PlaylistNode* temp = curr->GetNext();
                std::cout << "\"" << temp->GetSongName() << "\"" << " removed." << std::endl << std::endl;
                curr->SetNext(curr->GetNext()->GetNext());
                delete temp;
            }
            curr = curr->GetNext();
        }

    }


}

void Playlist::changePosition()
{
    int currPos;
    int newPos;
    std::cout << "CHANGE POSITION OF SONG" << std::endl;
    std::cout << "Enter song's current position:" << std::endl;
    std::cin >> currPos;
    std::cout << "Enter new position for song:" << std::endl;
    std::cin >> newPos;
    PlaylistNode* move;
    if(currPos <= 1)
    {
        move = head;
        head = head->GetNext();
    }
    else
    {
        PlaylistNode *curr = head;
        int cnt = 1;
        while(curr->GetNext() != nullptr && cnt != currPos-1)
        {
            curr = curr->GetNext();
            cnt++;
        }
        move = curr->GetNext();
        curr->SetNext(curr->GetNext()->GetNext());
    }
    //Now we move the pointer to the new part.
    if(newPos <= 1)
    {
        move->SetNext(head);
        head = move;
    }
    else
    {
        PlaylistNode *curr = head;
        int cnt = 1;
        while(curr->GetNext() != nullptr && cnt != newPos-1)
        {
            curr = curr->GetNext();
            cnt++;
        }
        if(curr->GetNext() == nullptr)
        {
            curr->SetNext(move);
            move->SetNext(nullptr);
        }
        else
        {
            move->SetNext(curr->GetNext());
            curr->SetNext(move);
        }
    }
    std::cout << "\"" << move->GetSongName() << "\"" << " moved to position " << newPos << std::endl << std::endl;
}
void Playlist::outputArtist()
{
    std::cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << std::endl;
    std::string name;
    std::cout << "Enter artist's name:" << std::endl;
    std::cin.ignore();
    getline(std::cin, name);
    std::cout << std::endl;
    PlaylistNode* curr = head;
    int cnt = 1;
    while(curr != nullptr)
    {
        if(curr->GetArtistName() == name)
        {
            std::cout << cnt << "." << std::endl;
            curr->PrintPlaylistNode();
            std::cout << std::endl;
        }
        curr = curr->GetNext();
        cnt++;

    }
}
void Playlist::outputTotalTime()
{
    std::cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << std::endl;
    int total = 0;
    PlaylistNode *curr = head;
    while (curr != nullptr) {
        total += curr->GetSongLength();
        curr = curr->GetNext();
    }
    std::cout << "Total time: " << total << " seconds" << std::endl;
    std::cout << std::endl;
}
