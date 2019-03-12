#include "IAudioFile.h"

IAudioFile<float>::IAudioFile() : SamplesPtr(&samples)  {}

IAudioFile<double>::IAudioFile() : SamplesPtr(&samples) {}