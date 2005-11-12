
/*
 * config for cfgparser
 */

#include "cfg-common.h"

#ifdef USE_FAKE_MONO
extern int fakemono; // defined in dec_audio.c
#endif
#ifdef HAVE_ODIVX_POSTPROCESS
extern int use_old_pp;
#endif

extern int sws_flags;
extern int readPPOpt(void *, char *arg);
extern void revertPPOpt(void *conf, char* opt);
extern char *pp_help;

#ifdef HAVE_DIVX4ENCORE
extern m_option_t divx4opts_conf[];
#endif

#ifdef HAVE_MP3LAME
extern m_option_t lameopts_conf[];
#endif

#ifdef USE_LIBAVCODEC
extern m_option_t lavcopts_conf[];
#endif

#ifdef HAVE_TOOLAME
extern m_option_t toolameopts_conf[];
#endif

#ifdef HAVE_TWOLAME
extern m_option_t twolameopts_conf[];
#endif

#ifdef HAVE_FAAC
extern m_option_t faacopts_conf[];
#endif

#ifdef USE_WIN32DLL
extern m_option_t vfwopts_conf[];
#endif

#if defined(HAVE_XVID3) || defined(HAVE_XVID4)
extern m_option_t xvidencopts_conf[];
#endif

#if defined(HAVE_X264)
extern m_option_t x264encopts_conf[];
#endif

extern m_option_t nuvopts_conf[];
extern m_option_t mpegopts_conf[];
#ifdef USE_LIBAVFORMAT
extern m_option_t lavfopts_conf[];
#endif

