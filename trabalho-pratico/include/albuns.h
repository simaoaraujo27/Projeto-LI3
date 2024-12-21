#ifndef _ALBUNS_H_
#define _ALBUNS_H_

typedef struct albuns Albuns;

const char *getAlbumId(const Albuns *album);
const char *getAlbumTitle(const Albuns *album);
const char *getAlbumArtistsId(const Albuns *album);
const char *getAlbumYear(const Albuns *album);
const char *getAlbumProducers(const Albuns *album);

void setAlbumId(Albuns *album, const char *id);
void setAlbumTitle(Albuns *album, const char *title);
void setAlbumArtistsId(Albuns *album, const char *artists_id);
void setAlbumYear(Albuns *album, const char *year);
void setAlbumProducers(Albuns *album, const char *producers);

Albuns *initAlbum();
void destroyAlbum(Albuns *album);

Albuns *separateAlbuns(char *line);

#endif