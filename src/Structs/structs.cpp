//
// Created by laceperro on 4/2/2026.
//
#include <windows.h>
#include <locale>

struct WaveStream {
    DWORD unk_00;
    DWORD pFormat;
    DWORD hFile;
    byte dataChunk[20];
    byte riffChunk[20];
    DWORD dataOffset;
};




struct GameConfig {
    char pad_00[149];
    char musicVolume;
    char ambientVolume;
    char pad_97;
    char audioFlags;
    char pad_99[29];
    char currentLevel;
    char levelState;
    char previousLevel;
    char levelTransitionCount;
    char languageId;
};





struct DSDeviceEntry {
    char szDescription[40];
    char guid[16];
};

typedef struct DSManager DSManager, *PDSManager;

struct DSManager {
    u_int vtable;
    char bInitilizaed;
    char pad[3];
    int unk_08;
    int nk_0c;
    int unk_10;
    int unk_14;
    DSDeviceEntry deviceList[20];
    u_int nDeviceCount;
    int unk_47C;
    char unk_480[64];
    char unk_4C0[64];
    int hNotifyEvents[16];
    int unk_500;
};

typedef struct LevelMusicEntry LevelMusicEntry, *PLevelMusicEntry;

struct LevelMusicEntry {
    short trackIndex;
    short unk_02;
};

