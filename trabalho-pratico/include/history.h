#ifndef _HISTORY_H_
#define _HISTORY_H_

typedef struct history History;

const char *getHistoryId(const History *hist);
const char *getHistoryUserId(const History *hist);
const char *getHistoryMusicId(const History *hist);
const char *getHistoryTimestamp(const History *hist);
const char *getHistoryDuration(const History *hist);
const char *getHistoryPlatform(const History *hist);

void setHistoryId(History *hist, const char *id);
void setHistoryUserId(History *hist, const char *user_id);
void setHistoryMusicId(History *hist, const char *music_id);
void setHistoryTimestamp(History *hist, const char *timestamp);
void setHistoryDuration(History *hist, const char *duration);
void setHistoryPlatform(History *hist, const char *platform);

History *initHistory();
void freeHistory(History *hist);

#endif