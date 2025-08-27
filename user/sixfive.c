#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc <= 1){
        fprintf(2, "usage: sixfive filePath\n");
        exit(1);
    }
    else{
        int fd = open(argv[1], 0);
        if(fd < 0){
            fprintf(2, "sixfive: cannot open %s\n", argv[1]);
            exit(1);
        }
        char buf[512];
        int n, i;
        char num[8];
        int index = 0;
        while((n = read(fd, buf, sizeof(buf))) > 0){
            for(i = 0; i < n; i++){
                char c = buf[i];
                if(c >= '0' && c <= '9'){
                    if(index < sizeof(num)-1)
                        num[index++] = c;
                } else if(c == '-'){
                    if(index > 0){
                        num[index] = '\0';
                        printf("%s\n", num);
                        index = 0;
                    }
                    i += 5;
                }
            }
        }
        close(fd);
    }
    exit(0);
}