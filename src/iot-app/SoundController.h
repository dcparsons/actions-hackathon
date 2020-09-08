#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

/**
 * @brief   Plays a sound associated with build success
 * 
 */
void PlaySuccessSound(void);
/**
 * @brief   Plays a sound associated with build failure
 * 
 */
void PlayFailureSound(void);
/**
 * @brief   Used to setup buffers, etc.
 * 
 */
void SetupAudioBuffer(void);


#endif