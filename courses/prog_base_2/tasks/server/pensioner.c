#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <time.h>

#include <libxml/tree.h>
#include "pensioner.h"

//Private fields

static pensioner_t *pensioner_from_xml (pensioner_t *curPensioner, xmlNode *curNode) {
    char *data;
    char *properties;

    properties = (char *)xmlGetProp(curNode, (const xmlChar *)"name");
    strcpy(curPensioner->name, properties);

    properties = (char *)xmlGetProp(curNode, (const xmlChar *)"surname");
    strcpy(curPensioner->surname, properties);

    for (curNode = curNode->children; curNode != NULL; curNode = curNode->next) {
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"birthDate")) {
            data = (char *)xmlNodeGetContent(curNode);
            sscanf(data, "%d-%d-%d", &curPensioner->birthDate.tm_year, &curPensioner->birthDate.tm_mday, &curPensioner->birthDate.tm_mon);
            continue;
        }

        if (!xmlStrcmp(curNode->name, (const xmlChar *)"pension")) {
            data = (char *)xmlNodeGetContent(curNode);
            curPensioner->pension = atof(data);
            continue;
        }

        if(!xmlStrcmp(curNode->name, (const xmlChar *)"experience")) {
            data = (char *)xmlNodeGetContent(curNode);
            curPensioner->experience = atoi(data);
            continue;
        }
    }

    return curPensioner;
}

// Public fields

pensioner_t *pensioner_new (void) {
    pensioner_t *pensioner = malloc(sizeof(pensioner_t));

    strcpy(pensioner->name, "");
    strcpy(pensioner->surname, "");

    memset(&pensioner->birthDate, 0, sizeof(pensioner->birthDate));

    pensioner->pension = 0;
    pensioner->experience = 0;

    return pensioner;
}

void pensioner_delete (pensioner_t *pensioner) {
    free (pensioner);
}

void xmlParse (pensioner_t *pensionerSet[], const char *XMLFileName) {
    xmlDoc *doc = xmlReadFile(XMLFileName, "UTF-8", 0);

    if (doc == NULL) {
        xmlFreeDoc (doc);
        return;
    }

    xmlNode *xml_root = xmlDocGetRootElement(doc);
    xmlNode *curNode;

    int i;
    for (i = 0, curNode = xml_root->children; curNode != NULL; curNode = curNode->next)
        if (!xmlStrcmp(curNode->name, (const xmlChar *)"pensioner")) pensioner_from_xml(pensionerSet[i++], curNode);

    xmlFreeDoc (doc);
}

void printPensionerInfo (pensioner_t *pensioner) {
    printf ("\t[%s]\n"
            "\t[%s]\n"
            "\t%d-%d-%d\n"
            "\t%f\n"
            "\t%i\n",
            pensioner->name,
            pensioner->surname,
            pensioner->birthDate.tm_year, pensioner->birthDate.tm_mon, pensioner->birthDate.tm_mday,
            pensioner->pension,
            pensioner->experience);
}
