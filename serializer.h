#ifndef SERIALIZER_H
#define SERIALIZER_H

struct diagnostics;

void serialize(struct diagnostics *d, char *login, char *password, char *out);
void freeXml(char *xml);

#endif
