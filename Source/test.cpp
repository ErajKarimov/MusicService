#include <Playlist.hpp>
#include <Song.hpp>
#include <gtest/gtest.h>

 std::string u_id = "Kali";
TEST(PlaylistTest, AddSong) {
    Playlist playlist(u_id);
    Song song1("song1", 100);
    Song song2("song2", 200);
    playlist.AddSong(song1);
    playlist.AddSong(song2);
    EXPECT_EQ(playlist.GetSongs().size(), 2);
}

TEST(PlaylistTest, DeleteSong) {
    Playlist playlist(u_id);
    Song song1("song1", 100);
    Song song2("song2", 200);
    playlist.AddSong(song1);
    playlist.AddSong(song2);
    playlist.DeleteSong("song1", 100);
    EXPECT_EQ(playlist.GetSongs().size(), 1);
}

TEST(PlaylistTest, Next) {
    Playlist playlist(u_id);
    Song song1("song1", 100);
    Song song2("song2", 200);
    playlist.AddSong(song1);
    playlist.AddSong(song2);
    playlist.Play();
    EXPECT_EQ(playlist.GetSongs().size(), 2);
    EXPECT_EQ(playlist.current_song->GetName(), "song1");
    playlist.Next();
    EXPECT_EQ(playlist.current_song->GetName(), "song2");
}

TEST(PlaylistTest, Prev) {
    Playlist playlist(u_id);
    Song song1("song1", 100);
    Song song2("song2", 200);
    playlist.AddSong(song1);
    playlist.AddSong(song2);
    EXPECT_EQ(playlist.GetSongs().size(), 2);
    playlist.Next(); playlist.Next();
    playlist.Prev();
    EXPECT_EQ(playlist.current_song->GetName(), "song2");
    playlist.Prev();
    EXPECT_EQ(playlist.current_song->GetName(), "song1");
}

TEST(PlaylistTest, PauseAndResume) {
    Playlist playlist(u_id);
    Song song1("song1", 100);
    Song song2("song2", 200);
    playlist.AddSong(song1);
    playlist.AddSong(song2);
    playlist.Play();
    EXPECT_FALSE(playlist.paused);
    playlist.Pause();
    EXPECT_TRUE(playlist.paused);
    playlist.Play();
    EXPECT_FALSE(playlist.paused);
}


TEST(PlaylistTest, UpdateSong) {
    Playlist playlist(u_id);
    Song song1("song1", 100);
    Song song2("song2", 200);
    playlist.AddSong(song1);
    playlist.AddSong(song2);
    playlist.UpdateSong("song1", 50);
    playlist.UpdateSong("song2", 50);
    for (const auto& song : playlist.GetSongs()) {
        EXPECT_EQ(song.GetDuration(), 50);
    }
}