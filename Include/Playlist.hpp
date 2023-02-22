// Copyright 2023  Eraj eradzh@2017@mail.ru

#ifndef INCLUDE_PLAYLIST_HPP
#define INCLUDE_PLAYLIST_HPP

#include <list>
#include <mutex>
#include <string>

#include <Song.hpp>

class Playlist {
public:
	void Play();
	void Pause();
	void AddSong(Song song);
	void Next();
	void Prev();
	Playlist() : current_song(songs.end()) {}

private:
	std::list<Song> songs;
	std::list<Song>::iterator current_song;
	bool playing = false;
	bool paused = false;
};

#endif //INCLUDE_PLAYLIST_HPP
