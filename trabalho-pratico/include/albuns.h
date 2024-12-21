#ifndef _ALBUNS_H_
#define _ALBUNS_H_

typedef struct albuns Albuns;

char *getAlbumId(Albuns *album);
char *getAlbumTitle(Albuns *album);
char *getAlbumArtistsId(Albuns *album);
char *getAlbumYear(Albuns *album);
char *getAlbumProducers(Albuns *album);

void setAlbumId(Albuns *album, char *id);
void setAlbumTitle(Albuns *album, char *title);
void setAlbumArtistsId(Albuns *album, char *artists_id);
void setAlbumYear(Albuns *album, char *year);
void setAlbumProducers(Albuns *album, char *producers);

Albuns *initAlbum();
void destroyAlbum(Albuns *album);

Albuns *separateAlbuns(char *line);

#endif