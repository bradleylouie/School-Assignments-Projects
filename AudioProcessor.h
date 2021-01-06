#include <vector>
#include <stdexcept>
class AudioProcessor
{
    public:
        std::vector<short> Compress(const std::vector<short>& audio, short threshold, float rate)
        {
            if (threshold < 0)
                throw std::invalid_argument("Compress threshold too low");
            if (rate < 1.0f)
                throw std::invalid_argument("Compress rate too low");

            std::vector<short> compressed_audio;
            for (auto& bit: audio)
            {
                if (bit > threshold)
                    compressed_audio.push_back((short) (threshold + ((bit-threshold) / rate) + 0.5f));
                else if (bit < -threshold)
                    compressed_audio.push_back((short) -(threshold + ((-bit-threshold) / rate) + 0.5f));
                else
                    compressed_audio.push_back(bit);
            }
            return compressed_audio;
        }

        std::vector<short> CutOutSilence(const std::vector<short>& audio, short level, int silenceLength)
        {
            if (level < 0)
                throw std::invalid_argument("CutOutSilence level too low");
            if (silenceLength < 1)
                throw std::invalid_argument("CutOutSilence silenceLength too low");
            int curr_silence_length = 0;
            std::vector<short> silent_portion_candidate;
            std::vector<short> clipped_audio;

            for (int i = 0; i < audio.size(); i++)
            {
                short bit = audio.at(i);
                if ((bit > -1 && bit <= level) || (bit < 0 && bit >= -level))
                {
                    curr_silence_length++;
                    silent_portion_candidate.push_back(bit);
                }
                else
                {
                    if (curr_silence_length >= silenceLength)
                    {
                        curr_silence_length = 0;
                        silent_portion_candidate.clear();
                    } 
                    else if (curr_silence_length > 0)
                    {
                        curr_silence_length = 0;
                        for (auto& sbit: silent_portion_candidate)
                            clipped_audio.push_back(sbit);
                        silent_portion_candidate.clear();
                    }
                    clipped_audio.push_back(bit);
                } 
            }
            if (curr_silence_length < silenceLength)
                for (auto& sbit: silent_portion_candidate)
                    clipped_audio.push_back(sbit);
            return clipped_audio;
        }

        std::vector<short> StretchTwice(const std::vector<short>& audio)
        {
            std::vector<short> stretched_audio;
            if (audio.size() == 1)
                stretched_audio = audio;
            else if (!audio.empty())
            {
                for(int i = 0; i < audio.size()-1; i++)
                {
                    stretched_audio.push_back(audio.at(i));
                    if (audio.at(i) > 0)
                        stretched_audio.push_back((short) (((float) audio.at(i) + (float) audio.at(i+1))*0.5f + 0.5f));
                    else
                        stretched_audio.push_back((short) (((float) audio.at(i) + (float) audio.at(i+1))*0.5f - 0.5f));
                }
                stretched_audio.push_back(audio.back());
            }
            return stretched_audio;
        }

        std::vector<short> Normalize(const std::vector<short>& audio, short normalizeTarget)
        {
            if (normalizeTarget < 1)
                throw std::invalid_argument("Normalize normalizeTarget too low");
            short max_val = 0;
            for (auto& bit: audio)
            {
                if (bit > -1 && bit > max_val)
                    max_val = bit;
                else if (bit < 0 && bit < -max_val)
                    max_val = -bit;
            }
            float scale_val = ((float) normalizeTarget) / ((float) max_val);
            std::vector<short> normalized_audio;
            for (auto& bit: audio)
            {
                if (bit > 0)
                    normalized_audio.push_back((short) ((float) bit * scale_val + 0.5f));
                else
                    normalized_audio.push_back((short) ((float) bit * scale_val - 0.5f));
            }
            return normalized_audio;
        }
};