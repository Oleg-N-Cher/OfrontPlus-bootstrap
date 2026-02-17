/* Ofront+ 1.0 -sC -48 */
#include "SYSTEM.oh"
#include "SDL2.oh"
#include "SDL2mixer.oh"


export BOOLEAN Sound_initOk;


export void Sound_Free (SDL2mixer_PMix_Chunk *sound);
export void Sound_Load (SDL2mixer_PMix_Chunk *sound, CHAR *fileName, INTEGER fileName__len);
export void Sound_Play (SDL2mixer_PMix_Chunk sound);
export void Sound_Quit (void);


/*============================================================================*/

void Sound_Load (SDL2mixer_PMix_Chunk *sound, CHAR *fileName, INTEGER fileName__len)
{
  if (Sound_initOk) {
    *sound = SDL2mixer_Mix_LoadWAV((SYSTEM_ADRINT)fileName);
  } else {
    *sound = NIL;
  }
}

/*----------------------------------------------------------------------------*/
void Sound_Play (SDL2mixer_PMix_Chunk sound)
{
  if (Sound_initOk && sound != NIL) {
    if (SDL2mixer_Mix_PlayChannel(-1, sound, 0) == 0) {
    }
  }
}

/*----------------------------------------------------------------------------*/
void Sound_Free (SDL2mixer_PMix_Chunk *sound)
{
  if (Sound_initOk && *sound != NIL) {
    Mix_FreeChunk(*sound);
  }
}

/*----------------------------------------------------------------------------*/
void Sound_Quit (void)
{
  Mix_CloseAudio();
  SDL2_QuitSubSystem(0x10);
}

/*----------------------------------------------------------------------------*/

export void *Sound__init (void)
{
  __DEFMOD;
  __REGMOD("Sound", 0);
  __REGCMD("Quit", Sound_Quit);
/* BEGIN */
  Sound_initOk = SDL2_InitSubSystem(0x10) >= 0;
  if (Sound_initOk) {
    Sound_initOk = 0 <= Mix_OpenAudio(22050, -32752, 2, 4096);
  }
  __ENDMOD;
}
