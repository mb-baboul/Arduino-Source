/*  Audio Sink
 *
 *  From: https://github.com/PokemonAutomation/Arduino-Source
 *
 *      AudioSink represents an audio output stream. Once constructed,
 *  you can push float audio samples to it and it will play it from the
 *  respective speaker or whatever.
 *
 */

#ifndef PokemonAutomation_AudioPipeline_AudioSink_H
#define PokemonAutomation_AudioPipeline_AudioSink_H

#include <memory>
#include "CommonFramework/AudioPipeline/AudioInfo.h"
#include "CommonFramework/AudioPipeline/AudioStream.h"

class QObject;

namespace PokemonAutomation{

class Logger;
class AudioSinkWriter;


class AudioSink{
public:
    ~AudioSink();
    AudioSink(Logger& logger, const AudioDeviceInfo& device, AudioFormat format);

    size_t sample_rate() const{ return m_sample_rate; }
    size_t channels() const{ return m_channels; }
    size_t samples_per_frame() const{ return m_channels * m_multiplier; }

    operator AudioFloatStreamListener&(){ return *m_writer; }

    void set_volume(float volume);


private:
    Logger& m_logger;

    size_t m_sample_rate;
    size_t m_channels;
    size_t m_multiplier;

    std::unique_ptr<QObject> m_device;
    std::unique_ptr<AudioSinkWriter> m_writer;
};



}
#endif