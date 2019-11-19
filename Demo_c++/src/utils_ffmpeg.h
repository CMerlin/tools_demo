#ifndef _UTILS_FFMPEG_H_
#define _UTILS_FFMPEG_H_

//int ffmepg_func(char *str);


#ifndef _FFMediaInfoReader_H
#define _FFMediaInfoReader_H
 
#include <string>
using namespace std;
 
#ifdef __cplusplus
extern "C" {
#endif 
 
#ifdef HAVE_AV_CONFIG_H
#undef HAVE_AV_CONFIG_H
#endif

#if 1
//#include <avcodec.h>
//#include <include/libavcodec/avcodec.h>
//#include "libavcodec/avcodec.h"
#include "libavutil/mathematics.h"
#include "libavutil/avutil.h"
#include "libswscale/swscale.h"
#include "libavutil/fifo.h"
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
#include "libavutil/error.h"
#include "libavutil/pixfmt.h"
#include "libswresample/swresample.h"
#endif


#if 0
#include "./include/libavcodec/avcodec.h"
#include "./include/libavutil/mathematics.h"
#include "./include/libavutil/avutil.h"
#include "./include/libswscale/swscale.h"
#include "./include/libavutil/fifo.h"
#include "./include/libavformat/avformat.h"
#include "./include/libavutil/opt.h"
#include "./include/libavutil/error.h"
#include "./include/libavutil/pixfmt.h"
#include "./include/libswresample/swresample.h"
#endif

#ifdef __cplusplus
}
#endif
 
#pragma comment( lib, "avcodec.lib")
#pragma comment( lib, "avutil.lib")
#pragma comment( lib, "avformat.lib")
#pragma comment(lib, "swresample.lib")
#pragma comment( lib, "swscale.lib" )
 
#define PIX_FMT_BGR24    AV_PIX_FMT_BGR24
#define PIX_FMT_YUV420P  AV_PIX_FMT_YUV420P
 
#define nullptr NULL
 
class FFMediaInfoReader
{
public:
    FFMediaInfoReader();
    virtual ~FFMediaInfoReader();
 
    BOOL OpenFileStream(const char* szFilePath);
    void CloseFileStream();
 
	//获取视频分辨率
	void GetVideoSize(int & width, int & height) 
	{
		width  = m_width;
		height = m_height;
	}
 
	string GetMediaFormatName(); //获取媒体封装格式描述
 
	//获取媒体轨道数目
	int    GetTrackNum()
	{
		int n = 0;
 
		if(HasVideoTrack())
			n += 1;
		if(HasAudioTrack())
			n += 1;
		return n;
	}
 
	//是否有视频流
	bool    HasVideoTrack()
	{
		if( m_videoStreamIndex == -1)
			return false;
 
		if(m_width > 0 && m_height > 0)
			return true;
 
		return false;
	}
 
	//是否有音频流
	bool    HasAudioTrack()
	{
		if(m_audioStreamIndex == -1)
			return false;
 
		return true;
	}
 
	//获取视频帧数
	int  GetVideoFrameNumber()
	{
		return m_video_frame_count;
	}
 
	//获取文件总的码率
	int GetFormatBitrate()
	{
		if(m_inputAVFormatCxt == NULL)
			return -1;
 
		return m_inputAVFormatCxt->bit_rate;
	}
 
	//文件播放时长（单位：秒）
	int  GetFileDuration()
	{
		if(m_inputAVFormatCxt == NULL)
			return -1;
 
		return (m_inputAVFormatCxt->duration)/1000000; //以微秒为单位，转换为秒为单位
	}
 
	string GetVideoCodecName()
	{
		return m_vcodec_name;
	}
 
	string GetAudioCodecName()
	{
		return m_acodec_name;
	}
 
private:
 
    BOOL openMediaFile();
    void closeMediaFile();
 
private:
 
    string m_filePath;
 
    AVFormatContext* m_inputAVFormatCxt;
 
	int m_videoStreamIndex;
	int m_audioStreamIndex;
 
	string   m_vcodec_name;
	string   m_acodec_name;
 
    char m_tmpErrString[64];
    bool m_stop_status;
 
	BOOL   m_bInited;
 
	int m_width, m_height; //视频分辨率
    int   m_video_frame_count; //视频总帧数
	int   m_frame_rate; //视频帧率
 
	int  m_audio_samplerate;
	int  m_audio_channels;
   
};
 
#endif // _FFMediaInfoReader_H



#endif
