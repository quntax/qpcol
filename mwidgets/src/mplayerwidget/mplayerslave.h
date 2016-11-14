#ifndef MPLAYERSLAVE_H
#define MPLAYERSLAVE_H

// non-blocking control commands (fire and forget)
#define Pause           "pause"
#define SeekForward     "seek +%1 type=1"
#define SeekReverse     "seek -%1 type=1"
#define Osd             "osd"
#define Mute            "mute"
#define MuteOn          "mute 1"
#define MuteOff         "mute 0"
#define VolumeUp        "volume +%1"
#define VolumeDown      "volume -%1"
#define VolumeSet       "volume %1 1"
#define ShowText        "osd_show_text %1 %2"
#define KeyEvent        "key_down_event %1"

// blocking queries
#define MediaSource     "get_property path"
#define Resolution      "get_video_resolution"
#define MuteStatus      "pausing_keep_force get_property mute"
#define Volume          "get_property volume"
#define Length          "get_time_length"
#define Position        "get_time_pos"
#define Progress        "get_percent_pos"
#define PauseStatus     "pausing_keep_force get_property pause"

// regular expressions to extract answer to query
#define RxResolution    "ANS_VIDEO_RESOLUTION='([0-9]+) x ([0-9]+)'"
#define RxMuteStatus    "ANS_mute=([a-z]+)"
#define RxPauseStatus   "ANS_pause=([a-z]+)"

#endif // MPLAYERSLAVE_H