m_option_t ovc_conf[]={
	{"copy", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_COPY, NULL},
	{"frameno", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_FRAMENO, NULL},
	{"divx4", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_DIVX4, NULL},
	{"lavc", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_LIBAVCODEC, NULL},
//	{"null", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_NULL, NULL},
	{"raw", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_RAW, NULL},
	{"vfw", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_VFW, NULL},
	{"libdv", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_LIBDV, NULL},
	{"xvid", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_XVID, NULL},
	{"qtvideo", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_QTVIDEO, NULL},
	{"nuv", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_NUV, NULL},
	{"x264", &out_video_codec, CONF_TYPE_FLAG, 0, 0, VCODEC_X264, NULL},
	{"help", "\nAvailable codecs:\n"
	"   copy     - frame copy, without re-encoding. Doesn't work with filters.\n"
	"   frameno  - special audio-only file for 3-pass encoding, see DOCS.\n"
	"   raw      - uncompressed video. Use fourcc option to set format explicitly.\n"
	"   nuv      - nuppel video\n"
#ifdef HAVE_DIVX4ENCORE
#ifdef ENCORE_XVID
	"   divx4    - XviD (divx4linux compatibility mode)\n"
#else
	"   divx4    - divx4linux/divx5linux library (depends on configuration)\n"
#endif
#endif
#ifdef USE_LIBAVCODEC
	"   lavc     - libavcodec codecs - best quality!\n"
#endif
#ifdef USE_WIN32DLL
	"   vfw      - VfW DLLs, currently only AVID is supported.\n"
	"   qtvideo  - QuickTime DLLs, currently only SVQ1/3 are supported.\n"
#endif
#ifdef HAVE_LIBDV095
	"   libdv    - DV encoding with libdv v0.9.5\n"
#endif
#if defined(HAVE_XVID3) || defined(HAVE_XVID4)
	"   xvid     - XviD encoding\n"
#endif
#ifdef HAVE_X264
	"   x264     - H.264 encoding\n"
#endif
	"\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
	{NULL, NULL, 0, 0, 0, 0, NULL}
};

m_option_t oac_conf[]={
	{"copy", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_COPY, NULL},
	{"pcm", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_PCM, NULL},
#ifdef HAVE_MP3LAME
	{"mp3lame", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_VBRMP3, NULL},
#else
	{"mp3lame", "MPlayer was compiled without libmp3lame support.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
#ifdef USE_LIBAVCODEC
	{"lavc", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_LAVC, NULL},
#else
	{"lavc", "MPlayer was compiled without libavcodec. See README or DOCS.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
#ifdef HAVE_TOOLAME
	{"toolame", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_TOOLAME, NULL},
#else
	{"toolame", "MPlayer was compiled without libtoolame. See README or DOCS.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
#ifdef HAVE_TWOLAME
	{"twolame", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_TWOLAME, NULL},
#else
	{"twolame", "MPlayer was compiled without libtwolame. See README or DOCS.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
#ifdef HAVE_FAAC
	{"faac", &out_audio_codec, CONF_TYPE_FLAG, 0, 0, ACODEC_FAAC, NULL},
#else
	{"faac", "MPlayer was compiled without libfaac. See README or DOCS.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
	{"help", "\nAvailable codecs:\n"
	"   copy     - frame copy, without re-encoding (useful for AC3)\n"
	"   pcm      - uncompressed PCM audio\n"
#ifdef HAVE_MP3LAME
	"   mp3lame  - cbr/abr/vbr MP3 using libmp3lame\n"
#endif
#ifdef USE_LIBAVCODEC
	"   lavc     - FFmpeg audio encoder (MP2, AC3, ...)\n"
#endif
#ifdef HAVE_TOOLAME
	"   toolame  - Toolame MP2 audio encoder\n"
#endif
#ifdef HAVE_TWOLAME
	"   twolame  - Twolame MP2 audio encoder\n"
#endif
#ifdef HAVE_FAAC
	"   faac     - FAAC AAC audio encoder\n"
#endif
	"\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
	{NULL, NULL, 0, 0, 0, 0, NULL}
};

m_option_t info_conf[]={
	{"name", &info_name, CONF_TYPE_STRING, 0, 0, 0, NULL},
	{"artist", &info_artist, CONF_TYPE_STRING, 0, 0, 0, NULL},
	{"genre", &info_genre, CONF_TYPE_STRING, 0, 0, 0, NULL},
	{"subject", &info_subject, CONF_TYPE_STRING, 0, 0, 0, NULL},
	{"copyright", &info_copyright, CONF_TYPE_STRING, 0, 0, 0, NULL},
	{"srcform", &info_sourceform, CONF_TYPE_STRING, 0, 0, 0, NULL},
	{"comment", &info_comment, CONF_TYPE_STRING, 0, 0, 0, NULL},
	{"help", "\nAvailable INFO fields:\n"
	"   name      - title of the work\n"
	"   artist    - artist or author of the work\n"
	"   genre     - original work category\n"
	"   subject   - contents of the work\n"
	"   copyright - copyright information\n"
	"   srcform   - original format of the digitzed material\n"
	"   comment   - general comments about the work\n"
	"\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
	{NULL, NULL, 0, 0, 0, 0, NULL}
};

m_option_t of_conf[]={
	{"avi", &out_file_format, CONF_TYPE_FLAG, 0, 0, MUXER_TYPE_AVI, NULL},
	{"mpeg", &out_file_format, CONF_TYPE_FLAG, 0, 0, MUXER_TYPE_MPEG, NULL},
#ifdef USE_LIBAVFORMAT
	{"lavf", &out_file_format, CONF_TYPE_FLAG, 0, 0, MUXER_TYPE_LAVF, NULL},
#endif
	{"rawvideo", &out_file_format, CONF_TYPE_FLAG, 0, 0, MUXER_TYPE_RAWVIDEO, NULL},
	{"rawaudio", &out_file_format, CONF_TYPE_FLAG, 0, 0, MUXER_TYPE_RAWAUDIO, NULL},
	{"help", "\nAvailable output formats:\n"
	"   avi      - Microsoft Audio/Video Interleaved\n"
	"   mpeg     - MPEG-1/2 system stream format\n"
#ifdef USE_LIBAVFORMAT
	"   lavf     - FFmpeg libavformat muxers\n"
#endif
	"   rawvideo - (video only, one stream only) raw stream, no muxing\n"
	"   rawaudio - (audio only, one stream only) raw stream, no muxing\n"
	"\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
	{NULL, NULL, 0, 0, 0, 0, NULL}
};

extern float avi_aspect_override; /* defined in libmpdemux/muxer_avi.c */
extern int write_odml; /* defined in libmpdemux/muxer_avi.c */

m_option_t mencoder_opts[]={
	/* name, pointer, type, flags, min, max */

	{"endpos", &end_at_string, CONF_TYPE_STRING, 0, 0, 0, NULL},

	{"frameno-file", &frameno_filename, CONF_TYPE_STRING, CONF_GLOBAL, 0, 0, NULL},

#ifdef USE_EDL
        {"hr-edl-seek", &edl_seek_type, CONF_TYPE_FLAG, 0, 0, 1, NULL},
        {"nohr-edl-seek", &edl_seek_type, CONF_TYPE_FLAG, 0, 1, 0, NULL},
#endif

	// set output framerate - recommended for variable-FPS (ASF etc) files
	// and for 29.97FPS progressive MPEG2 streams
	{"ofps", &force_ofps, CONF_TYPE_FLOAT, CONF_MIN|CONF_GLOBAL, 0, 0, NULL},
	{"o", &out_filename, CONF_TYPE_STRING, CONF_GLOBAL, 0, 0, NULL},

	// limit number of skippable frames after a non-skipped one
	{"skiplimit", &skip_limit, CONF_TYPE_INT, 0, 0, 0, NULL},
	{"noskiplimit", &skip_limit, CONF_TYPE_FLAG, 0, 0, -1, NULL},
	{"noskip", &skip_limit, CONF_TYPE_FLAG, 0, 0, 0, NULL},

	{"audio-density", &audio_density, CONF_TYPE_INT, CONF_RANGE|CONF_GLOBAL, 1, 50, NULL},
	{"audio-preload", &audio_preload, CONF_TYPE_FLOAT, CONF_RANGE|CONF_GLOBAL, 0, 2, NULL},
	{"audio-delay",   &audio_delay_fix, CONF_TYPE_FLOAT, CONF_MIN|CONF_GLOBAL, 0, 0, NULL},

	{"x", "-x is obsolete, use -vf scale=w:h for scaling.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
	{"xsize", "-xsize is obsolete, use -vf crop=w:h:x:y for cropping.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},

	// output audio/video codec selection
	{"oac", oac_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
	{"ovc", ovc_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},

	// output file format
	{"of", of_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},

	// override audio format tag in output file
	{"fafmttag", &force_audiofmttag, CONF_TYPE_INT, CONF_GLOBAL, 0, 0, NULL},
	// override FOURCC in output file
	{"ffourcc", &force_fourcc, CONF_TYPE_STRING, CONF_GLOBAL, 4, 4, NULL},

	// override avi aspect autodetection
	{"force-avi-aspect", &avi_aspect_override, CONF_TYPE_FLOAT, CONF_RANGE|CONF_GLOBAL, 0.2, 3.0, NULL},

	{"pass", "-pass is obsolete, use -lavcopts vpass=n, -xvidencopts pass=n, -divx4opts pass=n\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
	{"passlogfile", &passtmpfile, CONF_TYPE_STRING, CONF_GLOBAL, 0, 0, NULL},
	
	{"vobsubout", &vobsub_out, CONF_TYPE_STRING, CONF_GLOBAL, 0, 0, NULL},
	{"vobsuboutindex", &vobsub_out_index, CONF_TYPE_INT, CONF_RANGE|CONF_GLOBAL, 0, 31, NULL},
	{"vobsuboutid", &vobsub_out_id, CONF_TYPE_STRING, CONF_GLOBAL, 0, 0, NULL},

	{"autoexpand", &auto_expand, CONF_TYPE_FLAG, 0, 0, 1, NULL},
	{"noautoexpand", &auto_expand, CONF_TYPE_FLAG, 0, 1, 0, NULL},
	
	{"encodedups", &encode_duplicates, CONF_TYPE_FLAG, 0, 0, 1, NULL},
	{"noencodedups", &encode_duplicates, CONF_TYPE_FLAG, 0, 1, 0, NULL},
	
	{"odml", &write_odml, CONF_TYPE_FLAG, CONF_GLOBAL, 0, 1, NULL},
	{"noodml", &write_odml, CONF_TYPE_FLAG, CONF_GLOBAL, 1, 0, NULL},
	
	// info header strings
	{"info", info_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},

#ifdef HAVE_DIVX4ENCORE
	{"divx4opts", divx4opts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#endif
#ifdef HAVE_MP3LAME
	{"lameopts", lameopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#endif
#ifdef USE_LIBAVCODEC
	{"lavcopts", lavcopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#else
	{"lavcopts", "MPlayer was compiled without libavcodec. See README or DOCS.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
#ifdef HAVE_TOOLAME
	{"toolameopts", toolameopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#else
	{"toolameopts", "MPlayer was compiled without libtoolame. See README or DOCS.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
#ifdef HAVE_TWOLAME
	{"twolameopts", twolameopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#else
	{"twolameopts", "MPlayer was compiled without libtwolame. See README or DOCS.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
#ifdef HAVE_FAAC
	{"faacopts", faacopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#else
	{"faacopts", "MPlayer was compiled without libfaac. See README or DOCS.\n", CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
#endif
#ifdef USE_WIN32DLL
	{"xvfwopts", vfwopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#endif
#if defined(HAVE_XVID3) || defined(HAVE_XVID4)
	{"xvidencopts", xvidencopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#endif
#if defined(HAVE_X264)
	{"x264encopts", x264encopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#endif

	{"nuvopts",  nuvopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
	{"mpegopts",  mpegopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#ifdef USE_LIBAVFORMAT
	{"lavfopts",  lavfopts_conf, CONF_TYPE_SUBCONFIG, CONF_GLOBAL, 0, 0, NULL},
#endif	

#define MAIN_CONF
#include "cfg-common.h"
#undef MAIN_CONF

//	{"-help", help_text, CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
//	{"help", help_text, CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
//	{"h", help_text, CONF_TYPE_PRINT, CONF_NOCFG, 0, 0, NULL},
	{NULL, NULL, 0, 0, 0, 0, NULL}
};
