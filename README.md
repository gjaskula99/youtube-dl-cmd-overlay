# youtube-dl cmd overlay

Simple command-line C++ program to exec [youtube-DL](https://github.com/ytdl-org/youtube-dl) commands with ease. As I had troubles remembering all it's commands and flags...
Supports file input and bulk download of multiple URLs. URLs are downloaded as MP4. When choosing MP3 ffmpeg will be called for converting MP4 to MP3. PLAYLIST option forces youtube-DL to download entire playlist.

## File read

File should have following structure, be placed in same directory as executable and be encoded as plain text file.

> LINK
> 
> MP4/MP3/PLAYLIST
> 
> LINK
> 
> MP4/MP3/PLAYLIST
> 
> ...

Like:
> https://youtu.be/dQw4w9WgXcQ
> 
> MP4

## Notes / known issues
- If link contains ?list attribute program will attempt to download entie playlist even if not using PLAYLIST switch.
