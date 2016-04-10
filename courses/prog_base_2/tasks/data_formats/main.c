
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


// gcc main.c -I include -L  lib -llibxml2
int main() {
	char line[100];
	char text[1000] = "";
	FILE *fr = fopen("pensioners.xml", "r");
	while(fgets(line, 100, fr)){
        strcat(text, line);
	}

    xmlDoc * xDoc;

    xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("Error parsing xml from memory");
        return 1;
    }
    xmlNode * xRootEl;
    xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode *xCur = xRootEl->children; NULL != xCur; xCur = xCur->next){
        if(XML_ELEMENT_NODE == xCur->type){
            printf("Tag name <%s>\n", xCur->name);

            for(xmlNode *xJ = xCur->children; NULL != xJ; xJ = xJ->next){
                if(XML_ELEMENT_NODE == xJ->type){
                    if(strcmp(xJ->name, "bloodType") == 0){
                        xmlNode * xType = xJ;
                        xmlNode * xFact = xType->children->next;
                        char * factor = xmlGetProp(xType, "factor");
                        char * fact = xmlNodeGetContent(xFact);
                        printf("\t%19s: %s (%s)\n", "blood type", factor, fact);
                        continue;
                    }
                    const char * content = xmlNodeGetContent(xJ);
                    printf("\tTag name %10s: %s\n", xJ->name, content);
                }
            }
        }
    }

	return 0;
}

