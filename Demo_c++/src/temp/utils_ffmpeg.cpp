#include  <stdio.h>
#include "utils_ffmpeg.h"

#include "stdafx.h"
#include "FFMediaInfoReader.h"
#include <sstream>
//#include <mmsystem.h>


#if 0
int ffmepg_func(char *str){
	printf("[%s][%d]:str=%s\n", __func__, __LINE__, str);
	return 0;
}
#endif
 
string to_string(int n)
{
	std::ostringstream stm;
	string str;
	stm << n;
	str = stm.str();
	//std::cout << str << std::endl;
	return str;
}
 
 
//////////////////////////////////////////////////////////////
 
FFMediaInfoReader::FFMediaInfoReader()
{
    m_stop_status = false;
 
    m_inputAVFormatCxt = nullptr;
 
    m_videoStreamIndex = -1;
	m_audioStreamIndex = -1;
 
	m_bInited = FALSE;
    m_width = m_height = 0;
    m_frame_rate = 25;
    m_video_frame_count = 0;
	m_audio_samplerate = 0;
	m_audio_channels = 0;
 
	 /* register all codecs, demux and protocols */
    avcodec_register_all();
    av_register_all();
}
 
FFMediaInfoReader::~FFMediaInfoReader()
{
	CloseFileStream();
}
 
 
BOOL FFMediaInfoReader::OpenFileStream(const char* szFilePath)
{
    m_filePath   = szFilePath;
    m_video_frame_count = 0;
    m_videoStreamIndex = -1;
	m_audioStreamIndex = -1;
	m_vcodec_name = "";
	m_acodec_name = "";
	m_width = m_height = 0;
    m_audio_samplerate = 0;
	m_audio_channels = 0;
    m_video_frame_count = 0;
    m_bInited = FALSE;
 
	return openMediaFile();
}
 
 
void FFMediaInfoReader::CloseFileStream()
{
    m_stop_status = true;
 
    closeMediaFile();
    m_bInited = FALSE;
}
 
 
//打开输入文件
BOOL FFMediaInfoReader::openMediaFile()
{
    if (m_inputAVFormatCxt)
    {
        TRACE("already has input avformat \n");
		return FALSE;
    }
 
    int res = 0;
 
    if ((res = avformat_open_input(&m_inputAVFormatCxt, m_filePath.c_str(), 0, NULL)) < 0)
    {
  
    }
    
    if(res < 0)
    {
        string strError = "can not open file:" + m_filePath + ",errcode:" + to_string(res) + ",err msg:" + av_make_error_string(m_tmpErrString, AV_ERROR_MAX_STRING_SIZE, res);
		TRACE("--------------%s \n", strError.c_str());
		return FALSE;
    }
 
    if (avformat_find_stream_info(m_inputAVFormatCxt, 0) < 0)
    {
        TRACE("can not find stream info \n");
		return FALSE;
    }
 
	TRACE("filepath: %s, format: %s, Bitrate: %d Kbps \n",  m_filePath.c_str(), m_inputAVFormatCxt->iformat->name, m_inputAVFormatCxt->bit_rate/1000);
 
    av_dump_format(m_inputAVFormatCxt, 0, m_filePath.c_str(), 0);
    for (int i = 0; i < m_inputAVFormatCxt->nb_streams; i++)
    {
        AVStream *in_stream = m_inputAVFormatCxt->streams[i];
 
		if (in_stream->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_videoStreamIndex = i;
 
			m_width = in_stream->codec->width;
			m_height = in_stream->codec->height;
 
			if(in_stream->avg_frame_rate.den != 0 && in_stream->avg_frame_rate.num != 0)
			{
			  m_frame_rate = in_stream->avg_frame_rate.num/in_stream->avg_frame_rate.den;//每秒多少帧 
			}
 
			m_video_frame_count = in_stream->nb_frames; //视频帧数
 
			//m_vcodec_name = in_stream->codec->codec_name; //获取编码器名称。不行，这里获得的名字是空的，后面用别的方法
 
			TRACE("Video Track---stream index: %d, codec id: %d,  width: %d, height: %d, FrameRate: %d, Number of Frames: %d\n", 
				i, in_stream->codec->codec_id,  in_stream->codec->width, in_stream->codec->height, m_frame_rate, m_video_frame_count);
		}
		else if (in_stream->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			m_audioStreamIndex = i;
 
			m_audio_samplerate =  in_stream->codec->sample_rate;
	        m_audio_channels = in_stream->codec->channels;
 
			//m_acodec_name = in_stream->codec->codec_name; //获取编码器名称。不行，这里获得的名字是空的，后面用别的方法
 
			TRACE("Audio Track---stream index: %d, codec id: %d,  sample_rate: %d, channels: %d \n", 
				i, in_stream->codec->codec_id,  in_stream->codec->sample_rate, in_stream->codec->channels);
		}
    }
 
 
	if(m_videoStreamIndex != -1)
	{
		AVCodecContext *avctx;
		AVCodec *codec;
 
		do
		{
			avctx = m_inputAVFormatCxt->streams[m_videoStreamIndex]->codec;
			// 寻找视频解码器
			codec = avcodec_find_decoder(avctx->codec_id);
			if(codec == NULL)
				break;
 
			m_vcodec_name = codec->long_name; //视频编码器名称
 
            TRACE("video_codec name: %s \n", codec->long_name);
 
		}while(0);
	}
 
	
	if(m_audioStreamIndex != -1)
	{
		AVCodecContext *avctx;
		AVCodec *codec;
 
		do
		{
			avctx = m_inputAVFormatCxt->streams[m_audioStreamIndex]->codec;
			// 寻找音频解码器
			codec = avcodec_find_decoder(avctx->codec_id);
			if(codec == NULL)
				break;
 
			m_acodec_name = codec->long_name; //音频编码器名称
 
			TRACE("audio_codec_name: %s \n", codec->long_name);
 
		}while(0);
	}
 
#if 1
	int nVFrames = 0;
	bool bAudioDecoderInited = false;
	int ret;
 
	AVPacket pkt;
	av_init_packet(&pkt);
 
	//一帧一帧读取
	while (av_read_frame(m_inputAVFormatCxt, &pkt) >= 0)
	{
		if(pkt.stream_index == m_videoStreamIndex)
		{
			AVStream * pStream = m_inputAVFormatCxt->streams[m_videoStreamIndex];
 
			nVFrames++;
		}//Video
 
		else if(pkt.stream_index == m_audioStreamIndex)
		{
			AVStream * pStream = m_inputAVFormatCxt->streams[m_audioStreamIndex];
 
			if (!bAudioDecoderInited)
			{
				if (avcodec_open2(pStream->codec, avcodec_find_decoder(pStream->codec->codec_id), NULL) < 0)
				{
					TRACE("Could not open audio codec.（无法打开解码器）\n");
					break;
				}
 
				bAudioDecoderInited = true;
			}
 
 
			int dec_got_frame_a = 0;
		
 
			AVFrame *input_frame = av_frame_alloc();
			if (!input_frame)
			{
				ret = AVERROR(ENOMEM);
				break;
			}
			//解码为PCM音频
			if ((ret = avcodec_decode_audio4(pStream->codec, input_frame, &dec_got_frame_a, &pkt)) < 0)
			{
				TRACE("Could not decode audio frame.\n");
				
				av_frame_free(&input_frame);
				break;
			}
 
			if (dec_got_frame_a) //解码出一帧
			{
				//获得音频属性（音频输出格式、采样率、声道数）
				TRACE("audio_sample_format: %d, sample_rate: %d, channels: %d \n",  pStream->codec->sample_fmt, pStream->codec->sample_rate, pStream->codec->channels);
			}
 
			av_frame_free(&input_frame);
 
			//注意：这里根据你的需求情况决定是否屏蔽以下代码
			if(dec_got_frame_a) //获取到音频信息后是否跳出循环？？
				break;
 
		} //Audio
 
		av_free_packet(&pkt);
	}
 
	if(m_video_frame_count == 0)
	{
		m_video_frame_count = nVFrames; //更新视频帧数
	}
 
#endif
 
	m_bInited = FALSE;
	return TRUE;
}
 
 
void FFMediaInfoReader::closeMediaFile()
{
    if (m_inputAVFormatCxt)
    {
        avformat_close_input(&m_inputAVFormatCxt);
		m_inputAVFormatCxt = NULL;
    }
}
 
 
string FFMediaInfoReader::GetMediaFormatName()
{
	if(m_inputAVFormatCxt == NULL)
		return "";
 
	//return m_inputAVFormatCxt->iformat->name;
	return m_inputAVFormatCxt->iformat->long_name;
}
--------------------------------------------------------------------------------------------------------------------------

知识点讲解
对代码中一些重点的部分讲解一下。

首先，要调用FFmpeg获取文件的相关信息，肯定要先打开一个文件，然后获取相关媒体流（视频流、音频流）对应的轨道。

1. 打开一个文件。

   int res = 0;
    if ((res = avformat_open_input(&m_inputAVFormatCxt, m_filePath.c_str(), 0, NULL)) < 0)
    {
 
    }
    if(res < 0)
    {
        string strError = "can not open file:" + m_filePath + ",errcode:" + std::to_string((int)res) + ",err msg:" + av_make_error_string(m_tmpErrString, AV_ERROR_MAX_STRING_SIZE, res);
        TRACE("%s \n", strError.c_str());
        return false;
    }
    if (avformat_find_stream_info(m_inputAVFormatCxt, 0) < 0)
    {
       TRACE("can not find stream info \n");
       return false;
    }
    av_dump_format(m_inputAVFormatCxt, 0, m_filePath.c_str(), 0);
2. 获取各个流的轨道（StreamIndex）
————————————————
版权声明：本文为CSDN博主「zhoubotong2012」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/zhoubotong2012/article/details/79340722


