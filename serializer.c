#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "serializer.h"
#include "info.h"

void serialize(struct diagnostics *d, char *login, char *password, char *out)
{
    char buff[10];
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "Diagnostics");
    xmlDocSetRootElement(doc, root_node);

    xmlNewChild(root_node, NULL, BAD_CAST "Version", BAD_CAST "0.1");

    xmlNodePtr authNode = xmlNewChild(root_node, NULL, BAD_CAST "Authentcation", NULL);
    xmlNewChild(authNode, NULL, BAD_CAST "Login", BAD_CAST login);
    xmlNewChild(authNode, NULL, BAD_CAST "Password", BAD_CAST password);

    sprintf(buff, "%ld", d->time);
    xmlNewChild(root_node, NULL, BAD_CAST "Time", BAD_CAST buff);

    xmlNodePtr node = xmlNewChild(root_node, NULL, BAD_CAST "Memory", NULL);

    sprintf(buff, "%d", d->memory.memtotal);
    xmlNewChild(node, NULL, BAD_CAST "Total", BAD_CAST buff);

    sprintf(buff, "%d", d->memory.memfree);
    xmlNewChild(node, NULL, BAD_CAST "Free", BAD_CAST buff);

    sprintf(buff, "%d", d->memory.buffers);
    xmlNewChild(node, NULL, BAD_CAST "Buffers", BAD_CAST buff);

    sprintf(buff, "%d", d->memory.cached);
    xmlNewChild(node, NULL, BAD_CAST "Cached", BAD_CAST buff);

    sprintf(buff, "%d", d->memory.swapcached);
    xmlNewChild(node, NULL, BAD_CAST "Swapcached", BAD_CAST buff);

    sprintf(buff, "%d", d->memory.active);
    xmlNewChild(node, NULL, BAD_CAST "Active", BAD_CAST buff);

    sprintf(buff, "%d", d->memory.inactive);
    xmlNewChild(node, NULL, BAD_CAST "Inactive", BAD_CAST buff);

    node = xmlNewChild(root_node, NULL, BAD_CAST "CpuStatus", NULL);

    sprintf(buff, "%d", d->cpustatus.user);
    xmlNewChild(node, NULL, BAD_CAST "User", BAD_CAST buff);

    sprintf(buff, "%d", d->cpustatus.nice);
    xmlNewChild(node, NULL, BAD_CAST "Nice", BAD_CAST buff);

    sprintf(buff, "%d", d->cpustatus.system);
    xmlNewChild(node, NULL, BAD_CAST "System", BAD_CAST buff);

    sprintf(buff, "%d", d->cpustatus.idle);
    xmlNewChild(node, NULL, BAD_CAST "Idle", BAD_CAST buff);

    sprintf(buff, "%d", d->cpustatus.iowait);
    xmlNewChild(node, NULL, BAD_CAST "IOWait", BAD_CAST buff);
    
    sprintf(buff, "%d", d->cpustatus.irq);
    xmlNewChild(node, NULL, BAD_CAST "IRQ", BAD_CAST buff);

    sprintf(buff, "%d", d->cpustatus.softirq);
    xmlNewChild(node, NULL, BAD_CAST "SoftIRQ", BAD_CAST buff);

    node = xmlNewChild(root_node, NULL, BAD_CAST "Processors", NULL);

    int i;
    for (i = 0; i < d->cpu.processors; i++) {
        xmlNodePtr innerNode = xmlNewChild(node, NULL, BAD_CAST "Processor", NULL);

        sprintf(buff, "%d", d->cpu.procs[i].processor);
        xmlNewChild(innerNode, NULL, BAD_CAST "Processor", BAD_CAST buff);

        xmlNewChild(innerNode, NULL, BAD_CAST "ModelName", BAD_CAST d->cpu.procs[i].modelname);

        sprintf(buff, "%d", d->cpu.procs[i].cachesize);
        xmlNewChild(innerNode, NULL, BAD_CAST "CacheSize", BAD_CAST buff);

        sprintf(buff, "%d", d->cpu.procs[i].cpucores);
        xmlNewChild(innerNode, NULL, BAD_CAST "CpuCores", BAD_CAST buff);

        sprintf(buff, "%d", d->cpu.procs[i].coreid);
        xmlNewChild(innerNode, NULL, BAD_CAST "CoreID", BAD_CAST buff);

        sprintf(buff, "%f", d->cpu.procs[i].cpuMHz);
        xmlNewChild(innerNode, NULL, BAD_CAST "CpuMHz", BAD_CAST buff);
    }

    xmlChar *xmlBuffer = NULL;
    int size;
    xmlDocDumpFormatMemory(doc, &xmlBuffer, &size, 1);

    sprintf(out, "%s\n", (char*)xmlBuffer);

    xmlFree(xmlBuffer);
    xmlFreeDoc(doc);
    xmlCleanupParser();
}
