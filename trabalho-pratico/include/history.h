#ifndef _HISTORY_H_
#define _HISTORY_H_

typedef struct history History;


char *getHistoryId(History *hist);
char *getHistoryUserId(History *hist);
char *getHistoryMusicId(History *hist);
char *getHistoryTimestamp(History *hist);
char *getHistoryDuration(History *hist);
char *getHistoryPlatform(History *hist);

void setHistoryId(History *hist, char *id);
void setHistoryUserId(History *hist, char *user_id);
void setHistoryMusicId(History *hist, char *music_id);
void setHistoryTimestamp(History *hist, char *timestamp);
void setHistoryDuration(History *hist, char *duration);
void setHistoryPlatform(History *hist, char *platform);

History *initHistory();
void destroyHistory(History *hist);

History *separateHistory(char *line);


#endif