#ifndef _mov_reader_h_
#define _mov_reader_h_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void* mov_reader_create(const char* file);
void mov_reader_destroy(void* mov);

// @param[in] avtype: MOV_AVC1/MOV_MP4A
typedef void(*mov_reader_onvideo)(void* param, int avtype, int width, int height, const void* extra, size_t bytes);
typedef void(*mov_reader_onaudio)(void* param, int avtype, int channel_count, int bit_per_sample, int sample_rate, const void* extra, size_t bytes);
int mov_reader_getinfo(void* mov, mov_reader_onvideo onvideo, mov_reader_onaudio onaudio, void* param);

// audio: AAC raw data, don't include ADTS/AudioSpecificConfig
// video: 4-byte data length(don't include self length) + H.264 NALU(don't include 0x00000001)
typedef void (*mov_reader_onread)(void* param, int avtype, const void* buffer, size_t bytes, int64_t pts, int64_t dts);
int mov_reader_read(void* mov, void* buffer, size_t bytes, mov_reader_onread onread, void* param);

#ifdef __cplusplus
}
#endif
#endif /* !_mov_reader_h_*/
