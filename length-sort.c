#include <stdio.h>
#include <string.h>

#include "svec.h"

void
sort(svec* xs)
{
    // TODO: sort input vector by string length
    // see "man 3 strlen"
    int index = 0;
    while(index < xs->size){
        if(index == 0){
            index++;
        }
        else if(strlen(svec_get(xs, index)) >= strlen(svec_get(xs, index-1))){
            index++;
        }
        else{
            svec_swap(xs, index, index-1);
            index--;
        }
    }
    return;
}
void
chomp(char* text)
{
    // TODO: Modify input string to remove trailing newline ('\n')
    int len = strlen(text);
    if(len>0 && text[len-1] == '\n'){
        text[len-1] = 0;
    }
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage:\n  %s input-file\n", argv[0]);
        return 1;
    }

    FILE* fh = fopen(argv[1], "r");
    if (!fh) {
        perror("open failed");
        return 1;
    }

    svec* xs = make_svec();
    char temp[128];

    while (1) {
        char* line = fgets(temp, 128, fh);
        if (!line) {
            break;
        }

        chomp(line);
        svec_push_back(xs, line);
    }

    fclose(fh);

    sort(xs);

    for (int ii = 0; ii < xs->size; ++ii) {
        char* line = svec_get(xs, ii);
        printf("%s\n", line);
    }

    free_svec(xs);
    return 0;
}
