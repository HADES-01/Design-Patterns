/**
 *  @cite Facade Patttern states that in order to keep the end-user API simple and easy-to-use, an interface should be built over the all the complex sub-systems.
 * Aims at increasing Code Readabilty by simplifying the API.
 *
 * @brief Facade Pattern can exemplified by a Television Class that has a multitude of sub-systems (VideoDecoder, AudioDecoder, etc.) but provides a simple API of 'play_movie()' to play a movie.
 */

#include <iostream>
#include <string>

/**
 * @brief Decodes the encode audio from the file. 
 */
class AudioDecoder
{
public:
    std::string decode_audio(std::string encoded_audio)
    {
        std::cout << "Decoding Audio from "+ encoded_audio + "....\n";
        return "Decoded " + encoded_audio;
    }
};

/**DA
 * @brief Decodes the encoded video from the file.
 */
class VideoDecoder
{
public:
    std::string decode_video(std::string encoded_video)
    {
        std::cout << "Decoding Video from " + encoded_video +  "...\n";
        return "Decoded " + encoded_video;
    }
};

/**
 * @brief Displays the video after it is decoded.
 */
class DisplayVideo
{
public:
    void play_video(std::string decoded_video)
    {
        std::cout << "Displaying " + decoded_video + "\n";
    }
};

/**
 * @brief Plays the audio from the decoded audio format.
 */
class PlayAudio
{
public:
    void play_audio(std::string decoded_audio)
    {
        std::cout << "Playing " + decoded_audio + "\n";
    }
};

/**
 * @brief Facade over the all the complex subsytems of Decoding and Playing.
 */
class Television
{
    VideoDecoder vd;
    AudioDecoder ad;
    DisplayVideo dv;
    PlayAudio pa;

public:
    void play_movie(std::string filename)
    {
        auto decoded_video = vd.decode_video(filename);
        auto decoded_audio = ad.decode_audio(filename);
        {
            // Happening simultaneously on separate threads.
            dv.play_video(decoded_video);
            pa.play_audio(decoded_audio);
        }
    }
};

int main()
{
    {
        // ! Without using the Television Facade the use of API becomes very complex as the API is not abstracted enough.
        VideoDecoder vd;
        AudioDecoder ad;
        DisplayVideo dv;
        PlayAudio pa;
        std::string filename = "HelloWorld.mkv";
        auto decoded_video = vd.decode_video(filename);
        auto decoded_audio = ad.decode_audio(filename);
        {   
            // ! Happening simultaneously on separate threads that further adds to the complexity.
            dv.play_video(decoded_video);
            pa.play_audio(decoded_audio);
        }
        std::cout << std::endl << std::endl;
    }

    // * Use of API is very simple and completely abstracted.
    Television tv;
    tv.play_movie("HelloWorld.mp4");
    
    return 0;
}